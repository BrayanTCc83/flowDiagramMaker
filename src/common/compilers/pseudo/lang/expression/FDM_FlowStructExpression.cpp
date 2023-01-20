#include "FDM_Expression.hpp"

using namespace FDM_Expressions;

SequenceExpression::SequenceExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = "do ["+((string)*expr1)+ "] then ["+(expr2 == NULL ? "NULL" : (string)*expr2)+"]";
}

Expression *SequenceExpression::Interprete() {
    Expression *expression = GoDown(this->expr1);
    if(expr2 != NULL)
        expression = GoDown(this->expr2);

    return expression;
}

IfExpression::IfExpression(Expression *expr1, Expression *expr2, Expression *expr3) : TernaryExpression(expr1, expr2, expr3) {
    this->data = "if "+((string)*expr1)+ " do "+((string)*expr2) + " else " + (expr3 != NULL ? (string)*expr3 : "NULL");
}
IfExpression::IfExpression(Expression *expr1, Expression *expr2) : IfExpression(expr1, expr2, NULL) {
    this->data = "if "+((string)*expr1)+ " do "+((string)*expr2);
}

Expression *IfExpression::Interprete() {
    if((bool)*this->expr1->Interprete())
        return expr2->Interprete();
    else
        return expr3 == NULL ? new NullExpression() : expr3->Interprete();
}

CaseListExpression::CaseListExpression(Expression *expr1, Expression *expr2, Expression *expr3) : TernaryExpression(expr1, expr2, expr3) {
    this->data = "test "+((string)*expr1)+ " do ["+((string)*expr2)+"] then "+(expr3 == NULL ? "exit" : (string)*expr3);
}

void CaseListExpression::SetEvaluation(Expression *toEval) {
    this->toEval = toEval;
    this->evaluation = new EqualsToExpression(toEval, expr1);
}

Expression *CaseListExpression::Interprete() {
    if((bool)*this->evaluation->Interprete())
        return expr2;
    else {
        if(dynamic_cast<const CaseListExpression*>(expr3) != nullptr)
            ((CaseListExpression*)expr3)->SetEvaluation(toEval);
        return expr3->Interprete();
    }
}

DefaultCaseExpression::DefaultCaseExpression(Expression *expression) : UnitaryExpression(expression) {
    this->data = "default ["+((string)*expression)+"]";
}

Expression *DefaultCaseExpression::Interprete() {
    return this->expression;
}

SwitchExpression::SwitchExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = "switch "+((string)*expr1)+ " cases ["+(expr2 == NULL ? "" : (string)*expr2)+"]";
}

Expression *SwitchExpression::Interprete() {
    ((CaseListExpression*)expr2)->SetEvaluation(expr1);
    return this->expr2->Interprete();
}

WhileExpression::WhileExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = "while "+((string)*expr1)+ " do ["+(expr2 == NULL ? "" : (string)*expr2)+"]";
}

Expression *WhileExpression::Interprete() {
    Expression *sequence = this->expr2;
    while((bool)*this->expr1->Interprete())
        sequence->Interprete();

    return new NullExpression();
}

UntilExpression::UntilExpression(Expression *expr1, Expression *expr2) : BinaryExpression(expr1, expr2) {
    this->data = "until "+((string)*expr1)+ " do ["+(expr2 == NULL ? "" : (string)*expr2)+"]";
}

Expression *UntilExpression::Interprete() {
    Expression *sequence = this->expr2;
    while(!(bool)*this->expr1->Interprete())
        sequence->Interprete();

    return new NullExpression();
}

ForExpression::ForExpression(Expression *expr1, Expression *expr2, Expression *expr3) : TernaryExpression(expr1, expr2, expr3) {
    this->data = "for [ ;" + ((string)*expr1) + "; " + ((string)*expr2) + "] do [" + ((string)*expr3) + "]";
}

Expression *ForExpression::Interprete() {
    Expression *sequence = this->expr3;
    for(; (bool)*this->expr1->Interprete(); expr2->Interprete())
        sequence->Interprete();

    return new NullExpression();
}