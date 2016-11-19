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

#include <map>
#include <iostream>
#include <memory>
#include "src/defines.h"
#include "src/object.h"
#include "src/where.h"
#include "src/querybuilder.h"

using namespace cppsql;

int main(int argc, char* argv[])
{



    //AND (DATE_LAST IS NULL OR DATE_LAST = 0 OR DATE_LAST >= 20161107)
    Where test("DATE_LAST", "20161107", nullptr, Comparison::GREATER_EQUALS_THAN, Operator::OR);
    Where test1("DATE_LAST", "0", std::make_shared<Where>(test), Comparison::EQUALS, Operator::OR);
    Where test2("DATE_LAST", "", std::make_shared<Where>(test1), Comparison::IS_NULL, Operator::AND);
    std::cout << test2.to_string() << std::endl;

    //AND (ORDER_ID IN (SELECT ORDER_ID FROM SEPA_STANDIN_ODERS))
//    QueryBuilder builder;
//    builder.select("ORDER_ID").from("SEPA_STANDIN_ODERS");
//    Where test3("ORDER_ID", "", std::make_shared<QueryBuilder>(builder), Comparison::IN, Operator::AND);
//    std::cout << test3.to_string() << std::endl;
    // das geht so nicht, eine query muss ein right value sein

    //AND (DATE_END IS NULL AND (DATE_BEGIN IS NOT NULL OR TYPE = "NO_END"))
    Where test4("TYPE", "'NO_END'", nullptr, Comparison::EQUALS, Operator::OR);
    Where test5("DATE_BEGIN", "", std::make_shared<Where>(test4), Comparison::IS_NOT_NULL, Operator::AND);
    Where test6("DATE_END", "", std::make_shared<Where>(test5), Comparison::IS_NULL, Operator::AND);
    std::cout << test6.to_string() << std::endl;



}
