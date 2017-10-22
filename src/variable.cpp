#include "../include/variable.h"

Variable::Variable(string symbol) : _symbol(symbol) { _value = NULL; }

string Variable::value(vector<Term*> record) {
    string result;
    record.push_back(this);

    if (_value){
        set<Term*> tempSet( record.begin(), record.end());
        if (((record.front() == record.back()) || (tempSet.size() !=record.size())) && record.size() > 1)
            if (!record[record.size()-2]->getList() && !record[record.size()-2]->getStruct()) {
                if (_value->getVariable())  result = _value->symbol();
                else result = record[record.size()-2]->symbol();
            }
            else
                result = _symbol;
        else {
            result = _value->value(record);
        }
    }
    else
        result = _symbol;
    return result;
}


string Variable::symbol() const { return _symbol; }

bool Variable::match(Term& term) {
    if (_value == NULL) {
        if (Variable* v = term.getVariable()) {
            if (v->symbol() != symbol() && &term != this) _value = &term;

        } else
            _value = &term;
        return true;
    } 
    else{
        if (term.symbol() == _value->symbol() && &term == _value) return true;
        return _value->match(term);
    }
        
}