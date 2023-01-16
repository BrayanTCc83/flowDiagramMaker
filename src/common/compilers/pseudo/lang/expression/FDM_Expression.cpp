#include "FDM_ExpressionTree.hpp"

using namespace FDM_Expressions;

TerminalExpression::TerminalExpression(string data) {
    data = data;
}

bool TerminalExpression::interpreter(string toInteprete) {
    return toInteprete.find(data) != string::npos;
}

BinaryExpression::BinaryExpression(Expression expr1, Expression expr2) {
    this->expr1 = expr1;
    this->expr2 = expr2;
}

UnitaryExpression::UnitaryExpression(Expression expression) {
    this->expression = expression;
}