/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>

    Created on 25.10.16

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

#include "where.h"

cppsql::Where::Where(std::string left_val, std::string right_val, std::shared_ptr<Object> extension_,
        Comparison comparison,
        Operator opt)
        :left_val_(left_val),
         right_val_(right_val),
         extension_(extension_),
         comparison_(comparison),
         Object(opt)
{
    if (extension_!=nullptr)
        extension_->parent_ = std::make_shared<Object>(*this);
};

const std::string cppsql::Where::to_string()
{
    std::string statement;
    statement += to_s(operator_);
    statement += " ";

    if (is_first() || (operator_==Operator::AND
            && extension_->operator_==Operator::OR)) { //hier gehts weiter mit get_operator...
        statement += "(";
    }
    statement += left_val_;
    statement += " ";
    statement += to_s(comparison_);
    if (!right_val_.empty()) {
        statement += " ";
        statement += right_val_;
    }

    if (extension_!=nullptr) {
        statement += " ";
        statement += extension_->to_string();
    }
    if (!parent_ || (operator_==Operator::OR && parent_ && parent_->operator_==Operator::AND)) {
        statement += ")";
    }

    return statement;
}
const bool cppsql::Where::is_first() const { return this->extension_ && !this->parent_; }
cppsql::Operator cppsql::Where::get_operator_() const
{
    return operator_;
};

