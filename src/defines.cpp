/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>

    Created on 25.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
*/

#include "defines.h"

static const char* ComparisonNames[] = {
        "=",
        "<>",
        ">",
        "<",
        ">=",
        "<="
};

::std::string cppsql::to_s(Comparison cmp)
{
    return ComparisonNames[static_cast<int>(cmp)];
}

static const char* JoinTypeNames[] = {
        "LEFT JOIN",
        "RIGHT JOIN",
        "INNER JOIN"
};

::std::string cppsql::to_s(JoinType type)
{
    return JoinTypeNames[static_cast<int>(type)];
}

static const char* OperatorsNames[] = {
        "AND",
        "OR"
};

::std::string cppsql::to_s(Operator op)
{
    return OperatorsNames[static_cast<int>(op)];
}

#if __cplusplus>199711L
// Checks
// statically check that the size of ComparisonNames fits the number of Comparison
static_assert(sizeof(ComparisonNames)/sizeof(char*)==static_cast<int>(cppsql::Comparison::LOWER_EQUALS_THAN)+1,
        "Comparison sizes dont match");

// statically check that the size of JoinTypeNames fits the number of JoinType
static_assert(sizeof(JoinTypeNames)/sizeof(char*)==static_cast<int>(cppsql::JoinType::INNER)+1,
        "JoinType sizes dont match");

// statically check that the size of OperatorsNames fits the number of Operator
static_assert(sizeof(OperatorsNames)/sizeof(char*)==static_cast<int>(cppsql::Operator::OR)+1,
        "Operator sizes dont match");

#endif
