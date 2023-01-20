#ifndef FDM_EXPRESSION_TYPES
#define FDM_EXPRESSION_TYPES
#pragma once
#include <string>
#include <sstream>
#include <ostream>
#include <istream>
#include <iostream>
#include <vector>
#include<bits/stdc++.h>

using namespace std;

/**
 * This file contains the declaration of every expressions that programm needs to work,
 * each expression represents an instruction (definition, operator or flow struct), 
 * each of those expressions is instanced when a .fdm file contains it. 
*/
namespace FDM_Expressions{
    // EXPRESSION EXCEPTIONS 
    /**
     * Number Cast Exception, it's called when a number like a double can't be casted to 
     * a integer.
    */
    struct NumberCastException : public exception {
        const char* reason;
        /**
         * Returns the reason by the exception
        */
        const char * what () const throw () {
            return reason;
        }
        public:
            NumberCastException(const char* reason) {
                this->reason = reason;
            }
    };

    /**
     * Division Zero Exception it's called when you're trying to divide a number a between 0.
    */
    struct DivisionZeroException : public exception {
        /**
         * Returns the reason by the exception
        */
        const char * what () const throw () {
            return "You are trying to do a division by zero.";
        }
    };

    /**
     * No Number Exception is called when your expression not contains a value accepted as a 
     * number (double, float, short, int, long).
    */
    struct NoNumberException : public exception {
        /**
         * Returns the reason by the exception
        */
        const char * what () const throw () {
            return "The value isn't a number.";
        }
    };

    /**
     * No Terminal Expression Exception is called when you try to use a expression in other who 
     * needs a terminal expression, like an asignation right side or inceresse/decresse by example:
     * - Accepted:
     *      x = a + 1
     *      x++
     * - Denied:
     *      a + 1 = x
     *      (a + 1)++
    */
    struct NoTerminalExpressionException : public exception {
        /**
         * Returns the reason by the exception
        */
        const char * what () const throw () {
            return "The value can't be assigned to the variable.";
        }
    };

    /**
     * Out Range Exception is called when you are trying to access to an index out of range, greater 
     * or smaller the elements that the array contains.
    */
    struct OutRangeException : public exception {
        /**
         * Returns the reason by the exception
        */
        const char * what () const throw () {
            return "The index is out range";
        }
    };

    // BASICS EXPRESSIONS
    /**
     * The class Expression is the base of each expression used in the program, is used as an abstract
     * class and in the program never is instanced.
    */
    class Expression {
        public:
            /**
             * Contains the representation of the expression value.
            */
            string data;
        protected:
            /**
             * This function calls recusively the interpretation of each expression until identificates
             * a Terminal expression (Terminal, Variable, Array or Null)
            */
            Expression *GoDown(Expression *expression);
        public:
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
            /**
             * Returns if the current expression is an terminal expression or none.
            */
            virtual bool isTerminal();
            /**
             * Overloads the Right Side operator to make it compatible with expressions.
            */
            friend ostream& operator<<(ostream& output, const Expression& expression);
            /**
             * Overloads the Left Side operator to make it compatible with expressions.
            */
            friend istream& operator>>(istream& input, Expression& expression);
            /**
             * Overloads the cast string operator to make ir compatible with expressions.
            */
            operator string() { return data; }
            /**
             * Overloads the cast bool operator to make ir compatible with expressions.
            */
            operator bool() { 
                try { return data.compare("0") != 0; } 
                catch(exception e) { throw NoNumberException(); }
            }
            /**
             * Overloads the cast double operator to make ir compatible with expressions.
            */
            operator double() {
                try { return stod(data); }
                catch(exception e) { throw NoNumberException(); }
            }
            /**
             * Overloads the cast int operator to make ir compatible with expressions.
            */
            operator int() {
                try { return stoi(data); }
                catch(exception e) { throw NoNumberException(); }
            }
    };

    inline ostream& operator<<(ostream& output, const Expression& expression) {
        return output << expression.data;
    }

    inline istream& operator>>(istream& input, Expression& expression) {
        input >> expression.data;
        return input;
    }

    /**
     * Class Terminal indicates an expression that is the last on the interpretation tree.
    */
    class TerminalExpression: public Expression {
        public:
            TerminalExpression(string data);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
            /**
             * Returns if the current expression is an terminal expression or none.
            */
            virtual bool isTerminal();
    };

    /**
     * Class Null Expression is a terminal expression that indicates that is void, this expression
     * do nothing in the interpretation.
    */
    class NullExpression: public TerminalExpression {
        public:
            NullExpression();
            virtual Expression *Interprete();
    };

