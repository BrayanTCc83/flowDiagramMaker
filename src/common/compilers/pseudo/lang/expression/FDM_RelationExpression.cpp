#include "FDM_Expression.hpp"

using namespace FDM_Expressions;

GreaterThanExpression::GreaterThanExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = (string)*expr1 + " > " + (string)*expr2;
}

Expression *GreaterThanExpression::Interprete() {
    BinaryExpression::Interprete();
    return new TerminalExpression(to_string((double)*this->expr1 > (double)*this->expr2));
}

LessThanExpression::LessThanExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = (string)*expr1 + " < " + (string)*expr2;
}

Expression *LessThanExpression::Interprete() {
    BinaryExpression::Interprete();
    return new TerminalExpression(to_string((double)*this->expr1 < (double)*this->expr2));
}

EqualsToExpression::EqualsToExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = (string)*expr1 + " == " + (string)*expr2;
}

Expression *EqualsToExpression::Interprete() {
    BinaryExpression::Interprete();
    return new TerminalExpression(to_string((double)*this->expr1 == (double)*this->expr2));
}

DifferentToExpression::DifferentToExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = (string)*expr1 + " != " + (string)*expr2;
}

Expression *DifferentToExpression::Interprete() {
    BinaryExpression::Interprete();
    return new TerminalExpression(to_string((double)*this->expr1 != (double)*this->expr2));
}

GreaterEqualsExpression::GreaterEqualsExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = (string)*expr1 + " >= " + (string)*expr2;
}

Expression *GreaterEqualsExpression::Interprete() {
    BinaryExpression::Interprete();
    return new TerminalExpression(to_string((double)*this->expr1 >= (double)*this->expr2));
}

LessEqualsExpression::LessEqualsExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = (string)*expr1 + " <= " + (string)*expr2;
}

Expression *LessEqualsExpression::Interprete() {
    BinaryExpression::Interprete();
    return new TerminalExpression(to_string((double)*this->expr1 <= (double)*this->expr2));
}