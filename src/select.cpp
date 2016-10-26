/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>
    
    Created on 20.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
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

