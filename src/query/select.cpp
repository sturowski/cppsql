/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>
    
    Created on 20.10.16

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

#include "select.h"

cppsql::Select::Select(const std::string column_name)
        :
        column_name_(column_name)
{
}

cppsql::Select::Select(const std::string column_name, const std::string table_name)
        :
        column_name_(column_name),
        table_name_(table_name)
{
}

const std::string cppsql::Select::to_string()
{
    return this->create_string();
}

const std::string cppsql::Select::create_string() const
{
    std::string statement;
    if (!this->table_name_.empty())
        statement = this->table_name_+".";
    return statement+this->column_name_;
}

const std::string cppsql::Select::to_string() const
{
    return this->create_string();
}

