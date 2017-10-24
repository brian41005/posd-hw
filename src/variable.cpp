#include "../include/variable.h"

Variable::Variable(string symbol) : _symbol(symbol) { _value = NULL; }

string Variable::value() const { return _value ? _value->value() : symbol(); }

string Variable::symbol() const { return _symbol; }

bool Variable::match(Term& term) {
    if (_value == NULL) {
        if (Variable* v = term.getVariable()) {
            if (v->symbol() != symbol() && &term != this) _value = &term;
        }
        else
            _value = &term;
        return true;
    } 
    else{
        if (term.symbol() == _value->symbol() && &term == _value) return true;
        return _value->match(term);
    }
        
}