/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>

    Created on 25.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
*/

#include "where.h"

cppsql::Where::Where(const std::string clause, const Operator op)
        :
        clause_(clause),
        operator_(op)
{
}

const std::string cppsql::Where::get_clause() const
{
    return this->clause_;
}

const std::string cppsql::Where::get_operator() const
{
    return to_s(this->operator_);
}

