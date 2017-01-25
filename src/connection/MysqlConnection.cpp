/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>
    
    Created on 13.11.16

    This file is part of tools, a C++ collection.

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

#include "MysqlConnection.h"
#include "Errors.h"
/**
 * The basic contructor, will initialize this MySql connection.
 * If the mysql_init fails and con will be nullpr it throws an exception.
 * @throw SqlException SQL_INIT_FAILED
 * @return
 */
cppsql::MySqlConnection::MySqlConnection() throw(cppsql::SqlException)
        :con_(nullptr)
{

}
cppsql::MySqlConnection::~MySqlConnection()
{
    close();
}
void cppsql::MySqlConnection::connect(const std::string host, const std::string user, const std::string password,
        const std::string database, const int port) throw(cppsql::SqlException)
{
    con_ = mysql_init(nullptr);
    if (con_==nullptr) {
        throw SqlException(Errors::SQL_INIT_FAILED);
    }
    // Call the parent function
    Connection::connect(host, user, password, database, port);
    if (mysql_real_connect(con_, host_.c_str(), user_.c_str(), password_.c_str(),
            database_.c_str(), port, NULL, 0)==NULL) {
        // First close the connection to free the pointer, then throw the exception
        close();
        throw SqlException(Errors::SQL_CONNECT_FAILED, mysql_error(con_));
    }

}
void cppsql::MySqlConnection::close()
{
    if (con_!=nullptr)
        mysql_close(con_);
}
cppsql::Table cppsql::MySqlConnection::query(const std::string query) throw(cppsql::SqlException)
{
    if (query.empty())
        throw SqlException(Errors::SQL_EMPTY_QUERY);

    if (mysql_query(con_, query.c_str())) {
        throw SqlException(Errors::SQL_QUERY_FAILED, mysql_error(con_), query);
    }

    if (query.find("INSERT")!=std::string::npos
        || query.find("DELETE")!=std::string::npos
        || query.find("UPDATE")!=std::string::npos)
        return Table(mysql_affected_rows(con_));

    MYSQL_RES* result = mysql_store_result(con_);

    if (result==NULL) {
        mysql_free_result(result);
        throw SqlException(Errors::SQL_QUERY_FAILED, mysql_error(con_), query);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW my_row;

    Table table;
    while ((my_row = mysql_fetch_row(result))) {
        Row row;
        for (int i = 0; i<num_fields; i++) {
            char* value = my_row[i];
            if(value == nullptr) {
                row.add_column("");
                continue;
            }
            row.add_column(value);
        }
        table.add_row(row);
    }
    mysql_free_result(result);
    return table;
}
void cppsql::MySqlConnection::start_transaction() throw(cppsql::SqlException)
{
    if (mysql_autocommit(con_, 0))
        throw SqlException(Errors::SQL_START_TRANSACTION_FAILED, mysql_error(con_));
}
void cppsql::MySqlConnection::commit() throw(cppsql::SqlException)
{
    if (mysql_commit(con_))
        throw SqlException(Errors::SQL_COMMIT_TRANSACTION_FAILED, mysql_error(con_));
    if (mysql_autocommit(con_, 1))
        throw SqlException(Errors::SQL_COMMIT_TRANSACTION_FAILED, mysql_error(con_));
}
void cppsql::MySqlConnection::rollback() throw(cppsql::SqlException)
{
    if (mysql_rollback(con_))
        throw SqlException(Errors::SQL_ROLLBACK_TRANSACTION_FAILED, mysql_error(con_));
    if (mysql_autocommit(con_, 1))
        throw SqlException(Errors::SQL_ROLLBACK_TRANSACTION_FAILED, mysql_error(con_));
}
