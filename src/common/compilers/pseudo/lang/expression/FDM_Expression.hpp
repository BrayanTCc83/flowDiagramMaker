#ifndef FDM_EXPRESSION_TYPES
#define FDM_EXPRESSION_TYPES
#pragma once
#include <string>

using namespace std;

namespace FDM_Expressions{
    class Expression {
        public:
            bool interpreter(string toInterprete);
    };

    class TerminalExpression: Expression {
        private:
            string data;
        public:
            TerminalExpression(string data);
            bool interpreter(string toInterprete);
    };

    class BinaryExpression: Expression {
        private:
            Expression expr1, expr2;
        public:
            BinaryExpression(Expression expr1, Expression expr2);
            bool interpreter(string toInterprete);
    };

    class UnitaryExpression: Expression {
        private:
            Expression expression;
        public:
            UnitaryExpression(Expression expression);
            bool interpreter(string toInterprete);
    };
};

#endif