#include "../include/number.h"

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

bool Number::match(Variable& v){
    return v.match(*this);
}

bool Number::match(Term& term){
    return this->symbol() == term.symbol();
}