#include "../include/variable.h"


Variable::Variable(string symbol): _symbol(symbol){
    this->_value = NULL;
}

string Variable::value() const{
    return this->_value? this->_value->value():this->_symbol;
}

string Variable::symbol() const{
    return this->_symbol;
}

bool Variable::match(Term& term){
    if (this->_value == NULL){
        Variable* v = dynamic_cast<Variable*>(&term);
        if (!(v && this->symbol() == term.symbol()))
            this->_value = &term;
    }
    else
        this->_value->match(term);

    return this->value() == term.value();

}