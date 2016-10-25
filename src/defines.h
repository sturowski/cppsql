/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>

    Created on 25.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
*/
#ifndef CPPSQL_DEFINES_H
#define CPPSQL_DEFINES_H

namespace cppsql {

enum Comparison {
  EQUALS = 0,
  NOT_EQUALS,
  GREATER_THAN,
  LOWER_THAN,
  GREATER_EQUALS_THAN,
  LOWER_EQUALS_THAN,
  SIZE_OF_COMPARISON
};

enum JoinType {
  LEFT = 0,
  RIGHT,
  INNER,
  SIZE_OF_JOIN_TYPE
};

enum Operator {
  AND = 0,
  OR,
  SIZE_OF_OPERATORS
};

static const char *ComparisonNames[] = {
    "=",
    "<>",
    ">",
    "<",
    ">=",
    "<="

};

static const char *JoinTypeNames[] = {
    "LEFT JOIN",
    "RIGHT JOIN",
    "INNER JOIN"
};

static const char *OperatorsNames[] = {
    "AND",
    "OR"
};

// Checks
// statically check that the size of ComparisonNames fits the number of Comparison
static_assert(sizeof(ComparisonNames) / sizeof(char *) == Comparison::SIZE_OF_COMPARISON,
              "Comparison sizes dont match");

// statically check that the size of JoinTypeNames fits the number of JoinType
static_assert(sizeof(JoinTypeNames) / sizeof(char *) == JoinType::SIZE_OF_JOIN_TYPE,
              "JoinType sizes dont match");

// statically check that the size of OperatorsNames fits the number of Operator
static_assert(sizeof(OperatorsNames) / sizeof(char *) == Operator::SIZE_OF_OPERATORS,
              "Operator sizes dont match");
}

#endif //CPPSQL_DEFINES_H
