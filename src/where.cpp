/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>

    Created on 25.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
*/

#include "where.h"
using namespace cppsql;

Where::Where(const std::string clause, const Operator op) :
    clause_(clause),
    operator_(op) {
}

const std::string Where::get_clause() const {
  return this->clause_;
}

const std::string Where::get_operator() const {
  return OperatorsNames[this->operator_];
}

