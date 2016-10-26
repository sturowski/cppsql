/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>
    
    Created on 20.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
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
    Join join(left_table, right_table, JoinType::LEFT, comparison);
    this->joins_.push_back(join);
}

void cppsql::QueryBuilder::rightJoin(From left_table, From right_table, const Comparison comparison)
{
    Join join(left_table, right_table, JoinType::RIGHT, comparison);
    this->joins_.push_back(join);
}

void cppsql::QueryBuilder::innerJoin(From left_table, From right_table, const Comparison comparison)
{
    Join join(left_table, right_table, JoinType::INNER, comparison);
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
        throw ErrorNames[Errors::QUERY_CONTAINS_NO_SELECT];
    if (!this->has_fromClauses())
        throw ErrorNames[Errors::QUERY_CONTAINS_NO_FROM];

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

const std::string cppsql::QueryBuilder::create_from_string() const
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

const std::string cppsql::QueryBuilder::create_where_string() const
{
    std::string statement = "WHERE ";
    bool first = true; // we need to know if we have the first item, to set the ',' correct
    for (const auto& where : this->whereClauses_) {
        if (!first)
            statement += " "+where.get_operator()+" ";
        else
            first = false;
        statement += where.get_clause();
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









