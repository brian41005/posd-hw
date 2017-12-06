#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <utility>
#include <stack>
#include <map>

#include "atom.h"
#include "number.h"
#include "variable.h"
#include "struct.h"
#include "list.h"
#include "scanner.h"
#include "parserInfo.h"

using std::string;
using std::pair;
using std::stack;
using std::map;

class Parser {
   private:
    Scanner* _scanner;
    Prolog* _tokenInfo;
    std::pair<std::string, size_t> _currentToken;

    std::vector<Term*> _terms;
    std::map<std::string, Term*> _symbolTable;
    Node* _tree;
    Term* createStruct(Atom*);
    Term* createAtomOrStruct();
    Term* createList();
    Term* actualCreateTerm();
    bool isEndOfStruct();

   public:
    std::vector<Term*> getArgs();
    Parser(Scanner&);
    Term* createTerm();
    void createTerms();
    std::vector<Term*> getTerms();

    void matchings();
    Node* expressionTree();
};
#endif
