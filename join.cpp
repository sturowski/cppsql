/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>

    Created on 25.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
*/

#include "join.h"

cppsql::Join::Join(From left_table,
        From right_table,
        const JoinType type,
        const Comparison comparison)
        :
        left_table_(left_table),
        right_table_(right_table),
        type_(type),
        comparison_(comparison) { }

const std::string cppsql::Join::GetJoinStatement() const
{
    std::string statement = "(";
    statement += left_table_.get_table_name()+" "+left_table_.get_alias()
            +" "; // Adding the first element of the join
    statement += to_s(type_)+" ";
    statement += right_table_.get_table_name()+" "+right_table_.get_alias()
            +" "; // Adding the second element of the join
    statement += "on "+left_table_.get_join_column()+" "
            +to_s(comparison_)+" "+right_table_.get_join_column();
    statement += ")";

    return statement;
}
