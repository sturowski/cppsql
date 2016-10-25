/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>

    Created on 25.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
*/
#include "join.h"
using namespace cppsql;

Join::Join(From left_table,
                 From right_table,
                 const JoinType type,
                 const Comparison comparison) :
    left_table_(left_table),
    right_table_(right_table),
    type_(type),
    comparison_(comparison) {

}
const std::string Join::GetJoinStatement() const {
  std::string statement;
  statement += this->left_table_.get_table_name() + " " + this->left_table_.get_alias()
      + " "; // Adding the first element of the join
  statement += std::string(JoinTypeNames[this->type_]) + " ";
  statement += this->right_table_.get_table_name() + " " + this->right_table_.get_alias()
      + " "; // Adding the second element of the join
  statement += "on " + this->left_table_.get_join_column() + " "
      + std::string(ComparisonNames[this->comparison_]) + " " + this->right_table_.get_join_column();

  return statement;
}
