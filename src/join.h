/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>

    Created on 25.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
*/
#ifndef CPPSQL_JOIN_H
#define CPPSQL_JOIN_H

#include <string>
#include "defines.h"
#include "from.h"

namespace cppsql {

class Join {
public:

    Join(From left_table,
            From right_table,
            const JoinType type,
            const Comparison comparison);

    const std::string GetJoinStatement() const;

private:
    From left_table_;
    From right_table_;
    JoinType type_;
    Comparison comparison_;
};

}
#endif //CPPSQL_JOIN_H
