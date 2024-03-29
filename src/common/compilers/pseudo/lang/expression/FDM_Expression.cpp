#include <iostream>
#include "FDM_Expression.hpp"

using namespace FDM_Expressions;

Expression *Expression::Interprete() {
    return new TerminalExpression(to_string(true));
}

Expression *Expression::GoDown(Expression *expression) {
    Expression *result = expression;
    while(!result->isTerminal())
        result = result->Interprete();
    return result;
}

bool Expression::isTerminal () {
    return false;
}

void Expression::AddExpression(Expression *expression) {}

TerminalExpression::TerminalExpression(string data) {
    this->data = data;
}

bool TerminalExpression::isTerminal () {
    return true;
}

Expression *TerminalExpression::Interprete() {
    return new NullExpression();
}

NullExpression::NullExpression() : TerminalExpression("NULL") {}

Expression *NullExpression::Interprete() {
    return NULL;
}

TernaryExpression::TernaryExpression(Expression *expr1, Expression *expr2, Expression *expr3) {
    this->expr1 = expr1;
    this->expr2 = expr2;
    this->expr3 = expr3;
}


void TernaryExpression::AddExpression(Expression *expression) {
    if(this->expr1 == NULL)
        this->expr1 = expression;
    else if(this->expr2 == NULL)
        this->expr2 = expression;
    else
        this->expr3 = expression;
}

Expression *TernaryExpression::Interprete() {
    this->expr1 = GoDown(this->expr1);
    this->expr2 = GoDown(this->expr2);
    this->expr3 = GoDown(this->expr3);
}

BinaryExpression::BinaryExpression(Expression *expr1, Expression *expr2) {
    this->expr1 = expr1;
    this->expr2 = expr2;
}


void BinaryExpression::AddExpression(Expression *expression) {
    if(this->expr1 == NULL)
        this->expr1 = expression;
    else
        this->expr2 = expression;
}

Expression *BinaryExpression::Interprete() {
    this->expr1 = GoDown(this->expr1);
    this->expr2 = GoDown(this->expr2);
}

UnitaryExpression::UnitaryExpression(Expression *expression) {
    this->expression = expression;
}


void UnitaryExpression::AddExpression(Expression *expression) {
    this->expression = expression;
}

Expression *UnitaryExpression::Interprete() {
    this->expression = GoDown(this->expression);
}