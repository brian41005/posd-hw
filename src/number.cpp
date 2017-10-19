#include "../include/number.h"

Number::Number(double n) {
    ostringstream ostream;
    ostream << fixed << setprecision(12) << n;
    _n = ostream.str();

    int i = _n.find_last_not_of("0");
    if (i != string::npos) {
        _n = _n.substr(0, i + 1);
        if (_n.back() == '.') _n.pop_back();
    }
}

string Number::value() const { return _n; }

string Number::symbol() const { return _n; }

bool Number::match(Term& term) {
    if (Variable* v = term.getVariable()) return v->match(*this);
    return this->symbol() == term.symbol();
}