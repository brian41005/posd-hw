#include "../include/list.h"
#include "../include/variable.h"

List::List() : _elements() {}

List::List(vector<Term *> elements) : _elements(elements) {}

Term *List::head() const {
    if (_elements.empty()) throw string("Accessing head in an empty list");
    return _elements.front();
}

List *List::tail() const {
    if (_elements.empty()) throw string("Accessing tail in an empty list");
    return new List(vector<Term *>(_elements.begin() + 1, _elements.end()));
}

string List::symbol() const {
    ostringstream out;
    out << "[";
    if (!_elements.empty()) out << _elements[0]->symbol();
    for (auto t = _elements.begin() + 1; t < _elements.end(); t++)
        out << ", " << (*t)->symbol();
    out << "]";
    return out.str();
}

string List::value(vector<Term *> record) {
    record.push_back(this);
    ostringstream out;
    out << "[";
    if (!_elements.empty()) out << _elements[0]->value(record);
    for (auto t = _elements.begin() + 1; t < _elements.end(); t++)
        out << ", " << (*t)->value(record);
    out << "]";
    return out.str();
}

bool List::match(Term &term) {
    if (List *s = term.getList()) {
        if (s->_elements.size() == _elements.size()) {
            int failTime = 0;
            for (int i = 0; i < _elements.size(); i++)
                failTime += (!_elements[i]->match(*s->_elements[i]));
            return failTime == 0;
        }
        return false;
    } else if (Variable *v = term.getVariable()) {
        return v->match(*this);
    } else
        return false;
}
