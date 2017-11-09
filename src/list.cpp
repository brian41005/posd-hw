#include "../include/list.h"
#include "../include/variable.h"
#include <iostream>
List::List():Struct(){
}
List::List(vector<Term*> terms){
    if(terms.size() > 0){
        _terms.push_back(terms[0]);
        _terms.push_back(new List(vector<Term*>(terms.begin() + 1, terms.end())));
    }
        
}
List::List(Term* head = nullptr, Term* tail = nullptr):Struct(Atom("."), head, tail) {}

Term *List::head() const {
    if (_terms.empty()) throw string("Accessing head in an empty list");
    return _terms.front();
}

List *List::tail() const {
    if (!(_terms.size() > 1)) throw string("Accessing tail in an empty list");
    return _terms[1]->getList();
}

string List::symbol() {
    ostringstream out;
    out << "[";
    List *list = getList();
    while(list){
        if(list->_terms.empty())
            break;
        out << (((list != this) ? ", " : "") + list->_terms[0]->symbol());

        if(list->_terms.size() > 1)
            list = list->_terms[1]->getList();
        else
            break;
    }

    out << "]";
    return out.str();
}

string List::value() {
    ostringstream out;
    out << "[";
    List *list = getList();
    while(list){
        if(list->_terms.empty())
            break;
        out << (((list != this) ? ", " : "") + list->_terms[0]->value());

        if(list->_terms.size() > 1)
            list = list->_terms[1]->getList();
        else
            break;
    }

    
    out << "]";
    return out.str();
}
