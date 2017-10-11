#include "../include/number.h"
#include "../include/variable.h"
#include <string> 
#include <typeinfo>

Number::Number(int n): _n(n) {

}

string Number::value() const {
    return to_string(this->_n);
}

string Number::symbol() const {
    return to_string(this->_n);
}

bool Number::match(Term& term){
    if (typeid(term) == typeid(Variable))
        return term.match(*this);
    else
        return this->symbol() == term.symbol();
}