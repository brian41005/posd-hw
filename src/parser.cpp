#include "../include/parser.h"
#include <iostream>

Parser::Parser(Scanner& scanner): _scanner(&scanner), _tokenInfo(Prolog::getInstance()) {}

vector<Term*> Parser::getArgs() {
    vector<Term*> terms;
    Term* term = nullptr;
    while (!isEndOfStruct() &&
           ((term = createTerm()) || _currentToken.second == ','))
        if (term) terms.push_back(term);
    return terms;
}

Term* Parser::createStruct(Atom* functor) {
    _scanner->nextToken();
    vector<Term*> terms = getArgs();
    if (_scanner->nextToken().second == ')') {
        return new Struct(*functor, terms);
    }
    throw string("unexpected token");
}

Term* Parser::createAtomOrStruct() {
    Atom* atom = new Atom(_currentToken.first);
    if (_scanner->currentChar() == '(') return createStruct(atom);
    return atom;
}

Term* Parser::createList() {
    vector<Term*> terms = getArgs();
    Term* tail = _currentToken.second == '|' ? createTerm() : new List();
    if (_scanner->nextToken().second == ']') {
        for (int i = terms.size() - 1; i >= 0; i--) {
            if (tail->getList())
                tail = new List(terms[i], tail->getList());
            else
                new Struct(Atom("."), {terms[i], tail});
        }
        return tail;
    }
    throw string("unexpected token");
}

Term* Parser::createTerm() {
    _currentToken = _scanner->nextToken();
    return actualCreateTerm();
}

Term* Parser::actualCreateTerm() {
    string tokenString = _currentToken.first;
    int tokenType = _currentToken.second;
    Term* tempTerm = nullptr;
    if (tokenType == _tokenInfo->VARIABLE)
        tempTerm = new Variable(tokenString);
    else if (tokenType == _tokenInfo->NUMBER)
        tempTerm = new Number(stod(tokenString));
    else if (tokenType == _tokenInfo->ATOM || tokenType == _tokenInfo->ATOMSC)
        tempTerm = createAtomOrStruct();
    else if (_currentToken.second == '[')
        tempTerm = createList();

    if (tempTerm) {
        map<string, Term*>::iterator iter =
            _symbolTable.find(tempTerm->symbol());
        if (iter != _symbolTable.end()) return iter->second;
        _symbolTable[tempTerm->symbol()] = tempTerm;
        return tempTerm;
    }
    return nullptr;
}

bool Parser::isEndOfStruct() {
    _scanner->skipLeadingWhiteSpace();
    return (_scanner->currentChar() == ')' || _scanner->currentChar() == ']');
}

void Parser::matchings() {
    _tree = nullptr;
    _terms.clear();
    Term* term = nullptr;
    _symbolTable.clear();
    stack<Operators> opStack;
    vector<Node*> nodes;
    Operators currentOp;
    _currentToken = _scanner->nextToken();
    while ((_currentToken.second != _tokenInfo->EOS &&
            _currentToken.first != ".")) {
        term = actualCreateTerm();
        if (term) {
            _terms.push_back(term);
            nodes.push_back(new Node(TERM, term, nullptr, nullptr));
        } else {
            currentOp = operatorsEnum(_currentToken.first);
            if (currentOp == SEMICOLON) _symbolTable.clear();
            if (opStack.size() == 0 ||
                operatorsProity(currentOp) > operatorsProity(opStack.top()))
                opStack.push(currentOp);
            else {
                nodes.push_back(new Node(opStack.top()));
                opStack.pop();
                opStack.push(currentOp);
            }
        }

        _currentToken = _scanner->nextToken();
    }
    while (opStack.size()) {
        nodes.push_back(new Node(opStack.top()));
        opStack.pop();
    }

    stack<Node*> nodeStack;
    for (auto element : nodes) {
        if (element->payload != TERM) {
            element->right = nodeStack.top();
            nodeStack.pop();
            element->left = nodeStack.top();
            nodeStack.pop();
            nodeStack.push(element);
        } else
            nodeStack.push(element);
    }
    _tree = nodeStack.top();
}

void Parser::createTerms() { _terms = getArgs(); }

vector<Term*> Parser::getTerms() { return _terms; }

Node* Parser::expressionTree() { return _tree; }