#include "../include/list.h"
#include "../include/variable.h"

List::List() : _elements() {}

List::List(const vector<Term *> &elements) : _elements(elements) {}

Term *List::head() const { return _elements.front(); }

List *List::tail() const {
    vector<Term *>::const_iterator first = _elements.begin() + 1;
    vector<Term *>::const_iterator last = _elements.end();
    return new List(vector<Term *>(first, last));
}

string List::symbol() const {
    ostringstream out;
    out << "[";
    if (_elements.size() > 0) out << _elements[0]->symbol();
    for (auto t = _elements.begin() + 1; t < _elements.end(); t++)
        out << ", " << (*t)->symbol();
    out << "]";
    return out.str();
}
string List::value() const {
    ostringstream out;
    out << "[";
    if (_elements.size() > 0) out << _elements[0]->value();
    for (auto t = _elements.begin() + 1; t < _elements.end(); t++)
        out << ", " << (*t)->value();
    out << "]";
    return out.str();
}
bool List::match(Term &term) {
    if (List *s = term.getList()) {
        //
        return false;
    } else if (Variable *v = term.getVariable()) {
        return v->match(*this);
    } else
        return false;
}
