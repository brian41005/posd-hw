#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <utility>
#include "atom.h"
#include "number.h"
#include "variable.h"
#include "struct.h"
#include "list.h"
#include "scanner.h"
#include "parserInfo.h"

using std::string;
using std::pair;

class Parser
{
private:
    Term *getTail();
    int _pos;
    bool isGetArgs;
    Scanner _scanner;
    Prolog *_prolog;
    pair<string, int> _currentToken;
    vector<Term *> _terms;
    vector<Term *> _flyweight;
    ParserInfo _parserInfo;
public:
    Parser(Scanner scanner);
    void matchings();
    void updateToken();
    void processOpToken();
    Term *getTerm();
    Term *createTerm();
    Term *termFactory();
    Term *buildStruct(Atom *functor);
    Term *buildListOrStruct();
    vector<Term *> getArgs();
    vector<Term *> getTerms();
    Node *expressionTree();

};
#endif
