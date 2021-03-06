/* Copyright (c) 2017 Oracle and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   51 Franklin Street, Suite 500, Boston, MA 02110-1335 USA */

#ifndef DD_SYSTEM_VIEWS__TABLES_INCLUDED
#define DD_SYSTEM_VIEWS__TABLES_INCLUDED

#include "dd/impl/system_views/system_view_definition_impl.h"
#include "dd/impl/system_views/system_view_impl.h"

namespace dd {
namespace system_views {

/*
  The class representing INFORMATION_SCHEMA.TABLES system view definition
  common to both modes of setting 'information_schema_stats=latest|cached'.

  There are two definitions of information_schema.tables.
  1. INFORMATION_SCHEMA.TABLES view which picks dynamic column
     statistics from mysql.table_stats which gets populated when
     we execute 'anaylze table' command.

  2. INFORMATION_SCHEMA.TABLES_DYNAMIC view which retrieves dynamic
     column statistics using a internal UDF which opens the user
     table and reads dynamic table statistics.

  MySQL server uses definition 1) by default. The session variable
  information_schema_stats=latest would enable use of definition 2).
*/
class Tables_base : public System_view_impl<System_view_select_definition_impl>
{
public:
  enum enum_fields
  {
    FIELD_TABLE_CATALOG,
    FIELD_TABLE_SCHEMA,
    FIELD_TABLE_NAME,
    FIELD_TABLE_TYPE,
    FIELD_ENGINE,
    FIELD_VERSION,
    FIELD_ROW_FORMAT,
    FIELD_TABLE_ROWS,
    FIELD_AVG_ROW_LENGTH,
    FIELD_DATA_LENGTH,
    FIELD_MAX_DATA_LENGTH,
    FIELD_INDEX_LENGTH,
    FIELD_DATA_FREE,
    FIELD_AUTO_INCREMENT,
    FIELD_CREATE_TIME,
    FIELD_UPDATE_TIME,
    FIELD_CHECK_TIME,
    FIELD_TABLE_COLLATION,
    FIELD_CHECKSUM,
    FIELD_CREATE_OPTIONS,
    FIELD_TABLE_COMMENT
  };

  Tables_base();

  virtual const String_type &name() const = 0;
};


/*
 The class representing INFORMATION_SCHEMA.TABLES system view definition
 used when setting is 'information_schema_stats=cached'.
*/
class Tables : public Tables_base
{
public:
  Tables();

  static const Tables_base &instance();

  static const String_type &view_name()
  {
    static String_type s_view_name("TABLES");
    return s_view_name;
  }

  virtual const String_type &name() const
  { return Tables::view_name(); }
};


/*
 The class representing INFORMATION_SCHEMA.TABLES system view definition
 used when setting is 'information_schema_stats=latest'.
*/
class Tables_dynamic : public Tables_base
{
public:
  Tables_dynamic();

  static const Tables_base &instance();

  static const String_type &view_name()
  {
    static String_type s_view_name("TABLES_DYNAMIC");
    return s_view_name;
  }

  virtual const String_type &name() const
  { return Tables_dynamic::view_name(); }

  // This view definition is hidden from user.
  virtual bool hidden() const
  { return true; }
};

}
}

#endif // DD_SYSTEM_VIEWS__TABLES_INCLUDED
