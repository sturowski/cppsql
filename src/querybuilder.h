/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>
    
    Created on 20.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
*/

#ifndef CPPSQL_QUERYBUILDER_H
#define CPPSQL_QUERYBUILDER_H

#include <iostream>
#include <string>
#include <vector>

#include "from.h"
#include "join.h"
#include "select.h"
#include "where.h"

namespace cppsql {

class QueryBuilder {
 public:
  QueryBuilder();
  QueryBuilder(const QueryBuilder &builder);
  QueryBuilder &operator=(QueryBuilder &builder);
  virtual ~QueryBuilder() {}

  QueryBuilder &select(Select select);
  QueryBuilder &select(const std::string column_name);
  QueryBuilder &select(const std::string column_name, const std::string table_name);

  QueryBuilder &from(From from);
  QueryBuilder &from(const std::string table_name);
  QueryBuilder &from(const std::string table_name, const std::string alias);

  void LeftJoin(From left_table,
                From right_table,
                const Comparison comparison);
  void RightJoin(From left_table,
                From right_table,
                const Comparison comparison);
  void InnerJoin(From left_table,
                From right_table,
                const Comparison comparison);

  QueryBuilder &where(Where where);
  QueryBuilder &where(const std::string clause, const Operator op);


  const std::string GetSelectStatement();

  bool is_empty();
  bool has_selects();
  bool has_fromClauses();
  bool has_joins();
  bool has_whereClauses();
  bool has_orderByConditions();

  const std::string create_select_string() const;
  const std::string create_from_string() const;
  const std::string create_where_string() const;

 private:
  std::vector<Select> selects_;
  std::vector<From> fromClauses_;
  std::vector<Join> joins_;
  std::vector<Where> whereClauses_;
};

}

#endif //CPPSQL_QUERYBUILDER_H
