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
using std::string;
using std::pair;

class Parser
{
private:
    Term *getTail();
    Scanner _scanner;
    Prolog *_prolog;
    pair<string, int> _currentToken;
public:
    Parser(Scanner);
    Term *createTerm();
    Term *buildStruct(Atom *functor);
    Term *buildListOrStruct();
    vector<Term *> getArgs();

};
#endif
