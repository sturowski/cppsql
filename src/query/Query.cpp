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

#include <ParseHelper.h>
#include <algorithm>
#include "Errors.h"
#include "Query.h"

cppsql::Query::Query()
        :distinct_(false)
{

}

cppsql::Query::Query(const Query& builder)
        :
        distinct_(builder.distinct_),
        selects_(builder.selects_),
        fromClauses_(builder.fromClauses_),
        whereClauses_(builder.whereClauses_),
        type_(TYPE::NO)
{

}

cppsql::Query& cppsql::Query::operator=(Query& builder)
{
    this->distinct_ = builder.distinct_;
    this->selects_ = builder.selects_;
    this->fromClauses_ = builder.fromClauses_;
    this->whereClauses_ = builder.whereClauses_;
    return *this;
}

void cppsql::Query::left_join(From left_table, From right_table, const Comparison comparison)
{
    Join join(left_table, right_table, JoinType::LEFT, comparison);
    this->joins_.push_back(join);
}

void cppsql::Query::right_join(From left_table, From right_table, const Comparison comparison)
{
    Join join(left_table, right_table, JoinType::RIGHT, comparison);
    this->joins_.push_back(join);
}

void cppsql::Query::inner_join(From left_table, From right_table, const Comparison comparison)
{
    Join join(left_table, right_table, JoinType::INNER, comparison);
    this->joins_.push_back(join);
}

cppsql::Query& cppsql::Query::where(Where where)
{
    this->whereClauses_.push_back(where);
    return *this;
}

const std::string cppsql::Query::statement(Params params) const throw()
{
    if (this->type_==TYPE::SELECT)
        return create_select_statement(params);
    if (this->type_==TYPE::INSERT)
        return create_insert_statement(params);
    return "";
}
const std::string cppsql::Query::create_select_statement(cppsql::Params& params) const
{
    if (!this->has_selects())
        throw cppsql::ErrorNames[cppsql::QUERY_CONTAINS_NO_SELECT];
    if (!this->has_from_clauses())
        throw cppsql::ErrorNames[cppsql::QUERY_CONTAINS_NO_FROM];

    std::string statement;
    statement += this->create_select_string();
    statement += " ";
    statement += this->create_from_string();
    if (this->has_where_clauses()) {
        statement += " ";
        statement += this->create_where_string();
    }

    if (!params.is_empty()) {
        this->replace_params(statement, params);
    }
    return statement;
}
const std::string cppsql::Query::create_select_string() const
{
    std::string statement = "SELECT ";
    if (is_distinct())
        statement += "DISTINCT ";

    bool first = true; // we need to know if we have the first item, to set the ',' correct

    for (const auto& select : this->selects_) {
        if (!first)
            statement += ", ";
        else
            first = false;
        statement += select.to_string();
    }
    return statement;
}

const std::string cppsql::Query::create_from_string() const
{
    std::string statement = "FROM ";
    bool first = true; // we need to know if we have the first item, to set the ',' correct
    for (const auto& from : this->fromClauses_) {
        if (!first)
            statement += ", ";
        else
            first = false;
        statement += from.to_string();
    }

    for (const auto& join : this->joins_) {
        if (!first)
            statement += ", ";
        else
            first = false;
        statement += join.GetJoinStatement();
    }

    return statement;
}

const std::string cppsql::Query::create_where_string() const
{
    std::string statement = "WHERE ";
    bool first = true; // we need to know if we have the first item, to set the ',' correct
    for (const auto& where : this->whereClauses_) {
        if (first) {
            statement += where.to_string(false);
            first = false;
        }
        else
            statement += " "+where.to_string();

    }
    return statement;
}

// Returns an bool that says if this object, has no current members
// to build a useful sql query.
const bool cppsql::Query::empty() const
{
    bool empty = true;
    if (!this->has_selects())
        empty = false;
    if (!this->has_from_clauses())
        empty = false;
    if (!this->has_joins())
        empty = false;
    if (!this->has_where_clauses())
        empty = false;
    return empty;
}
const bool cppsql::Query::is_distinct() const
{
    return this->distinct_;
}
const bool cppsql::Query::has_selects() const
{
    return !this->selects_.empty();
}

const bool cppsql::Query::has_from_clauses() const
{
    return !this->fromClauses_.empty();
}

const bool cppsql::Query::has_joins() const
{
    return !this->joins_.empty();
}

const bool cppsql::Query::has_where_clauses() const
{
    return !this->whereClauses_.empty();;
}

const std::string cppsql::Query::to_string() const
{
    return statement();
}

cppsql::Query& cppsql::Query::and_where(std::string left_val, cppsql::Comparison comparison, std::string right_val)
{
    Where where(left_val, comparison, right_val, Operator::AND);
    this->whereClauses_.push_back(where);
    return *this;
}

