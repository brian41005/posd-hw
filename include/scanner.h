#ifndef SCANNER_H
#define SCANNER_H

#include <utility>
#include <string>
#include "prolog.h"
using std::string;
using std::pair;

class Scanner
{

private:
    Prolog *_prolog;
    string _buffer;
    int _position;

public:
    Scanner(string input="");
    pair<string, int> nextToken();
    int skipLeadingWhiteSpace();
    string extractNumber();
    string extractAtom();
    string extractAtomSC();
    string extractVariable();
    char extractChar();
    char currentChar();
    int position();

};

#endif