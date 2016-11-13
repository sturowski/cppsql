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
#include <mysqlconnection.h>
#include <iostream>
using namespace cppsql;
int main(int argc, char* argv[])
{
    try {
        MySqlConnection con;
        con.connect("192.168.178.65", "cn_adm", "", "CLUBNET", 0);
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }

//
//    if (mysql_query(con, "SELECT * FROM USERS"))
//    {
//        finish_with_error(con);
//    }
//
//    MYSQL_RES *result = mysql_store_result(con);
//
//    if (result == NULL)
//    {
//        finish_with_error(con);
//    }
//
//    int num_fields = mysql_num_fields(result);
//
//    MYSQL_ROW row;
//
//    while ((row = mysql_fetch_row(result)))
//    {
//        for(int i = 0; i < num_fields; i++)
//        {
//            printf("%s ", row[i] ? row[i] : "NULL");
//        }
//        printf("\n");
//    }
//
//    mysql_free_result(result);
//    mysql_close(con);

    exit(0);
}
