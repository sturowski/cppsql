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
#include <string>
#include "src/querybuilder.h"
#include "src/resourcemanager.h"

using namespace cppsql;




std::map<int, QueryBuilder*> queryCache;
QueryBuilder* findQueryInCache(const int stmtNr)
{
    std::map<int, QueryBuilder*>::iterator it = queryCache.find(stmtNr);
    if (it==queryCache.end()) {
        queryCache[stmtNr] = static_cast<QueryBuilder*>(new QueryBuilder());
        return queryCache[stmtNr];
    }
    return it->second;
}
int main(int argc, char* argv[])
{
    QueryBuilder* qb1 = findQueryInCache(1);
    qb1->select("Test");

    QueryBuilder* qb2 = findQueryInCache(1);
    std::cout << "has selects: " << qb2->has_selects() << std::endl;

    ResourceManager<int, QueryBuilder> rm;
    const int i = 1;
    QueryBuilder& qb = rm.get_resource(i);
    qb.select("Hallo");

    std::cout << "rm has_selects: " << qb.has_selects() << std::endl;
    std::cout << "our resource has_selects: " << rm.get_resource(1).has_selects();
}

/*
 * std::map<int, DBStatement*> queryCache;
 * DBStatement* findQueryInCache(const int stmtNr);
 * DBStatement*
SearchUser::findQueryInCache(const int stmtNr) {
    std::map<int, DBStatement*>::iterator it = queryCache.find(stmtNr);
    if (it == queryCache.end()) {
        queryCache[stmtNr] = static_cast<DBStatement*>(con.getStatement(getSelectCustomersStmt(stmtNr)).clone());
        return queryCache[stmtNr];
    }
    return it->second;
}
 *
 *
 */