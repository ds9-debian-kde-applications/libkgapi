/*
 * This file is part of LibKGAPI library
 *
 * Copyright (C) 2013  Daniel Vrátil <dvratil@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "permissioncreatejob.h"
#include "account.h"
#include "driveservice.h"
#include "permission.h"
#include "utils.h"

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <KDE/KLocalizedString>

using namespace KGAPI2;

class DrivePermissionCreateJob::Private
{
  public:
    Private(DrivePermissionCreateJob *parent);
    void processNext();

    DrivePermissionsList permissions;
    QString fileId;

  private:
    DrivePermissionCreateJob* const q;
};

DrivePermissionCreateJob::Private::Private(DrivePermissionCreateJob *parent):
    q(parent)
{
}

void DrivePermissionCreateJob::Private::processNext()
{
    if (permissions.isEmpty()) {
        q->emitFinished();
        return;
    }

    const DrivePermissionPtr permission = permissions.takeFirst();

    const QUrl url = DriveService::createPermissionUrl(fileId);

    QNetworkRequest request;
    request.setRawHeader("Authorization", "Bearer " + q->account()->accessToken().toLatin1());
    request.setUrl(url);

    const QByteArray rawData = DrivePermission::toJSON(permission);
    q->enqueueRequest(request, rawData, QLatin1String("application/json"));
}

DrivePermissionCreateJob::DrivePermissionCreateJob(const QString &fileId,
                                                   const DrivePermissionPtr &permission,
                                                   const AccountPtr &account,
                                                   QObject *parent):
    CreateJob(account, parent),
    d(new Private(this))
{
    d->fileId = fileId;
    d->permissions << permission;
}

DrivePermissionCreateJob::DrivePermissionCreateJob(const QString &fileId,
                                                   const DrivePermissionsList &permissions,
                                                   const AccountPtr &account,
                                                   QObject *parent):
    CreateJob(account, parent),
    d(new Private(this))
{
    d->fileId = fileId;
    d->permissions = permissions;
}

DrivePermissionCreateJob::~DrivePermissionCreateJob()
{
    delete d;
}


void DrivePermissionCreateJob::start()
{
    d->processNext();
}

ObjectsList DrivePermissionCreateJob::handleReplyWithItems(const QNetworkReply *reply,
                                                           const QByteArray &rawData)
{
   const QString contentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();
    ContentType ct = Utils::stringToContentType(contentType);
    ObjectsList items;
    if (ct == KGAPI2::JSON) {
        items << DrivePermission::fromJSON(rawData);
    } else {
        setError(KGAPI2::InvalidResponse);
        setErrorString(i18n("Invalid response content type"));
        emitFinished();
    }

    // Enqueue next item or finish
    d->processNext();

    return items;
}

