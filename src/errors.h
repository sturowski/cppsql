/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>
    
    Created on 24.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
*/

#ifndef CPPSQL_ERRORS_H
#define CPPSQL_ERRORS_H

namespace cppsql {

enum Errors {
  OK = 0,
  QUERY_CONTAINS_NO_SELECT,
  QUERY_CONTAINS_NO_FROM,
  SIZE_OF_ERRORS
};

static const char* ErrorNames[] = {
        "All ok.",
        "Query contains no select statement.",
        "Query contains no from statement."
};

// statically check that the size of ErrorNames fits the number of Errors
static_assert(sizeof(cppsql::ErrorNames)/sizeof(char*)==cppsql::Errors::SIZE_OF_ERRORS,
        "sql sizes dont match"); //Check for Errors and ErrorNames
}
#endif //CPPSQL_ERRORS_H
