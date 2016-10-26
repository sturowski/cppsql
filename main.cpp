/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>
    
    Created on 20.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY;
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
        sqb.from("CUSTOMER", "C").from("PERSON", "P");
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
