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

#ifndef CPPSQL_QUERYBUILDER_H
#define CPPSQL_QUERYBUILDER_H

#include <iostream>
#include <string>
#include <vector>

#include "from.h"
#include "join.h"
#include "select.h"
#include "where.h"
#include "object.h"

namespace cppsql {

class Query {
public:
    Query();
    Query(const Query& builder);
    Query& operator=(Query& builder);
    virtual ~Query() { }

    Query& select(Select select);
    Query& select(const std::string column_name);
    Query& select(const std::string column_name, const std::string table_name);

    Query& from(From from);
    Query& from(const std::string table_name);
    Query& from(const std::string table_name, const std::string alias);

    void leftJoin(From left_table,
            From right_table,
            const Comparison comparison);
    void rightJoin(From left_table,
            From right_table,
            const Comparison comparison);
    void innerJoin(From left_table,
            From right_table,
            const Comparison comparison);

    Query& where(Where where);
    Query& where(const std::string clause, const Operator op);

    const std::string GetSelectStatement();

    const bool is_empty() const;
    const bool is_distinct() const;
    const bool has_selects() const;
    const bool has_fromClauses() const;
    const bool has_joins() const;
    const bool has_whereClauses() const;
    const bool has_orderByConditions() const;

    const bool set_distinct(const bool distinct);

    const std::string create_select_string() const;
    const std::string create_from_string() const;
    const std::string create_where_string() const;

private:
    bool distinct_;
    std::vector<Select> selects_;
    std::vector<From> fromClauses_;
    std::vector<Join> joins_;
    std::vector<Where> whereClauses_;
};

}

#endif //CPPSQL_QUERYBUILDER_H
