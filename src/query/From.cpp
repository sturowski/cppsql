/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>

    Created on 25.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    As a special exception, the Contributors give you permission to link
    this library with independent modules to produce an executable,
    regardless of the license terms of these independent modules, and to
    copy and distribute the resulting executable under terms of your choice,
    provided that you also meet, for each linked independent module, the
    terms and conditions of the license of that module. An independent
    module is a module which is not derived from or based on this library.
    If you modify this library, you must extend this exception to your
    version of the library.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
    License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "From.h"

cppsql::From::From(const std::string table_name)
        :
        table_name_(table_name)
{
}

cppsql::From::From(const std::string table_name, const std::string alias)
        :
        table_name_(table_name),
        alias_(alias)
{
}

cppsql::From::From(const std::string table_name, const std::string alias, const std::string join_column)
        :
        table_name_(table_name),
        alias_(alias),
        join_column_(join_column)
{
}

const std::string cppsql::From::to_string()
{
    return create_string();
}

const std::string cppsql::From::to_string() const
{
    return create_string();
}

const std::string cppsql::From::create_string() const
{
    std::string statement = this->table_name_;
    if (!this->alias_.empty())
        statement += " "+this->alias_;
    return statement;
}

const std::string cppsql::From::get_table_name() const
{
    return this->table_name_;
}

const std::string cppsql::From::get_alias() const
{
    return this->alias_;
}

const std::string cppsql::From::get_join_column() const
{
    std::string statement;
    if (!this->alias_.empty())
        statement = this->alias_+".";

    return statement+this->join_column_;
}

