#include "../include/variable.h"

Variable::Variable(string symbol) : _symbol(symbol) { _value = NULL; }

string Variable::value(vector<Term*> record) {
    string result;
    record.push_back(this);

    if (_value){
        vector<Term*>::iterator index = find(record.begin(), record.end(), this);
        if (index != record.end() && index != record.end()-1 && record.size() > 1){

            if (record[record.size()-2]->getVariable()) 
                result = record[record.size()-2]->symbol(); 
            else
                result = _symbol;

        }else 
            result = _value->value(record);
    }
    else
        result = _symbol;
    return result;
}


string Variable::symbol() const { return _symbol; }

bool Variable::match(Term& term) {
    if (_value) {
        if (term.symbol() == _value->symbol() && &term == _value) return true;
        return _value->match(term);
    } 
    else{
        if (Variable* v = term.getVariable()) {
            if (v->symbol() != symbol() && &term != this) _value = &term;
        } else
            _value = &term;
        return true;
    }
        
}