cppsql::Query& cppsql::Query::and_where(std::string left_val, cppsql::Comparison comparison, cppsql::Query& right_val)
{
    Where where(left_val, comparison, right_val, Operator::AND);
    this->whereClauses_.push_back(where);
    return *this;
}

cppsql::Query& cppsql::Query::and_where(cppsql::Query& left_val, cppsql::Comparison comparison, std::string right_val)
{
    Where where(left_val, comparison, right_val, Operator::AND);
    this->whereClauses_.push_back(where);
    return *this;
}

cppsql::Query& cppsql::Query::and_where(std::string left_val, cppsql::Comparison comparison, std::string right_val,
        cppsql::Where& extension)
{
    Where where(left_val, comparison, right_val, extension, Operator::AND);
    this->whereClauses_.push_back(where);
    return *this;
}

cppsql::Query& cppsql::Query::and_where(std::string left_val, cppsql::Comparison comparison, cppsql::Query& right_val,
        cppsql::Where& extension)
{
    Where where(left_val, comparison, right_val, extension, Operator::AND);
    this->whereClauses_.push_back(where);
    return *this;
}

cppsql::Query& cppsql::Query::and_where(cppsql::Query& left_val, cppsql::Comparison comparison, std::string right_val,
        cppsql::Where& extension)
{
    Where where(left_val, comparison, right_val, extension, Operator::AND);
    this->whereClauses_.push_back(where);
    return *this;
}

cppsql::Query& cppsql::Query::or_where(std::string left_val, cppsql::Comparison comparison, std::string right_val)
{
    Where where(left_val, comparison, right_val, Operator::OR);
    this->whereClauses_.push_back(where);
    return *this;
}

cppsql::Query& cppsql::Query::or_where(std::string left_val, cppsql::Comparison comparison, cppsql::Query& right_val)
{
    Where where(left_val, comparison, right_val, Operator::OR);
    this->whereClauses_.push_back(where);
    return *this;
}

cppsql::Query& cppsql::Query::or_where(cppsql::Query& left_val, cppsql::Comparison comparison, std::string right_val)
{
    Where where(left_val, comparison, right_val, Operator::OR);
    this->whereClauses_.push_back(where);
    return *this;
}

cppsql::Query& cppsql::Query::or_where(std::string left_val, cppsql::Comparison comparison, std::string right_val,
        cppsql::Where& extension)
{
    Where where(left_val, comparison, right_val, extension, Operator::OR);
    this->whereClauses_.push_back(where);
    return *this;
}

cppsql::Query& cppsql::Query::or_where(std::string left_val, cppsql::Comparison comparison, cppsql::Query& right_val,
        cppsql::Where& extension)
{
    Where where(left_val, comparison, right_val, extension, Operator::OR);
    this->whereClauses_.push_back(where);
    return *this;
}

cppsql::Query& cppsql::Query::or_where(cppsql::Query& left_val, cppsql::Comparison comparison, std::string right_val,
        cppsql::Where& extension)
{
    Where where(left_val, comparison, right_val, extension, Operator::OR);
    this->whereClauses_.push_back(where);
    return *this;
}

const void cppsql::Query::replace_params(std::string& statement, cppsql::Params& params) const throw()
{
    long placeholder_count = std::count(statement.begin(), statement.end(), '?');
    std::vector<std::string> elements = split(statement, '?');
    if (placeholder_count!=params.size())
        throw SqlException(Errors::PARAMS_MISMATCH_COUNT_OF_PARAMS);
    statement.clear();
    for (int i = 0; i<placeholder_count; i++) {
        statement += elements[i]+"'"+params[i]+"'";
    }
    if (placeholder_count<elements.size())
        statement += elements.back();
}
void cppsql::Query::set_type(cppsql::Query::TYPE type)
{
    if (this->type_==TYPE::NO)
        this->type_ = type;
}
cppsql::Query& cppsql::Query::insert_into(const std::string table)
{
    table_ = table;
    set_type(TYPE::INSERT);
    return *this;
}
const std::string cppsql::Query::create_insert_statement(cppsql::Params& params) const
{
    if (!this->has_table())
        throw cppsql::ErrorNames[cppsql::QUERY_CONTAINS_NO_TABLE];
    if (params.is_empty())
        throw cppsql::ErrorNames[cppsql::QUERY_CONTAINS_NO_VALUES];

    std::string statement;
    statement += "INSERT INTO ";
    statement += this->table_;
    statement += " ";
    if (this->has_columns()) {
        statement += "(";
        statement += create_column_string();
        statement += ") ";
    }

    return statement;
}
const std::string cppsql::Query::create_column_string() const
{
    std::string statement;
    bool first = true; // we need to know if we have the first item, to set the ',' correct

    for (const auto& column : this->columns_) {
        if (!first)
            statement += ", ";
        else
            first = false;
        statement += column;
    }
    return statement;
}
const bool cppsql::Query::has_table() const
{
    return !this->table_.empty();
}
const bool cppsql::Query::has_columns() const
{
    return this->columns_.size();
}












