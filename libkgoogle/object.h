/*
    libKGoogle - Object
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


#ifndef LIBKGOOGLE_OBJECT_H
#define LIBKGOOGLE_OBJECT_H

#include <qstring.h>
#include <qshareddata.h>

#include <libkgoogle/libkgoogle_export.h>

namespace KGoogle {

  class ObjectPrivate;

  /**
   * Base class for Google objects.
   *
   * Google object represents data received
   * from a Google service.
   */
  class LIBKGOOGLE_EXPORT Object
  {
    public:
      Object();

      Object(const Object &other);

      virtual ~Object();

      /**
       * Sets etag of this object.
       *
       * Etag represents a revision of an object.
       * When object is changed on the remote side
       * is given a new etag.
       */
      void setEtag (const QString &etag);

      /**
       * Returns tag of this object.
       */
      const QString& etag() const;

    private:
      QExplicitlySharedDataPointer< ObjectPrivate > d;

  };

} // namespace KGoogle

#endif // LIBKGOOGLE_OBJECT_H
