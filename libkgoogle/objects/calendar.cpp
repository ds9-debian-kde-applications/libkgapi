/*
    libKGoogle - KGoogleObject - Calendar
    Copyright (C) 2011  Dan Vratil <dan@progdan.cz>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "calendar.h"
#include "calendar_p.h"

#include <qdebug.h>
#include <qjson/parser.h>
#include <qjson/serializer.h>

using namespace KGoogle::Objects;

CalendarData::CalendarData(const CalendarData &other) :
  QSharedData(other),
  title(other.title),
  details(other.details),
  timezone(other.timezone),
  location(other.location),
  editable(other.editable),
  alarms(other.alarms)
{ }

Calendar::Calendar() :
  d(new CalendarData)
{ }

Calendar::Calendar(const Calendar &other) :
  KGoogle::Object(other),
  d(other.d)
{ }

Calendar::~Calendar()
{ }


void Calendar::setUid(const QString &uid)
{
  d->uid = uid;
}

QString Calendar::uid() const
{
  return d->uid;
}


QString Calendar::title() const
{
  return d->title.isEmpty() ? "Google Calendar" : d->title;
}

void Calendar::setTitle(const QString &title)
{
  d->title = title;
}

QString Calendar::details() const
{
  return d->details;
}

void Calendar::setDetails(const QString &details)
{
  d->details = details;
}

QString Calendar::location() const
{
  return d->location;
}

void Calendar::setLocation(const QString &location)
{
  d->location = location;
}

QString Calendar::timezone() const
{
  return d->timezone;
}

void Calendar::setTimezone(const QString &timezone)
{
  d->timezone = timezone;
}

bool Calendar::editable() const
{
  return d->editable;
}

void Calendar::setEditable(const bool editable)
{
  d->editable = editable;
}

void Calendar::setDefaultReminders (const Alarm::List &alarms)
{
  d->alarms = alarms;
}

void Calendar::addDefaultReminer (const Alarm::Ptr &alarm)
{
  d->alarms.append(alarm);
}

Alarm::List Calendar::defaultReminders() const
{
  return d->alarms;
}

