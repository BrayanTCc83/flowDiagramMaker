#include "FDM_Expression.hpp"

using namespace FDM_Expressions;

AsignationExpression::AsignationExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = (string)*expr1 + " = " + (string)*expr2;
}

Expression *AsignationExpression::Interprete() {
    if(!expr1->isTerminal())
        throw NoTerminalExpressionException();

    Expression *expression = GoDown(expr2);
    this->expr1->data = expression->data;
    return new TerminalExpression("Instruction end");
}

IncresseExpression::IncresseExpression(Expression *expression) : UnitaryExpression(expression) {
    this->data = (string)*expression + "++";
}

Expression *IncresseExpression::Interprete() {
    if(!expression->isTerminal())
        throw NoTerminalExpressionException();

    int value = (int)*expression;
    expression->data = to_string(++value);
    return new NullExpression();
}

DecresseExpression::DecresseExpression(Expression *expression) : UnitaryExpression(expression) {
    this->data = (string)*expression + "--";
}

Expression *DecresseExpression::Interprete() {
    if(!expression->isTerminal())
        throw NoTerminalExpressionException();
    
    int value = (int)*expression;
    expression->data = to_string(--value);
    return new NullExpression();
}

AditionExpression::AditionExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = "(" + (string)*expr1 + " + " + (string)*expr2 + ")";
}

Expression *AditionExpression::Interprete() {
    BinaryExpression::Interprete();
    double result = (double)*this->expr1 + (double)*this->expr2;
    return new TerminalExpression(to_string(result));
}

SubstractionExpression::SubstractionExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = "(" + (string)*expr1 + " - " + (string)*expr2 + ")";
}

Expression *SubstractionExpression::Interprete() {
    BinaryExpression::Interprete();
    double result = (double)*this->expr1 - (double)*this->expr2;
    return new TerminalExpression(to_string(result));
}

MultiplicationExpression::MultiplicationExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = "(" + (string)*expr1 + " * " + (string)*expr2 + ")";
}

Expression *MultiplicationExpression::Interprete() {
    BinaryExpression::Interprete();
    double result = (double)*this->expr1 * (double)*this->expr2;
    return new TerminalExpression(to_string(result));
}

DivisionExpression::DivisionExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = "(" + (string)*expr1 + " / " + (string)*expr2 + ")";
}

Expression *DivisionExpression::Interprete() {
    BinaryExpression::Interprete();
    double a = (double)*this->expr1, b = (double)*this->expr2;
    if(b == 0)
        throw DivisionZeroException();

    return new TerminalExpression(to_string(a/b));
}

ModuleExpression::ModuleExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = "(" + (string)*expr1 + " % " + (string)*expr2 + ")";
}

Expression *ModuleExpression::Interprete() {
    BinaryExpression::Interprete();
    int a = (int)*this->expr1, b = (int)*this->expr2;
    if(a != (double)*this->expr1 && b != (double)*this->expr2)
        throw NumberCastException("The number isn't an integer value.");

    if(b == 0)
        throw DivisionZeroException();

    return new TerminalExpression(to_string(a % b));
}

ConcatExpression::ConcatExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = "\"" + (string)*expr1 + "\" UNION \"" + (string)*expr2 + "\"";
}

Expression *ConcatExpression::Interprete() {
    BinaryExpression::Interprete();
    try{
        return new TerminalExpression(to_string((int)*this->expr1) + to_string((int)*this->expr2));
    } catch(exception e) {
        return new TerminalExpression((string)*this->expr1 + (string)*this->expr2);
    }
}