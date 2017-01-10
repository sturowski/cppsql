/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>

    Created on 09.01.17

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

#include "Set.h"

Set::Set(const std::string column, const std::string value) :
        column_(column),
        value_(value) {
}

const std::string Set::to_string() {
    return create_string();
}

const std::string Set::to_string() const {
    return create_string();
}

const std::string Set::create_string() const {
    std::string statement;
    statement += column_;
    statement += " = ";
    statement += value_;
    return statement;
}
