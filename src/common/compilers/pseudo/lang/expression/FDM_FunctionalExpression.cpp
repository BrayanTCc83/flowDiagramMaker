#include "FDM_Expression.hpp"

using namespace FDM_Expressions;

class HashTable {
    int m;
    Expression** saves;
    private:
        int H(string key) {
            const char *x = key.c_str();
            int j = 0;
            for(; *x; x++)
                j = 131*j + *x;
            return j%m;
        }

    public:
        HashTable(int m) {
            this->m = m;
            this->saves = new Expression*[m];
        }
        void Put(string key, Expression* value) {
            int n = H(key);
            this->saves[n] = value;
        }

        Expression *Get(string key) {
            int n = H(key);
            return saves[n];
        }
};

HashTable *arrs = new HashTable(31);

WriteExpression::WriteExpression(Expression *expression) : UnitaryExpression(expression) {
    this->data = "Write '"+ (string)*expression +"'";
}

Expression *WriteExpression::Interprete() {
    Expression *expr = GoDown(expression);
    cout << ((string)*expression) << endl;
    return new NullExpression();
}

ReadExpression::ReadExpression(Expression *expression) : UnitaryExpression(expression) {
    this->data = "Read " + (string)*expression;
}

Expression *ReadExpression::Interprete() {
    cin >> (*this->expression);
    return new NullExpression();
}

ArrayExpression::ArrayExpression(string name) : TerminalExpression(name) {
    this->size = 0;
    this->data = "Array = NULL";
    arrs->Put(name, this);
}

Expression *ArrayExpression::Interprete() {
    return new NullExpression();
}

InsertItemExpression::InsertItemExpression(string key, Expression *expression) : UnitaryExpression(expression) {
    this->key = key;
}

Expression *InsertItemExpression::Interprete() {
    ArrayExpression *array = (ArrayExpression*) arrs->Get(this->key);
    array->content.push_back(expression);
    array->size++;
    return new TerminalExpression("1");
}

RemoveItemExpression::RemoveItemExpression(string key, Expression *expression) : UnitaryExpression(expression) {
    this->key = key;
}

Expression *RemoveItemExpression::Interprete() {
    ArrayExpression *array = (ArrayExpression*) arrs->Get(this->key);
    int n = (int)*expression;
    if(n >= array->size || n < 0)
        throw OutRangeException();
    array->content.erase(array->content.begin() + n);

    return new NullExpression();
}

GetItemExpression::GetItemExpression(string key, Expression *expression) : UnitaryExpression(expression) {
    this->key = key;
}

Expression *GetItemExpression::Interprete() {
    ArrayExpression *array = (ArrayExpression*) arrs->Get(this->key);
    int n = (int)*expression;
    if(n >= array->size || n < 0)
        throw OutRangeException();
    cout << ((string)*array->content.at(n));

    return array->content.at(n);
}