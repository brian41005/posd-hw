#include "../include/variable.h"
#include <iostream>
Variable::Variable(string symbol) : _symbol(symbol) { _value = NULL; }

string Variable::value(vector<Term*> record) {
    record.push_back(this);
    string result;
    if (_value) {
        vector<Term*>::iterator index = find(record.begin(), record.end(), this);
        if (index != record.end() && index != record.end() - 1 && record.size() > 1) {
            if (record[record.size() - 2]->getVariable())
                result = record.size() > 2 ? record[record.size() - 2]->symbol():_value->symbol();
            else
                result = record[distance(record.begin(), index)]->symbol();

        } else
            result = _value->value(record);
    } else
        result = _symbol;
    return result;
}

string Variable::symbol() const { return _symbol; }

bool Variable::match(Term& term) {
    if (term.getVariable() && term.symbol() == symbol() && &term == this)
        return true;

    if (_value) {
        return (term.symbol() == _value->symbol() && &term == _value)? true:_value->match(term);
    } else {
        _value = &term;
        return true;
    }
}