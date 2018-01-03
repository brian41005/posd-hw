#include "../include/node.h"
#include "../include/variable.h"
#include <iostream>
#include <sstream>
using namespace std;
Node::Node(Operators op) : payload(op), term(0), left(0), right(0)
{
}

Node::Node(Operators op, Term *t, Node *l, Node *r) : payload(op), term(t), left(l), right(r)
{
}

bool Node::evaluate() {
    switch (payload) {
        case COMMA:
            return left->evaluate() && right->evaluate();
        case SEMICOLON: {
            bool leftIsTrue = left->evaluate();
            bool rightIsTrue = right->evaluate();
            return leftIsTrue || rightIsTrue;
        }
        case EQUALITY:
            return ((left->term)->match(*right->term));
        default:
            return true;
    }
}

std::string Node::getResult() {
    std::ostringstream oss;
    switch (payload) {
        case COMMA: {
            std::string rightResult = right->getResult();
            std::string leftResult = left->getResult();
            if (leftResult == "false" || rightResult == "false") {
                oss << "false";
            } else if (leftResult == "true") {
                if (rightResult == "true") {
                    oss << "true";
                } else {
                    oss << rightResult;
                }
            } else {
                if (leftResult == rightResult || rightResult == "true") {
                    oss << leftResult;
                } else {
                    oss << leftResult << ", " << rightResult;
                }
            }
            break;
        }
        case SEMICOLON: {
            std::string leftResult = left->getResult();
            std::string rightResult = right->getResult();
            if (leftResult == "false")
                oss << rightResult;
            else if (rightResult == "false")
                oss << leftResult;
            else
                oss << leftResult << "; " << rightResult;
            break;
        }
        case EQUALITY: {
            Variable* leftVariable = left->term->getVariable();
            Variable* rightVariable = right->term->getVariable();
            if (leftVariable && !rightVariable) {
                if (leftVariable->symbol() == leftVariable->value()) {
                    ((left->term)->match(*right->term));
                    oss << leftVariable->symbol() << " = "
                        << leftVariable->value();
                } else {
                    oss << ((left->term)->match(*right->term) ? "true"
                                                              : "false");
                }
            } else if (rightVariable && !leftVariable) {
                if (rightVariable->symbol() == rightVariable->value()) {
                    (left->term)->match(*right->term);
                    oss << rightVariable->symbol() << " = "
                        << rightVariable->value();
                } else {
                    oss << ((left->term)->match(*right->term) ? "true"
                                                              : "false");
                }
            } else {
                oss << ((left->term)->match(*right->term) ? "true" : "false");
            }
            break;
        }

        default:
            oss << "";
    }
    return oss.str();
}