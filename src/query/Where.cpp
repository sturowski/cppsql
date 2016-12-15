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

#include "Where.h"

cppsql::Where::Where(std::string left_val, Comparison comparison, std::string right_val, Operator opt)
        :left_val_(std::make_shared<Value>(left_val)),
         right_val_(std::make_shared<Value>(right_val)),
         comparison_(comparison),
         parent_(nullptr),
         operator_(opt)
{
}

cppsql::Where::Where(std::string left_val, Comparison comparison, Query& right_val, cppsql::Operator opt)
        :left_val_(std::make_shared<Value>(left_val)),
         right_val_(std::make_shared<Query>(right_val)),
         comparison_(comparison),
         parent_(nullptr),
         operator_(opt)
{

}

cppsql::Where::Where(Query& left_val, Comparison comparison, std::string right_val, cppsql::Operator opt)
        :left_val_(std::make_shared<Query>(left_val)),
         right_val_(std::make_shared<Value>(right_val)),
         comparison_(comparison),
         parent_(nullptr),
         operator_(opt)
{

}

cppsql::Where::Where(std::string left_val, Comparison comparison, std::string right_val, Where& extension,
        Operator opt)
        :left_val_(std::make_shared<Value>(left_val)),
         right_val_(std::make_shared<Value>(right_val)),
         extension_(std::make_shared<Where>(extension)),
         comparison_(comparison),
         parent_(nullptr),
         operator_(opt)
{
    int i = 0;
    if (extension_!=nullptr)
        extension_->parent_ = std::make_shared<Where>(*this);
}

cppsql::Where::Where(std::string left_val, Comparison comparison, Query& right_val,
        Where& extension, Operator opt)
        :left_val_(std::make_shared<Value>(left_val)),
         right_val_(std::make_shared<Query>(right_val)),
         extension_(std::make_shared<Where>(extension)),
         comparison_(comparison),
         parent_(nullptr),
         operator_(opt)
{
    if (extension_!=nullptr)
        extension_->parent_ = std::make_shared<Where>(*this);
};

cppsql::Where::Where(Query& left_val, Comparison comparison, std::string right_val,
        Where& extension, Operator opt)
        :left_val_(std::make_shared<Query>(left_val)),
         right_val_(std::make_shared<Value>(right_val)),
         extension_(std::make_shared<Where>(extension)),
         comparison_(comparison),
         parent_(nullptr),
         operator_(opt)
{
    if (extension_!=nullptr)
        extension_->parent_ = std::make_shared<Where>(*this);
}

const std::string cppsql::Where::to_string(bool with_operator) const
{
    std::string statement;
    if (with_operator) {
        statement += to_s(operator_);
        statement += " ";
    }

    if (extension_ && (is_first() || (operator_==Operator::AND
            && extension_->operator_==Operator::OR))) {
        statement += "(";
    }
    statement += left_val_->to_string();
    statement += " ";
    statement += to_s(comparison_);

    if (!right_val_->empty()) {
        statement += " ";
        if (comparison_==Comparison::IN)
            statement += "(";
        statement += right_val_->to_string();
        if (comparison_==Comparison::IN)
            statement += ")";
    }

    if (extension_!=nullptr) {
        statement += " ";
        statement += extension_->to_string();
    }
    if (!parent_ && !extension_) {
    }
    else if(parent_ && parent_->is_first() && !extension_) {
    }
    else if (!parent_ || (operator_==Operator::AND && extension_->operator_==Operator::OR)) {
        statement += ")";
    }

    return statement;
}

const bool cppsql::Where::is_first() const
{
    return !parent_;
}

cppsql::Operator cppsql::Where::get_operator_() const
{
    return operator_;
}











