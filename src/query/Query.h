/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>
    
    Created on 20.10.16

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

#ifndef CPPSQL_QUERYBUILDER_H
#define CPPSQL_QUERYBUILDER_H

#include <iostream>
#include <string>
#include <vector>
#include <SelectParser.h>
#include <FromParser.h>

#include "From.h"
#include "Join.h"
#include "Select.h"
#include "Where.h"
#include "Object.h"
#include "Params.h"
#include "Set.h"

namespace cppsql {
class Where;

class Query : public Object{
public:
    Query();
    Query(const Query& builder);
    Query& operator=(Query& builder);
    virtual ~Query() { }

    template<typename Type, typename = std::enable_if_t<std::is_class<std::string>::value>>
    Query& select(Type statement)
    {
        selects_.push_back(SelectParser::parse(statement));
        set_type(TYPE::SELECT);
        return *this;
    }
    template<typename Type, typename ... Types>
    Query& select(Type statement, Types ... rest)
    {
        selects_.push_back(SelectParser::parse(statement));
        return select(rest...);
    }

    template<typename Type, typename = std::enable_if_t<std::is_class<std::string>::value>>
    Query& select_distinct(Type statement)
    {
        selects_.push_back(SelectParser::parse(statement));
        distinct_ = true;
        set_type(TYPE::SELECT);
        return *this;
    }
    template<typename Type, typename ... Types>
    Query& select_distinct(Type statement, Types ... rest)
    {
        selects_.push_back(SelectParser::parse(statement));
        return select_distinct(rest...);
    }

    template<typename Type, typename = std::enable_if_t<std::is_class<std::string>::value>>
    Query& from(Type statement)
    {
        fromClauses_.push_back(FromParser::parse(statement));
        return *this;
    }
    template<typename Type, typename ... Types>
    Query& from(Type statement, Types ... rest)
    {
        fromClauses_.push_back(FromParser::parse(statement));
        return from(rest...);
    }

    template<typename Type, typename = std::enable_if_t<std::is_class<std::string>::value>>
    Query& columns(Type statement)
    {
        columns_.push_back(statement);
        return *this;
    }
    template<typename Type, typename ... Types>
    Query& columns(Type statement, Types ... rest)
    {
        columns_.push_back(statement);
        return columns(rest...);
    }

    void left_join(From left_table, From right_table, const Comparison comparison);
    void right_join(From left_table, From right_table, const Comparison comparison);
    void inner_join(From left_table, From right_table, const Comparison comparison);

    Query& where(Where where);
    Query& and_where(std::string left_val, Comparison comparison, std::string right_val);
    Query& and_where(std::string left_val, Comparison comparison, Query& right_val);
    Query& and_where(Query& left_val, Comparison comparison, std::string right_val);
    Query& and_where(std::string left_val, Comparison comparison, std::string right_val, Where& extension);
    Query& and_where(std::string left_val, Comparison comparison, Query& right_val, Where& extension);
    Query& and_where(Query& left_val, Comparison comparison, std::string right_val, Where& extension);
    Query& or_where(std::string left_val, Comparison comparison, std::string right_val);
    Query& or_where(std::string left_val, Comparison comparison, Query& right_val);
    Query& or_where(Query& left_val, Comparison comparison, std::string right_val);
    Query& or_where(std::string left_val, Comparison comparison, std::string right_val, Where& extension);
    Query& or_where(std::string left_val, Comparison comparison, Query& right_val, Where& extension);
    Query& or_where(Query& left_val, Comparison comparison, std::string right_val, Where& extension);

    Query& insert_into(const std::string table);
    Query& delete_from(const std::string table);
    Query& update(const std::string table);

    Query& set(const std::string column, const std::string value);


    const std::string statement(Params params = Params()) const throw();

    virtual const bool empty() const override;
    virtual const std::string to_string() const override;
    const bool is_distinct() const;
    const bool has_selects() const;
    const bool has_from_clauses() const;
    const bool has_joins() const;
    const bool has_where_clauses() const;
    const bool has_table() const;
    const bool has_columns() const;
    const bool has_sets() const;
private:
    enum class TYPE {
        NO,
        SELECT,
        INSERT,
        DELETE,
        UPDATE
    };

    TYPE type_;
    bool distinct_;

    std::string table_;
    std::vector<Select> selects_;
    std::vector<From> fromClauses_;
    std::vector<Join> joins_;
    std::vector<Where> whereClauses_;
    std::vector<std::string> columns_;
    std::vector<Set> sets_;

    void set_type(TYPE type);

    const std::string create_select_statement(Params& params) const;
    const std::string create_insert_statement(Params& params) const;
    const std::string create_delete_statement(Params& params) const;
    const std::string create_update_statement(Params& params) const;
    const void replace_params(std::string& statement, Params& params) const throw();
    const std::string create_select_string() const;
    const std::string create_from_string() const;
    const std::string create_where_string() const;
    const std::string create_column_string() const;
};

}

#endif //CPPSQL_QUERYBUILDER_H
