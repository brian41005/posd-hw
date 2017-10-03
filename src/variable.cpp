#include "../include/variable.h"
#include <string> 

using namespace std;

Variable::Variable(string symbol): _symbol(symbol){
    this->_value = "";
}

string Variable::value() const{
    return this->_value;
}

string Variable::symbol() const{
    return this->_symbol;
}

bool Variable::match(SimpleObj* simple){
    if (this->_value == ""){
        this->_value = simple->value();
        return true;
    }
    else
        return  this->_value == simple->value();
}