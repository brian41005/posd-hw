#include "../include/variable.h"
#include <iostream>
Variable::Variable(string symbol) : _symbol(symbol) { 
    _value = NULL;
    _isSearching = false;
    _isMatching = false;
}

string Variable::value() {
    if (!_value)
        return symbol();
    if (_isSearching)
        return getLastSymbol();
    _isSearching = true;
    string result = _value->value();
    _isSearching = false;
    return result; 

    
}

string Variable::getLastSymbol(){
    if (!_value->getVariable())
        return symbol();

    Term* value = _value;
    while (Variable* tempVaribale = value->getVariable()){
        if (tempVaribale->_value == this)
            return tempVaribale->symbol();
        value = tempVaribale->_value;

    }
       
}
string Variable::symbol() const { return _symbol; }

bool Variable::matchForce(Term& term){
    _value = &term;
    return true;
}
bool Variable::match(Term& term) {
    if (!_value){
        _value = &term;
        return true;
    }

    if (_value == &term || &term == this)
        return true;

    if (!_value->getVariable())
        return false;

    _isMatching = true;
    Term* value = _value;
    if (Variable* v = value->getVariable()){
        if (v->_value == this || v->_isMatching)
            return v->matchForce(term);
        else
            return v->match(term);
    }
        

}