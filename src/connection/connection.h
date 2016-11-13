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

#ifndef CPPSQL_CONNECTION_H
#define CPPSQL_CONNECTION_H
#include <string>

namespace cppsql {

class Connection {
public:
    Connection() throw() { };
    virtual ~Connection() { };

    virtual void connect(const std::string host, const std::string user, const std::string password,
            const std::string database,
            const int port) throw();

    virtual void close()=0;
    virtual void single_query(const std::string query) throw() =0;

protected:
    std::string host_;
    std::string user_;
    std::string password_;
    std::string database_;
    int port;
};

}

#endif //CPPSQL_CONNECTION_H
