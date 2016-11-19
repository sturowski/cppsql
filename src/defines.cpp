/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>

    Created on 25.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    As a special exception, the Contributors give you permission to link
    this library with independent modules to produce an executable,
    regardless of the license terms of these independent modules, and to
    copy and distribute the resulting executable under terms of your choice,
    provided that you also meet, for each linked independent module, the
    terms and conditions of the license of that module. An independent
    module is a module which is not derived from or based on this library.
    If you modify this library, you must extend this exception to your
    version of the library.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
    License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "defines.h"

static const char* ComparisonNames[] = {
        "=",
        "<>",
        ">",
        "<",
        ">=",
        "<=",
        "IS NULL",
        "IS NOT NULL",
        "IN"
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

// Checks
// statically check that the size of ComparisonNames fits the number of Comparison
static_assert(sizeof(ComparisonNames)/sizeof(char*)==static_cast<int>(cppsql::Comparison::IN)+1,
        "Comparison sizes dont match");

// statically check that the size of JoinTypeNames fits the number of JoinType
static_assert(sizeof(JoinTypeNames)/sizeof(char*)==static_cast<int>(cppsql::JoinType::INNER)+1,
        "JoinType sizes dont match");

// statically check that the size of OperatorsNames fits the number of Operator
static_assert(sizeof(OperatorsNames)/sizeof(char*)==static_cast<int>(cppsql::Operator::OR)+1,
        "Operator sizes dont match");
