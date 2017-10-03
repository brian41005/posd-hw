#include "../include/number.h"

Number::Number(string s):_symbol(s) {

}

float Number::value() const {
    return stof(_symbol);
}

string Number::symbol() const {
    return _symbol;
}

bool Number::match(const Number n) const {
    return _symbol == n.symbol();
}