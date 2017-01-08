/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>
    
    Created on 24.10.16

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

#ifndef CPPSQL_ERRORS_H
#define CPPSQL_ERRORS_H
#include <exception>
#include <string>
namespace cppsql {

static const char* ErrorNames[] = {
        "All ok.",
        "Query contains no select statement.",
        "Query contains no from statement.",
        "Query contains no table for insert.",
        "Query contains no values for insert.",
        "Initialisation of SQL connection failed.",
        "Failed to connect to SQL database",
        "The query is empty.",
        "Getting error by executing the query",
        "Start transaction failed",
        "Commit transaction failed",
        "Rollback transaction failed",
        "The parsing string contains no value.",
        "The number of arguments doesn't match.",
        "Paramter index is out of range.",
        "The count of params mismatch the count of ?."
};

enum Errors {
  OK = 0,
  QUERY_CONTAINS_NO_SELECT,
  QUERY_CONTAINS_NO_FROM,
  QUERY_CONTAINS_NO_TABLE,
  QUERY_CONTAINS_NO_VALUES,
  SQL_INIT_FAILED,
  SQL_CONNECT_FAILED,
  SQL_EMPTY_QUERY,
  SQL_QUERY_FAILED,
  SQL_START_TRANSACTION_FAILED,
  SQL_COMMIT_TRANSACTION_FAILED,
  SQL_ROLLBACK_TRANSACTION_FAILED,
  PARSER_EMPTY_STRING,
  PARSER_NO_MATCHING_NUMBER_OF_ARGUMENTS,
  PARAMS_INDEX_OUT_OF_RANGE,
  PARAMS_MISMATCH_COUNT_OF_PARAMS,
  SIZE_OF_ERRORS
};

class SqlException : public std::exception {
public:
    SqlException(Errors error, const std::string error_text = "", const std::string statement = "")
            :error_(error),
             error_text_(error_text),
             statement_(statement)
    {

    }
    virtual const char* what() const throw()
    {
        if (!error_text_.empty())
            return error_text_.c_str();
        return ErrorNames[error_];
    }

    const std::string statement() const {
        return statement_;
    }

    const std::string log_entry() const {
        std::string log = "Message:"+ std::string(what());
        log += " Statement:"+statement()+"";
        return log;
    };
    const int code() const
    {
        return error_;
    }
private:
    Errors error_;
    std::string error_text_;
    std::string statement_;
};





// statically check that the size of ErrorNames fits the number of Errors
static_assert(sizeof(cppsql::ErrorNames)/sizeof(char*)==cppsql::Errors::SIZE_OF_ERRORS,
        "sql sizes dont match"); //Check for Errors and ErrorNames
}
#endif //CPPSQL_ERRORS_H
