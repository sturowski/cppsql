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
#include <Defines.h>
#include <Where.h>
#include <MysqlConnection.h>
#include <Errors.h>

using namespace cppsql;



int main(int argc, char* argv[])
{
    MySqlConnection connection;
    connection.connect("127.0.0.1", "root", "root", "CLUBNET", 3306);
    Params params;
    params.clear();
    params.add_param("10002");
    params.add_param("test@test.de");

    cppsql::Query statement;
    statement.delete_from("TOKEN")
            .and_where("MSG_TYPE", cppsql::EQUALS, "?")
            .and_where("MAIL_ADDRESS", cppsql::EQUALS, "?");

    std::cout << statement.statement(params) << "\n";
    //connection.query(statement.statement(params));

    params.clear();
    params.add_param("123");
    params.add_param("20160107");
    params.add_param("10002");
    params.add_param("test@test.de");
    params.add_param("");
    cppsql::Query statement2;
    statement2.insert_into("TOKEN").columns("TOKEN", "CREATE_DATE", "MSG_TYPE", "MAIL_ADDRESS", "DATA");

    try {
        std::cout << statement2.statement(params) << "\n";
        connection.query(statement2.statement(params));
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

//    Query statement;
//    statement.select("U.USER_ID", "U.SALT", "U.PASSWORD", "U.AVAILABLE_LOGINS")
//            .from("USER U", "PERSON P")
//            .and_where("U.PERSON_ID", EQUALS, "P.PERSON_ID")
//            .and_where("P.EMAIL", EQUALS, "?");
//    Params params;
//    params.add_param("test@test.de");
//
//    MySqlConnection connection;
//    connection.connect("127.0.0.1", "root", "root", "CLUBNET", 3306);
//
//    Table table = connection.query(statement.statement(params));
//
//    for(auto row : table.rows()) {
//        std::cout << row.to_string() << "\n";
//    }



//    SELECT U.USER_ID, U.SALT, U.PASSWORD, U.AVAILABLE_LOGINS
//    FROM USER U, PERSON P
//    WHERE U.PERSON_ID = P.PERSON_ID
//    AND P.EMAIL = 'test@test.de';


//    Query statement;
//    statement.select_distinct("O.ORDER_ID AS ID", "O.USER_ID", "U.USER_ID")
//            .from("ORDER O", "USER U")
//            .and_where("O.ORDER_ID", EQUALS, "?")
//            .and_where("O.BANK_ID", EQUALS, "?");
//    Where where1("TYPE", Comparison::EQUALS, "?", Operator::OR);
//    Where where2("DATE_BEGIN", Comparison::IS_NOT_NULL, "", where1, Operator::AND);
//    statement.and_where("DATE_END", Comparison::IS_NULL, "", where2);
//
//    Params para;
//    para.add_param("12345678");
//    para.add_param("25400011");
//    para.add_param("NO_END");
//    std::cout << statement.statement(para) << "\n";
//
//    para.clear();
//    para.add_param("45678903");
//    para.add_param("25400011");
//    para.add_param("NO_END");
//    std::cout << statement.statement(para) << "\n";
//
//    Query insert;
//    insert.insert_into("ORDER").columns("ORDER_ID", "ORDER_NAME");
//    std::cout << insert.statement(para) << "\n";
//
//    Query insert2;
//    insert2.insert_into("ORDER");
//    std::cout << insert2.statement(para) << "\n";


//    //AND (DATE_LAST IS NULL OR DATE_LAST = 0 OR DATE_LAST >= 20161107)
//    Where test("DATE_LAST", "20161107", Comparison::GREATER_EQUALS_THAN, Operator::OR);
//    Where test1("DATE_LAST", "0", test, Comparison::EQUALS, Operator::OR);
//    Where test2("DATE_LAST", "", test, Comparison::IS_NULL, Operator::AND);
//    std::cout << test2.to_string() << std::endl;
//
//    //AND (ORDER_ID IN (SELECT ORDER_ID FROM SEPA_STANDIN_ODERS))
//    Query query;
//    query.select("ORDER_ID").from("SEPA_STANDIN_ODERS");
//    Where test3("ORDER_ID", query, Comparison::IN, Operator::AND);
//    std::cout << test3.to_string() << std::endl;
//
//    //AND (DATE_END IS NULL AND (DATE_BEGIN IS NOT NULL OR TYPE = "NO_END"))
//    Where test4("TYPE", "'NO_END'", Comparison::EQUALS, Operator::OR);
//    Where test5("DATE_BEGIN", "", test4, Comparison::IS_NOT_NULL, Operator::AND);
//    Where test6("DATE_END", "", test5, Comparison::IS_NULL, Operator::AND);
//    std::cout << test6.to_string() << std::endl;


}
