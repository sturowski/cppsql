/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>

    Created on 25.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
*/
#ifndef CPPSQL_DEFINES_H
#define CPPSQL_DEFINES_H

#include <string>

namespace cppsql {

enum Comparison {
  EQUALS = 0,
  NOT_EQUALS,
  GREATER_THAN,
  LOWER_THAN,
  GREATER_EQUALS_THAN,
  LOWER_EQUALS_THAN
};
::std::string to_s(Comparison);

enum JoinType {
  LEFT = 0,
  RIGHT,
  INNER
};
::std::string to_s(JoinType);

enum Operator {
  AND = 0,
  OR
};
::std::string to_s(Operator);

};

#endif //CPPSQL_DEFINES_H
