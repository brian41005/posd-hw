#ifndef PROLOG_H
#define PROLOG_H

#include "list.h"

class Prolog
{

private:
    static Prolog *_instance;

protected:
    Prolog();

public:
    const int NONE = -1;
    const int EOS = '\0';
    const int NUMBER = 256;
    const int ATOM = 257;
    const int ATOMSC = 258;
    const int VARIABLE = 259;
    List EMPTY_LIST;
    static Prolog *getInstance();
    bool isSpecialChar(char c);

};

#endif
