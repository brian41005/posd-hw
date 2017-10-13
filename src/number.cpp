#include "../include/number.h"

Number::Number(int n): _n(to_string(n)){
}
Number::Number(double n): _n(to_string(n)){
}

string Number::value() const {
    return this->_n;
}

string Number::symbol() const {
    return this->_n;
}

bool Number::match(Variable& v){
    return v.match(*this);
}

bool Number::match(Term& term){
    return this->symbol() == term.symbol();
}