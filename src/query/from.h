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
#ifndef CPPSQL_FROM_H
#define CPPSQL_FROM_H
#include <string>

namespace cppsql {

class From {
public:
    From(const std::string table_name); //for a small query without a specific table declaration
    From(const std::string table_name,
            const std::string alias); //for complex queries with specific table declaration
    From(const std::string table_name,
            const std::string alias,
            const std::string join_column); //for complex queries with joins

    const std::string to_string();
    const std::string to_string() const;

    const std::string get_table_name() const;
    const std::string get_alias() const;
    const std::string get_join_column() const;

private:
    const std::string create_string() const;

    std::string table_name_;
    std::string alias_;
    std::string join_column_;

};

}

#endif //CPPSQL_FROM_H
