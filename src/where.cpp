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

cppsql::Where::Where(std::string left_val, std::string right_val, Comparison comparison, Operator opt)
        :left_val_(new Value(left_val)),
         right_val_(new Value(right_val)),
         extension_(nullptr),
         comparison_(comparison),
         parent_(nullptr),
         operator_(opt),
         delete_left(true),
         delete_right(true)
{
}

cppsql::Where::Where(std::string left_val, QueryBuilder* right_val, Comparison comparison,
        cppsql::Operator opt)
        :left_val_(new Value(left_val)),
         right_val_(right_val),
         extension_(nullptr),
         comparison_(comparison),
         parent_(nullptr),
         operator_(opt),
         delete_left(true),
         delete_right(false)
{

}

cppsql::Where::Where(QueryBuilder* left_val, std::string right_val, Comparison comparison,
        cppsql::Operator opt)
        :left_val_(left_val),
         right_val_(new Value(right_val)),
         extension_(nullptr),
         comparison_(comparison),
         parent_(nullptr),
         operator_(opt),
         delete_left(false),
         delete_right(true)
{

}

cppsql::Where::Where(std::string left_val, std::string right_val, Where* extension,
        Comparison comparison,
        Operator opt)
        :left_val_(new Value(left_val)),
         right_val_(new Value(right_val)),
         extension_(extension),
         comparison_(comparison),
         parent_(nullptr),
         operator_(opt),
         delete_left(true),
         delete_right(true)
{
    int i = 0;
    if (extension_!=nullptr)
        extension_->parent_ = this;
}

cppsql::Where::Where(std::string left_val, QueryBuilder* right_val,
        Where* extension, Comparison comparison, Operator opt)
        :left_val_(new Value(left_val)),
         right_val_(right_val),
         extension_(extension),
         comparison_(comparison),
         parent_(nullptr),
         operator_(opt),
         delete_left(true),
         delete_right(false)
{
    if (extension_!=nullptr)
        extension_->parent_ = this;
};

cppsql::Where::Where(QueryBuilder* left_val, std::string right_val,
        Where* extension, Comparison comparison, Operator opt)
        :left_val_(left_val),
         right_val_(new Value(right_val)),
         extension_(extension),
         comparison_(comparison),
         parent_(nullptr),
         operator_(opt),
         delete_left(false),
         delete_right(true)
{
    if (extension_!=nullptr)
        extension_->parent_ = this;
}

const std::string cppsql::Where::to_string(bool with_operator) const
{
    std::string statement;
    if (with_operator) {
        statement += to_s(operator_);
        statement += " ";
    }

    if (extension_ && (is_first() || (operator_==AND
            && extension_->operator_==Operator::OR))) {
        statement += "(";
    }
    statement += left_val_->to_string();
    statement += " ";
    statement += to_s(comparison_);

    if (!right_val_->empty()) {
        statement += " ";
        if (comparison_==IN)
            statement += "(";
        statement += right_val_->to_string();
        if (comparison_==IN)
            statement += ")";
    }

    if (extension_!=nullptr) {
        statement += " ";
        statement += extension_->to_string();
    }
    if (!parent_ && !extension_) {
    }
    else if (parent_ && parent_->is_first() && !extension_) {
    }
    else if (!parent_ || (operator_==AND && extension_->operator_==OR)) {
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
cppsql::Where::~Where()
{
    if (delete_left && left_val_)
        delete left_val_;
    if (delete_right && right_val_)
        delete right_val_;
}
cppsql::Where::Where(const cppsql::Where& obj)
{
    this->left_val_ = obj.left_val_;
    this->right_val_ = obj.right_val_;
    this->extension_ = obj.extension_;
    this->parent_ = obj.parent_;
    this->comparison_ = obj.comparison_;
    this->operator_ = obj.operator_;
    this->delete_left = obj.delete_left;
    this->delete_right = obj.delete_right;
}


