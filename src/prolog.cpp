#include "../include/prolog.h"

Prolog::_instance = nullptr;

Prolog::Prolog()
{

}

static Prolog* Prolog::getInstance(){
    if (!_instance)
        _instance = new Prolog();
    return _instance;
}

bool Prolog::isSpecialChar(char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '<' || c == '>' || c == '.' || c == '&' || c == '\\' || c == '~' || c == '^' || c == '$' || c == '#' || c == '@' || c == '?' || c == ':';
}