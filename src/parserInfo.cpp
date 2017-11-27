#include "../include/parserInfo.h"

void ParserInfo::clearAll()
{
    while (!nodes.empty())
        nodes.pop();
    while (!ops.empty())
        ops.pop();
}

void ParserInfo::pushNode(Node *node)
{
    nodes.push(node);
}

void ParserInfo::pushOp(string op)
{
    ops.push(op);
}

Node *ParserInfo::popNode()
{
    Node *node = nodes.top();
    nodes.pop();
    return node;
}

Node *ParserInfo::peekNode()
{
    if (nodes.empty())
        return nullptr;
    return nodes.top();
}

string ParserInfo::popOp()
{
    string op = ops.top();
    ops.pop();
    return op;
}

string ParserInfo::peekOp()
{
    if (ops.empty())
        return "";
    return ops.top();
}

int ParserInfo::getPriority(string op)
{
    if (op == "=")
        return 700;
    else if (op == ",")
        return 1000;
    else if (op == ";")
        return 1100;
    else
        return 99999;
}

Operators ParserInfo::getOperators(string op)
{
    if (op == "=")
        return EQUALITY;
    else if (op == ",")
        return COMMA;
    else if (op == ";")
        return SEMICOLON;
    else
        return TERM;
}