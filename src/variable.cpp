#include "../include/variable.h"
#include <iostream>
Variable::Variable(string symbol) : _symbol(symbol) { _value = NULL; }

string Variable::value(vector<Term*> record) {
    record.push_back(this);
    string result;
    if (_value) {
        vector<Term*>::iterator index =
            find(record.begin(), record.end(), this);
        if (index != record.end() && index != record.end() - 1 &&
            record.size() > 1) {
            if (record[record.size() - 2]->getVariable())
                result = record.size() > 2 ? record[record.size() - 2]->symbol()
                                           : _value->symbol();
            else
                result = record[distance(record.begin(), index)]->symbol();

        } else
            result = _value->value(record);
    } else
        result = _symbol;
    return result;
}

string Variable::symbol() const { return _symbol; }

bool Variable::match(Term& term, vector<Variable*> record) {
    record.push_back(this);
    if (_value) {
        vector<Variable*>::iterator index =
            find(record.begin(), record.end(), this);
        if (index != record.end() && index != record.end() - 1 &&
            record.size() > 1) {
            if (!term.getVariable()) record[record.size() - 2]->_value = &term;
            return true;

        } else {
            if (term.symbol() == _symbol || this == &term) return true;
            if (_value == &term) return true;
            return _value->match(term, record);
        }
        //
    } else {
        _value = &term;
        return true;
    }
}