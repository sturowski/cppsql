/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>

    Created on 25.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
*/
#include "from.h"

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

