#include "../include/number.h"
#include "../include/variable.h"
#include <string> 
#include <typeinfo>

Number::Number(int n):_n(n) {

}

string Number::value() const {
    return to_string(this->_n);
}

string Number::symbol() const {
    return to_string(this->_n);
}

bool Number::match(SimpleObj* simple){
    if (typeid(*simple) == typeid(Variable))
        return simple->match(this);
    else
        return this->symbol() == simple->symbol();
}