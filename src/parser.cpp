#include "../include/parser.h"
#include <iostream>

Parser::Parser(Scanner scanner) : _scanner(scanner), _prolog(Prolog::getInstance()), _pos(0), isGetArgs(false)
{
}

void Parser::matchings()
{
    _parserInfo.clearAll(); 
    Term *temp;
    int _pos = 0; 
    _currentToken = pair<string, int>("haha", 8763);
    while (_currentToken.second != _prolog->EOS && _currentToken.second != '.')
    {

        if (temp = createTerm())
            _parserInfo.pushNode(new Node(TERM, temp, nullptr, nullptr));
        else
        {
            processOpToken();
        }
    }
        processOpToken();

    }

void Parser::updateToken()
{
    _currentToken = _scanner.nextToken();
}

void Parser::processOpToken()
{
    string topOp;
    //std::cout << _parserInfo.peekOp() << std::endl;
    while ((topOp = _parserInfo.peekOp()) != "" && _parserInfo.getPriority(_currentToken.first) > _parserInfo.getPriority(topOp))
    {
        Operators ops = _parserInfo.getOperators(_parserInfo.popOp());
        Node *right = _parserInfo.popNode();
        Node *left = _parserInfo.popNode();
        _parserInfo.pushNode(new Node(ops, nullptr, left, right));
    }
    if (_parserInfo.getOperators(_currentToken.first) == SEMICOLON)
        _pos = _flyweight.size();
    _parserInfo.pushOp(_currentToken.first);
}

Term *Parser::getTerm()
{

    for (int i = _pos; i < _flyweight.size(); i++)
        if (_flyweight[i]->symbol() == _currentToken.first)
            return _flyweight[i];
    Term *term = termFactory();
    if (term)
        _flyweight.push_back(term);
    return term;
}

Term *Parser::createTerm()
{
    _currentToken = _scanner.nextToken();
    if (_currentToken.first == "." && _scanner.isDone())
        return nullptr;
    Term *term = getTerm();

    if (term && !isGetArgs)
        _terms.push_back(term);
    return term;

}

Term *Parser::termFactory()
{
    if (_currentToken.second == _prolog->VARIABLE)
        return new Variable(_currentToken.first);
    else if (_currentToken.second == _prolog->NUMBER)
        return new Number(stod(_currentToken.first));
    else if (_currentToken.second == _prolog->ATOM || _currentToken.second == _prolog->ATOMSC)
    {
        Atom *atom = new Atom(_currentToken.first);
        if (_scanner.currentChar() == '(')
            return buildStruct(atom);
        return atom;
    }
    else if (_currentToken.second == '[')
        return buildListOrStruct();
    else
        return nullptr;
}

Term *Parser::buildStruct(Atom *functor)
{
    _scanner.nextToken();
    vector<Term *> args = getArgs();
    if (_scanner.nextToken().second == ')')
    {
        if (functor->symbol() == "." && args.size() == 2 && args[1]->match(_prolog->EMPTY_LIST))
            return new List(args[0], args[1]);
        return new Struct(*functor, args);
    }
    throw string("unexpected token");
    /* Throw the syntax error when the current char is not right parentheses */
}

Term *Parser::buildListOrStruct()
{
    vector<Term *> args = getArgs();
    Term *tail = (args.size() == 0) ? nullptr : getTail();
    if (_currentToken.second == ']')
    {
        for (int i = args.size() - 1; i >= 0; i--)
        {
            if (tail->getList() || tail->match(_prolog->EMPTY_LIST))
                tail = new List(args[i], tail);
            else
                tail = new Struct(Atom("."), {args[i], tail});
        }
        return (tail) ? tail : new List();
    }
    throw string("unexpected token");
}

vector<Term *> Parser::getArgs()
{
    vector<Term *> args;
    Term *term;
    isGetArgs = true;
    while (_scanner.currentChar() != ')' && ((term = createTerm()) || _currentToken.second == ','))
    {
        isGetArgs = true;
        if (term)
            args.push_back(term);
    }
    isGetArgs = false;
    return args;
}

Term *Parser::getTail()
{
    Term *tail;
    if (_currentToken.second == '|')
    {
        tail = createTerm();
        _currentToken = _scanner.nextToken();
    }
    tail = &_prolog->EMPTY_LIST;
    return tail;
}

vector<Term *> Parser::getTerms()
{
    return _terms;
}

Node *Parser::expressionTree()
{
    return _parserInfo.peekNode();
}
