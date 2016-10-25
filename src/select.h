/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>
    
    Created on 20.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
*/

#ifndef CPPSQL_SELECT_H
#define CPPSQL_SELECT_H
#include <string>

namespace cppsql {
// This is a simple class for SqlSelects
class Select {
 public:
  Select(const std::string column_name); //for a small query without a specific table declaration
  Select(const std::string column_name,
            const std::string table_name); //for complex queries with specific table declaration

  const std::string to_string();
  const std::string to_string() const;

 private:
  const std::string create_string() const;

  std::string table_name_;
  std::string column_name_;

};

}
#endif //CPPSQL_SELECT_H
