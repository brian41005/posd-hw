#ifndef NODE_H
#define NODE_H
#include "term.h"
#include <string>
enum Operators
{
    SEMICOLON,
    COMMA,
    EQUALITY,
    TERM
};
static Operators operatorsEnum(std::string tokenString) {
    if (tokenString == "=")
        return EQUALITY;
    else if (tokenString == ",")
        return COMMA;
    else
        return SEMICOLON;
}

static int operatorsProity(Operators op) {
    switch (op) {
        case EQUALITY:
            return 300;
        case COMMA:
            return 200;
        case SEMICOLON:
            return 100;
        default:
            return 999;
    }
}

static std::string operatorsEnumToString(Operators op) {
    if (op == COMMA)
        return ",";
    else
        return ";";
}
class Node
{
  public:
    Node(Operators op);
    Node(Operators op, Term *t, Node *l, Node *r);
    Operators payload;
    Term *term;
    Node *left;
    Node *right;
    Node* parent;
    bool evaluate();
    std::string getResult();
};

#endif
