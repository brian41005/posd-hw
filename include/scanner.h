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
    int _position, _peekPosition;
    bool isNumberChar(bool *hasPoint);
    
public:
    Scanner(string input="");
    pair<string, int> nextToken();
    pair<std::string, int> peekNextToken();//
    int peekSkipLeadingSpace();//
    std::string peekAtom();//
    std::string peekAtomSC();//
    std::string peekNumber();//
    std::string peekVariable();//
    char peekCurrentChar();//
    char peekChar();//
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