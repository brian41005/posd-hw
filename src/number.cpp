#include "../include/number.h"

Number::Number(int n): _n(to_string(n)){
}

Number::Number(double n){
    _n = to_string(n);
    int i = _n.find_last_not_of("0");
    if (i != string::npos){
        _n = _n.substr(0, i+1);
        if (_n.back() == '.')
            _n += "0";
    }
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