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

#ifndef CPPSQL_WHERE_H
#define CPPSQL_WHERE_H
#include <string>
#include "defines.h"

#include <string>
#include <memory>
#include <defines.h>
#include <object.h>
#include <value.h>
#include <querybuilder.h>

namespace cppsql {
class QueryBuilder;

class Where {
public:
    Object* left_val_;
    Object* right_val_;
    Where* extension_;
    Where* parent_;
    Comparison comparison_;
    Operator operator_;
    bool delete_left;
    bool delete_right;

public:
    Where(std::string left_val, std::string right_val, Comparison comparison, Operator opt);
    Where(std::string left_val, QueryBuilder* right_val, Comparison comparison, Operator opt);
    Where(QueryBuilder* left_val, std::string right_val, Comparison comparison, Operator opt);
    Where(std::string left_val, std::string right_val, Where* extension, Comparison comparison,
            Operator opt);
    Where(std::string left_val, QueryBuilder* right_val, Where* extension,
            Comparison comparison,
            Operator opt);
    Where(QueryBuilder* left_val, std::string right_val, Where* extension,
            Comparison comparison,
            Operator opt);
    ~Where();
    Where(const Where& obj);
    const std::string to_string(bool with_operator = true) const;

    Operator get_operator_() const;
    const bool is_first() const;
};

}

#endif //CPPSQL_WHERE_H
