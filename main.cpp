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

#include "src/querybuilder.h"

using namespace cppsql;

int main(int argc, char* argv[])
{
    try {
        QueryBuilder sqb;
        sqb.select("COUNTRY_CODE", "C").select("BANK_CODE", "C").select("CUSTOMER_ID", "C").select("SUBCLIENT", "C")
                .select("BLOCKED", "C").select("NAME1", "P").select("NAME2", "P").select("TITLE", "P").select("SEX",
                        "P")
                .select("DATE_OF_BIRTH", "P");
        sqb.select("PHONE", "PH");
        sqb.from("CUSTOMER", "C");
        sqb.leftJoin(From("PERSON", "P", "PERSON_ID"), From("PHONE", "PH", "PERSON_ID"), Comparison::EQUALS);
        sqb.where("C.PERSON_ID = P.PERSON_ID", Operator::AND)
                .where("C.CUSTOMER_ID like ?", Operator::AND)
                .where("C.CLIENT = ?", Operator::AND)
                .where("C.COUNTRY_CODE like ?", Operator::AND)
                .where("C.BANK_CODE like ?", Operator::AND)
                .where("C.PERSON_ID like ?", Operator::AND)
                .where("(P.NAME1 is null or upper(P.NAME1) like ?)", Operator::AND)
                .where("(P.NAME2 is null or upper(P.NAME2) like ?)", Operator::AND);

        std::cout << sqb.GetSelectStatement() << std::endl;

    }
    catch (char const* msg) {
        std::cerr << msg << std::endl;
    }

}
