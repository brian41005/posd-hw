#include "../include/variable.h"
#include <string> 
#include <iostream>
Variable::Variable(string symbol): _symbol(symbol){
}

string Variable::value() const{
    return this->_value;
}

string Variable::symbol() const{
    return this->_symbol;
}

bool Variable::match(Term& term){
    if (this->_value.empty())
        this->_value = term.value();
    return  this->_value == term.value();
}