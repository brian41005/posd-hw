#include "../include/node.h"
#include <iostream>
using namespace std;
Node::Node(Operators op) : payload(op), term(0), left(0), right(0)
{
}

Node::Node(Operators op, Term *t, Node *l, Node *r) : payload(op), term(t), left(l), right(r)
{
}

bool Node::evaluate()
{
    if (payload == COMMA)
    {
        bool leftBool = left->evaluate();
        bool rightBool = right->evaluate();
        return leftBool && rightBool;
    }
    else if (payload == SEMICOLON)
    {
        bool leftBool = left->evaluate();
        bool rightBool = right->evaluate();
        return left || right;
    }
    else if (payload == EQUALITY){
        cout << left->term->symbol() <<endl;
        cout << right->term->symbol() <<endl;
        
        return ((left->term)->match(*right->term));
    }
        
}