    /**
     * Is used as base for ternary expression, like an if [condition, if case, else case] or anothers.
    */
    class TernaryExpression: public Expression {
        protected:
            Expression *expr1, *expr2, *expr3;
        public:
            TernaryExpression(Expression *expr1, Expression *expr2, Expression *expr3);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is used as base for binary expression, the most common like asignation (a = b), logic, relational, 
     * or aritmethic operation.
    */
    class BinaryExpression: public Expression {
        protected:
            Expression *expr1, *expr2;
        public:
            BinaryExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is used as base for a unitary expression, like an increment (a++), switch, while flow struct, etc.
    */
    class UnitaryExpression: public Expression {
        protected:
            Expression *expression;
        public:
            UnitaryExpression(Expression *expression);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    // LOGICAL EXPRESSION
    /**
     * Is the representation of an 'and logic operator', in C++ &&
    */
    class AndExpression: public BinaryExpression {
        public:
            AndExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'or logic operator', in C++ ||
    */
    class OrExpression: public BinaryExpression {
        public:
            OrExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'xor logic operator'
    */
    class XorExpression: public BinaryExpression {
        public:
            XorExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'not logic operator', in C++ !
    */
    class NotExpression: public UnitaryExpression {
        public:
            NotExpression(Expression *expression);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    // ARITMETICAL EXPRESSION
    /**
     * Is the representation of an 'asignation aritmethic operator', in C++ =
    */
    class AsignationExpression: public BinaryExpression {
        public:
            AsignationExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'incresse aritmethic operator', in C++ ++
    */
    class IncresseExpression : public UnitaryExpression {
        public:
            IncresseExpression(Expression *expression);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'decresse aritmethic operator', in C++ --
    */
    class DecresseExpression : public UnitaryExpression {
        public:
            DecresseExpression(Expression *expression);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'adition aritmethic operator', in C++ +
    */
    class AditionExpression: public BinaryExpression {
        public:
            AditionExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'substraction aritmethic operator', in C++ -
    */
    class SubstractionExpression: public BinaryExpression {
        public:
            SubstractionExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'multiplication aritmethic operator', in C++ *
    */
    class MultiplicationExpression: public BinaryExpression {
        public:
            MultiplicationExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'division aritmethic operator', in C++ /
    */
    class DivisionExpression: public BinaryExpression {
        public:
            DivisionExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'module aritmethic operator', in C++ %
    */
    class ModuleExpression: public BinaryExpression {
        public:
            ModuleExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'concat operator', in C++ +
    */
    class ConcatExpression: public BinaryExpression {
        public:
            ConcatExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    // RELATIONAL EXPRESSION
    /**
     * Is the representation of an 'greater relational operator', in C++ >
    */
    class GreaterThanExpression: public BinaryExpression {
        public:
            GreaterThanExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'less relational operator', in C++ <
    */
    class LessThanExpression: public BinaryExpression {
        public:
            LessThanExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'equals relational operator', in C++ ==
    */
    class EqualsToExpression: public BinaryExpression {
        public:
            EqualsToExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'different relational operator', in C++ !=
    */
    class DifferentToExpression: public BinaryExpression {
        public:
            DifferentToExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'greater or equals relational operator', in C++ >=
    */
    class GreaterEqualsExpression: public BinaryExpression {
        public:
            GreaterEqualsExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of an 'less or equals relational operator', in C++ <=
    */
    class LessEqualsExpression: public BinaryExpression {
        public:
            LessEqualsExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    // FLOW STRUCTS
    /**
     * Represents common sequence expression in a program a -> b -> c instruction order
     * in blocks of two in two expressions.
    */
    class SequenceExpression: public BinaryExpression {
        public:
            SequenceExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Represents an if exprexsion, when expr1 is true, then do expr2 else expr3 (only when exists).
    */
    class IfExpression: public TernaryExpression {
        public:
            IfExpression(Expression *expr1, Expression *expr2, Expression *expr3);
            IfExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the representation of a posible case in a switch expression.
    */
    class CaseListExpression: public TernaryExpression {
        private:
            Expression *evaluation, *toEval;
        public:
            CaseListExpression(Expression *expr1, Expression *expr2, Expression *expr3);
            void SetEvaluation(Expression *toEval);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Is the expression to do when no one case is assert in a switch expression.
    */
    class DefaultCaseExpression: public UnitaryExpression {
        public:
            DefaultCaseExpression(Expression *expression);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Represents an switch case expression, test every case one by one, if any one assert do that and
     * returns the expression resultant, if has and default and any case assert return its, else do nothing.
    */
    class SwitchExpression: public BinaryExpression {
        public:
            SwitchExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Represents a while expression, if the expression 1 is true do the sequence of expression 2.
    */
    class WhileExpression: public BinaryExpression {
        public:
            WhileExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Represents a until expression, if the expression 1 is false do the sequence of expression 2.
    */
    class UntilExpression: public BinaryExpression {
        public:
            UntilExpression(Expression *expr1, Expression *expr2);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Represents a for expression, if the expression 1 assert do the sequence of expression 3 and 
     * then turn to do expression 2 and repeat until expression 1 fail.
    */
    class ForExpression: public TernaryExpression {
        public:
            ForExpression(Expression *expr1, Expression *expr2, Expression *expr3);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    // Functional Expression
    /**
     * Write a value on the console output.
    */
    class WriteExpression: public UnitaryExpression {
        public:
            WriteExpression(Expression *expression);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Read a value by the console input.
    */
    class ReadExpression: public UnitaryExpression {
        public:
            ReadExpression(Expression *expression);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    // Define variables and functions
    /**
     * Define an array list of expression to work.
    */
    class ArrayExpression: public TerminalExpression {
        public:
            int size;
            vector<Expression*> content;
        public:
            ArrayExpression(string);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Insert an expression value on an array list
    */
    class InsertItemExpression : public UnitaryExpression {
        private:
            string key;
        public:
            InsertItemExpression(string key, Expression *expression);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };
    
    /**
     * Removes an expression value of an array list
    */
    class RemoveItemExpression : public UnitaryExpression {
        private:
            string key;
        public:
            RemoveItemExpression(string key, Expression *expression);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };

    /**
     * Get a value expression of an array list.
    */
    class GetItemExpression : public UnitaryExpression {
        private:
            string key;
        public:
            GetItemExpression(string key, Expression *expression);
            /**
             * Do an interpretation execution of the expression used.
            */
            virtual Expression *Interprete();
    };
};

#endif