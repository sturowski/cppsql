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

#include "mysqlconnection.h"
#include <errors.h>
/**
 * The basic contructor, will initialize this MySql connection.
 * If the mysql_init fails and con will be nullpr it throws an exception.
 * @throw SqlException SQL_INIT_FAILED
 * @return
 */
cppsql::MySqlConnection::MySqlConnection() throw()
        :con_(nullptr)
{
    con_ = mysql_init(nullptr);
    if (con_==nullptr) {
        throw SqlException(Errors::SQL_INIT_FAILED);
    }
}
cppsql::MySqlConnection::~MySqlConnection()
{

}
void cppsql::MySqlConnection::connect(const std::string host, const std::string user, const std::string password,
        const std::string database, const int port) throw()
{
    // Call the parent function
    Connection::connect(host, user, password, database, port);
    if (mysql_real_connect(con_, host_.c_str(), user_.c_str(), password_.c_str(),
            database_.c_str(), port, NULL, 0)==NULL) {
        // First close the connection to free the pointer, then throw the exception
        close();
        std::string test(mysql_error(con_));
        throw SqlException(Errors::SQL_CONNECT_FAILED, test);
    }

}
void cppsql::MySqlConnection::close()
{
    mysql_close(con_);
}
void cppsql::MySqlConnection::single_query(const std::string query) throw()
{

}
