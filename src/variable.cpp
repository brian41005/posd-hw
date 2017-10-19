#include "../include/variable.h"

Variable::Variable(string symbol) : _symbol(symbol) { _value = NULL; }

string Variable::value() const { return _value ? _value->value() : symbol(); }

string Variable::symbol() const { return _symbol; }

bool Variable::match(Term& term) {
    if (_value == NULL) {
        if (this != &term) _value = &term;
    } else
        _value->match(term);
    return this->value() == term.value();
}