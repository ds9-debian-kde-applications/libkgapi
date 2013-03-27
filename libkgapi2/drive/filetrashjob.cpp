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


#include "filetrashjob.h"
#include "driveservice.h"

using namespace KGAPI2;

class DriveFileTrashJob::Private
{
};

DriveFileTrashJob::DriveFileTrashJob(const QString &fileId,
                                     const AccountPtr &account, QObject *parent):
    DriveFileAbstractModifyJob(fileId, account, parent),
    d(new Private)
{
}

DriveFileTrashJob::DriveFileTrashJob(const QStringList &filesIds,
                                     const AccountPtr &account, QObject *parent):
    DriveFileAbstractModifyJob(filesIds, account, parent),
    d(new Private)
{
}

DriveFileTrashJob::DriveFileTrashJob(const DriveFilePtr &file,
                                     const AccountPtr &account, QObject *parent):
    DriveFileAbstractModifyJob(file, account, parent),
    d(new Private)
{
}

DriveFileTrashJob::DriveFileTrashJob(const DriveFilesList &files,
                                     const AccountPtr &account, QObject *parent):
    DriveFileAbstractModifyJob(files, account, parent),
    d(new Private)
{
}

DriveFileTrashJob::~DriveFileTrashJob()
{
    delete d;
}

QUrl DriveFileTrashJob::url(const QString &fileId)
{
    return DriveService::trashFileUrl(fileId);
}

#include "filetrashjob.moc"
