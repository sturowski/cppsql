/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>

    Created on 25.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
*/

#ifndef CPPSQL_WHERE_H
#define CPPSQL_WHERE_H
#include <string>
#include "defines.h"

namespace cppsql {

class Where {
public:
    Where(const std::string clause, const Operator op);

    const std::string get_clause() const;
    const std::string get_operator() const;

private:
    std::string clause_;
    Operator operator_;
};

}
#endif //CPPSQL_WHERE_H
