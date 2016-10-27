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

#include "errors.h"
#include "querybuilder.h"

cppsql::QueryBuilder::QueryBuilder()
{

}

cppsql::QueryBuilder::QueryBuilder(const QueryBuilder& builder)
{

}

cppsql::QueryBuilder& cppsql::QueryBuilder::operator=(QueryBuilder& builder)
{
    return *this;
}

cppsql::QueryBuilder& cppsql::QueryBuilder::select(Select select)
{
    this->selects_.push_back(select);
    return *this;
}

cppsql::QueryBuilder& cppsql::QueryBuilder::select(const std::string column_name)
{
    this->selects_.push_back(Select(column_name));
    return *this;
}

cppsql::QueryBuilder& cppsql::QueryBuilder::select(const std::string column_name, const std::string table_name)
{
    this->selects_.push_back(Select(column_name, table_name));
    return *this;
}

cppsql::QueryBuilder& cppsql::QueryBuilder::from(From from)
{
    this->fromClauses_.push_back(from);
    return *this;
}
cppsql::QueryBuilder& cppsql::QueryBuilder::from(const std::string table_name)
{
    this->fromClauses_.push_back(From(table_name));
    return *this;
}
cppsql::QueryBuilder& cppsql::QueryBuilder::from(const std::string table_name, const std::string alias)
{
    this->fromClauses_.push_back(From(table_name, alias));
    return *this;
}

void cppsql::QueryBuilder::leftJoin(From left_table, From right_table, const Comparison comparison)
{
    Join join(left_table, right_table, LEFT, comparison);
    this->joins_.push_back(join);
}

void cppsql::QueryBuilder::rightJoin(From left_table, From right_table, const Comparison comparison)
{
    Join join(left_table, right_table, RIGHT, comparison);
    this->joins_.push_back(join);
}

void cppsql::QueryBuilder::innerJoin(From left_table, From right_table, const Comparison comparison)
{
    Join join(left_table, right_table, INNER, comparison);
    this->joins_.push_back(join);
}

cppsql::QueryBuilder& cppsql::QueryBuilder::where(Where where)
{
    this->whereClauses_.push_back(where);
    return *this;
}

cppsql::QueryBuilder& cppsql::QueryBuilder::where(const std::string clause, const Operator op)
{
    this->whereClauses_.push_back(Where(clause, op));
    return *this;
}

const std::string cppsql::QueryBuilder::GetSelectStatement()
{
    if (!this->has_selects())
        throw ErrorNames[QUERY_CONTAINS_NO_SELECT];
    if (!this->has_fromClauses())
        throw ErrorNames[QUERY_CONTAINS_NO_FROM];

    std::string statement;
    statement += this->create_select_string();
    statement += " ";
    statement += this->create_from_string();
    statement += " ";
    statement += this->create_where_string();

    return statement;
}
const std::string cppsql::QueryBuilder::create_select_string() const
{
    std::string statement = "SELECT ";

    std::vector<Select>::const_iterator it = this->selects_.begin();
    for (; it!=this->selects_.end(); it++) {
        if (it!=this->selects_.begin())
            statement += ", ";
        statement += (*it).to_string();
    }
    return statement;
}

const std::string cppsql::QueryBuilder::create_from_string() const
{
    std::string statement = "FROM ";

    std::vector<From>::const_iterator it = this->fromClauses_.begin();
    for (; it!=this->fromClauses_.end(); it++) {
        if (it!=this->fromClauses_.begin())
            statement += ", ";
        statement += (*it).to_string();
    }

    std::vector<Join>::const_iterator it2 = this->joins_.begin();
    for (; it2!=this->joins_.end(); it2++) {
        if (it2!=this->joins_.begin() || !this->fromClauses_.empty())
            statement += ", ";
        statement += (*it2).GetJoinStatement();
    }

    return statement;
}

const std::string cppsql::QueryBuilder::create_where_string() const
{
    std::string statement = "WHERE ";

    std::vector<Where>::const_iterator it = this->whereClauses_.begin();
    for (; it!=this->whereClauses_.end(); it++) {
        if (it!=this->whereClauses_.begin())
            statement += " "+(*it).get_operator()+" ";

        statement += (*it).get_clause();
    }
    return statement;
}

// Returns an bool that says if this object, has no current members
// to build a useful sql query.
bool cppsql::QueryBuilder::is_empty()
{
    bool empty = true;
    if (!this->has_selects())
        empty = false;
    if (!this->has_fromClauses())
        empty = false;
    if (!this->has_joins())
        empty = false;
    if (!this->has_whereClauses())
        empty = false;
    return empty;
}

bool cppsql::QueryBuilder::has_selects()
{
    return !this->selects_.empty();
}

bool cppsql::QueryBuilder::has_fromClauses()
{
    return !this->fromClauses_.empty();
}

bool cppsql::QueryBuilder::has_joins()
{
    return !this->joins_.empty();
}

bool cppsql::QueryBuilder::has_whereClauses()
{
    return !this->whereClauses_.empty();;
}

bool cppsql::QueryBuilder::has_orderByConditions()
{
    return false;
}









