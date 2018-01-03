#include "../include/scanner.h"
#include <iostream>

Scanner::Scanner(std::string in)
    : _prolog(Prolog::getInstance()), _buffer(in), _position(0) {}

int Scanner::skipLeadingWhiteSpace() {
    for (; (_position < _buffer.length() && _buffer[_position] == ' ') ||
           _buffer[_position] == '\t';
         _position++)
        ;
    return _position;
}

std::string Scanner::extractNumber() {
    int begin = _position;
    int hasDot = -1;
    for (;
         isdigit(_buffer[_position]) ||
         (hasDot == -1 && (_buffer[_position] == '.' && (hasDot = _position)));
         _position++)
        ;
    if (hasDot == _position - 1) _position--;
    return _buffer.substr(begin, _position - begin);
}

std::string Scanner::extractAtom() {
    int begin = _position;
    for (; isalnum(_buffer[_position]) || _buffer[_position] == '_';
         _position++)
        ;
    return _buffer.substr(begin, _position - begin);
}

std::string Scanner::extractAtomSC() {
    int begin = _position;
    for (; _prolog->isSpecialChar(_buffer[_position]); _position++)
        ;
    return _buffer.substr(begin, _position - begin);
}

std::string Scanner::extractVariable() {
    int begin = position();
    for (; isalnum(_buffer[_position]) || _buffer[_position] == '_';
         _position++)
        ;
    return _buffer.substr(begin, _position - begin);
}

char Scanner::extractChar() { return _buffer[_position++]; }

char Scanner::currentChar() { return _buffer[_position]; }

int Scanner::position() { return _position; }

std::pair<std::string, int> Scanner::nextToken() {
    if (skipLeadingWhiteSpace() >= _buffer.length())
        return std::pair<std::string, int>("", _prolog->EOS);
    else if (isdigit(currentChar()))
        return std::pair<std::string, int>(extractNumber(), _prolog->NUMBER);
    else if (islower(currentChar()))
        return std::pair<std::string, int>(extractAtom(), _prolog->ATOM);
    else if (_prolog->isSpecialChar(currentChar()))
        return std::pair<std::string, int>(extractAtomSC(), _prolog->ATOMSC);
    else if (isupper(currentChar()) || currentChar() == '_')
        return std::pair<std::string, int>(extractVariable(),
                                           _prolog->VARIABLE);
    else {
        char c = extractChar();
        return std::pair<std::string, int>(std::string(1, c), c);
    }
}

std::pair<std::string, int> Scanner::peekNextToken() {
    _peekPosition = _position;
    if (peekSkipLeadingSpace() >= _buffer.length())
        return std::pair<std::string, int>("", _prolog->EOS);
    else if (isdigit(peekCurrentChar()))
        return std::pair<std::string, int>(peekNumber(), _prolog->NUMBER);
    else if (islower(peekCurrentChar()))
        return std::pair<std::string, int>(peekAtom(), _prolog->ATOM);
    else if (_prolog->isSpecialChar(peekCurrentChar()))
        return std::pair<std::string, int>(peekAtomSC(), _prolog->ATOMSC);
    else if (isupper(peekCurrentChar()) || peekCurrentChar() == '_')
        return std::pair<std::string, int>(peekVariable(),
                                           _prolog->VARIABLE);
    else {
        char c = peekChar();
        return std::pair<std::string, int>(std::string(1, c), c);
    }
}

int Scanner::peekSkipLeadingSpace() {
    for (;
         (_peekPosition < _buffer.length() && _buffer[_peekPosition] == ' ') ||
         _buffer[_peekPosition] == '\t';
         _peekPosition++)
        ;
    return _peekPosition;
}

std::string Scanner::peekAtom() {
    int begin = _peekPosition;
    for (; isalnum(_buffer[_peekPosition]) || _buffer[_peekPosition] == '_';
         _peekPosition++)
        ;
    return _buffer.substr(begin, _peekPosition - begin);
}

std::string Scanner::peekAtomSC() {
    int begin = _peekPosition;
    for (; _prolog->isSpecialChar(_buffer[_peekPosition]); _peekPosition++)
        ;
    return _buffer.substr(begin, _peekPosition - begin);
}

std::string Scanner::peekNumber() {
    int begin = _peekPosition;
    int hasDot = -1;
    for (; isdigit(_buffer[_peekPosition]) ||
           (hasDot == -1 &&
            (_buffer[_peekPosition] == '.' && (hasDot = _peekPosition)));
         _peekPosition++)
        ;
    if (hasDot == _peekPosition - 1) _peekPosition--;
    return _buffer.substr(begin, _peekPosition - begin);
}
std::string Scanner::peekVariable() {
    int begin = _peekPosition;
    for (; isalnum(_buffer[_peekPosition]) || _buffer[_peekPosition] == '_';
         _peekPosition++)
        ;
    return _buffer.substr(begin, _peekPosition - begin);
}
char Scanner::peekCurrentChar() { return _buffer[_peekPosition]; }
char Scanner::peekChar() { return _buffer[_peekPosition++]; }