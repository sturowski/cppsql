/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>

    Created on 25.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
*/
#ifndef CPPSQL_FROM_H
#define CPPSQL_FROM_H
#include <string>

namespace cppsql {

class From {
 public:
  From(const std::string table_name); //for a small query without a specific table declaration
  From(const std::string table_name,
          const std::string alias); //for complex queries with specific table declaration
  From(const std::string table_name,
          const std::string alias,
          const std::string join_column); //for complex queries with joins

  const std::string to_string();
  const std::string to_string() const;

  const std::string get_table_name() const;
  const std::string get_alias() const;
  const std::string get_join_column() const;

 private:
  const std::string create_string() const;

  std::string table_name_;
  std::string alias_;
  std::string join_column_;

};

}

#endif //CPPSQL_FROM_H
