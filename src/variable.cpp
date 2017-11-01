#include "../include/variable.h"
#include <iostream>
Variable::Variable(string symbol) : _symbol(symbol) { 
    _value = NULL;
    _isSearching = false;
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

bool Variable::match(Term& term, vector<Variable*> record) {
    record.push_back(this);
    if (_value) {

        vector<Variable*>::iterator index = find(record.begin(), record.end(), this);

        if (index != record.end() && index != record.end() - 1 && record.size() > 1) {
            if (!term.getVariable()) record[record.size() - 2]->_value = &term;
            return true;

        } else {
            return  (term.symbol() == _symbol || this == &term || _value == &term)? true:_value->match(term, record);
        }

    } else {
        _value = &term;
        return true;
    }
}