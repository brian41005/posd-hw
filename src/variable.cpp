#include "../include/variable.h"

Variable::Variable(string symbol) : _symbol(symbol) { _value = NULL; }

string Variable::value() const { return _value ? _value->value() : symbol(); }

string Variable::symbol() const { return _symbol; }

bool Variable::match(Term& term) {
    if (Variable* v = term.getVariable()) {
        if (term.symbol() == symbol() || &term == this) return true;
        if (v->_value == this) return true;
    }
    if (_value) {
        return (term.symbol() == _value->symbol() || &term == _value)
                   ? true
                   : _value->match(term);
    } else {
        _value = &term;
        return true;
    }
}