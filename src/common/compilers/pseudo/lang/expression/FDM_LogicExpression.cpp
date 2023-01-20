#include "FDM_Expression.hpp"

using namespace FDM_Expressions;

AndExpression::AndExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = (string)*expr1 + " && " + (string)*expr2;
}

Expression *AndExpression::Interprete() {
    bool result = ((bool)*this->expr1) && ((bool)*this->expr2);
    return new TerminalExpression(to_string(result));
}

OrExpression::OrExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = (string)*expr1 + " || " + (string)*expr2;
}

Expression *OrExpression::Interprete() {
    bool result = ((bool)*this->expr1) || ((bool)*this->expr2);
    return new TerminalExpression(to_string(result));
}

XorExpression::XorExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = (string)*expr1 + " XOR " + (string)*expr2;
}

Expression *XorExpression::Interprete() {
    bool result = (((bool)*this->expr1) && !((bool)*this->expr2)) || 
                    (((bool)*this->expr2) && !((bool)*this->expr1));
    return new TerminalExpression(to_string(result));
}

NotExpression::NotExpression(Expression *expression) : UnitaryExpression(expression) {
    this->data = " ! " + (string)*expression;
}

Expression *NotExpression::Interprete() {
    bool result = !((bool)*this->expression);
    return new TerminalExpression(to_string(result));
}