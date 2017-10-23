#ifndef UTVARIABLE_H
#define UTVARIABLE_H

#include <iostream>
#include "../include/atom.h"
#include "../include/number.h"
#include "../include/struct.h"
#include "../include/variable.h"

TEST(Variable, constructor) {
    Variable X("X");
    ASSERT_EQ("X", X.symbol());
}

TEST(Variable, matching) {
    Atom tom("tom");
    Variable X("X");
    X.match(tom);
    ASSERT_EQ("tom", X.value());
}

TEST(Variable, haveValue) {
    Atom tom("tom");
    Atom jerry("jerry");
    Variable X("X");
    ASSERT_TRUE(X.match(tom));
    ASSERT_FALSE(X.match(jerry));
}

// ?- X=2.7182.
// X=2.7182
TEST(Variable, numE_to_varX) {
    Variable X("X");
    Number n1(2.7182);
    ASSERT_TRUE(X.match(n1));
    ASSERT_EQ("2.7182", n1.value());
}

// ?- X=Y, X=1.
// Y=1
TEST(Variable, varY_to_varX_and_num1_to_varX) {
    Variable X("X"), Y("Y");
    Number n1(1);
    ASSERT_TRUE(X.match(Y));
    ASSERT_TRUE(X.match(n1));
    ASSERT_EQ("1", Y.value());
}

// ?- X=Y, Y=1.
// X=1, Y=1.
TEST(Variable, varY_to_varX_and_num1_to_varY) {
    Variable X("X"), Y("Y");
    Number n1(1);
    ASSERT_TRUE(X.match(Y));
    ASSERT_TRUE(Y.match(n1));
    ASSERT_EQ("1", X.value());
    ASSERT_EQ("1", Y.value());
}

// ?- X=X, X=1.
// X=1.
TEST(Variable, varX_match_varX_and_num1_to_varX) {
    Variable X("X");
    Number n1(1);
    ASSERT_TRUE(X.match(X));
    ASSERT_TRUE(X.match(n1));
    ASSERT_EQ("1", X.value());
}

// ?- Y=1, X=Y.
// X=1
TEST(Variable, num1_to_varY_and_varX_match_varY) {
    Variable X("X"), Y("Y");
    Number n1(1);
    ASSERT_TRUE(Y.match(n1));
    ASSERT_TRUE(X.match(Y));
    ASSERT_EQ("1", X.value());
    ASSERT_EQ("1", Y.value());
}

// ?- X=Y, Y=Z, Z=1.
// X=1, Y=1, Z=1
TEST(Variable, num1_to_varZ_to_varY_to_varX) {
    Variable X("X"), Y("Y"), Z("Z");
    Number n1(1);
    ASSERT_TRUE(X.match(Y));
    ASSERT_TRUE(Y.match(Z));
    ASSERT_TRUE(Z.match(n1));
    ASSERT_EQ("1", X.value());
    ASSERT_EQ("1", Y.value());
    ASSERT_EQ("1", Z.value());
}

// ?- X=Y, X=Z, Z=1.
// X=1, Y=1, Z=1
TEST(Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
    Variable X("X"), Y("Y"), Z("Z");
    Number n1(1);
    ASSERT_TRUE(X.match(Y));
    ASSERT_TRUE(Y.match(Z));
    ASSERT_TRUE(Z.match(n1));
    ASSERT_EQ("1", X.value());
    ASSERT_EQ("1", Y.value());
    ASSERT_EQ("1", Z.value());
}

// X=Q, Y=W, Z=X.
// X = Q
// Y = W
// Z = Q
TEST(Variable, X_to_Q_and_Y_to_W_and_Z_to_X) {
    Variable X("X"), Y("Y"), Z("Z"), Q("Q"), W("W");

    ASSERT_TRUE(X.match(Q));
    ASSERT_TRUE(Y.match(W));
    ASSERT_TRUE(Z.match(X));
    ASSERT_EQ("Q", X.value());
    ASSERT_EQ("W", Y.value());
    ASSERT_EQ("Q", Z.value());
}
// s(tom) = X.
TEST(Vaiable, Struct0) {
    Variable X("X");
    Atom a1("tom");
    Struct s(Atom("s"), vector<Term *>{&a1});
    ASSERT_TRUE(s.match(X));
    ASSERT_EQ("s(tom)", X.value());
    ASSERT_TRUE(s.match(X));
    ASSERT_TRUE(X.match(s));
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
TEST(Variable, Struct1) {
    Variable X("X"), Y("Y");
    Struct s(Atom("s"), vector<Term *>{&X});
    ASSERT_EQ("s(X)", s.symbol());
    ASSERT_TRUE(Y.match(s));
    ASSERT_EQ("Y", Y.symbol());
    ASSERT_EQ("s(X)", Y.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST(Variable, Struct2) {
    Variable X("X"), Y("Y");
    Struct s(Atom("s"), vector<Term *>{&X});
    ASSERT_EQ("s(X)", s.symbol());
    ASSERT_TRUE(Y.match(s));
    Atom a1("teddy");
    ASSERT_TRUE(X.match(a1));
    ASSERT_EQ("Y", Y.symbol());
    ASSERT_EQ("s(teddy)", Y.value());
}

// ?- X = s(X).
// X = s(X)
TEST(Variable, Struct3) {
    Variable X("X");
    Struct s(Atom("s"), vector<Term *>{&X});
    ASSERT_TRUE(X.match(s));
    ASSERT_EQ("s(X)", X.value());
}

// ?- X = X, X = s(X).
// X = s(X)
TEST(Variable, Struct4) {
    Variable X("X");
    Struct s(Atom("s"), vector<Term *>{&X});

    ASSERT_TRUE(X.match(X));
    ASSERT_TRUE(X.match(s));
    ASSERT_EQ("s(X)", X.value());
}

// ?- X = s(X), X = X.
// X = s(X)
TEST(Variable, Struct5) {
    Variable X("X");
    Struct s(Atom("s"), vector<Term *>{&X});

    ASSERT_TRUE(X.match(s));
    ASSERT_EQ("s(X)", X.value());
    ASSERT_TRUE(X.match(X));
}
// ?- X=Y, Y=Z, Z=1, Q=s(X).
// Q = s(1),
// X = Y, Y = Z, Z = 1
TEST(Variable, Struct6) {
    Variable X("X"), Y("Y"), Z("Z"), Q("Q");
    Number n1(1);
    Struct s(Atom("s"), vector<Term *>{&n1});

    ASSERT_TRUE(X.match(Y));
    ASSERT_TRUE(Y.match(Z));
    ASSERT_TRUE(Z.match(n1));
    ASSERT_TRUE(Q.match(s));
    ASSERT_EQ("s(1)", Q.value());
    ASSERT_EQ("1", X.value());
    ASSERT_EQ("1", Y.value());
    ASSERT_EQ("1", Z.value());
}

// -? X=Y, Y=X, Z=s(X).
// Z = s(Y),
// X = Y
TEST(Variable, Struct7) {
    Variable X("X"), Y("Y"), Z("Z");
    Struct s(Atom("s"), vector<Term *>{&X});
    ASSERT_TRUE(X.match(Y));
    ASSERT_TRUE(Y.match(X));
    ASSERT_TRUE(Z.match(s));
    ASSERT_EQ("Y", X.value());
    ASSERT_EQ("X", Y.value());
    ASSERT_EQ("s(Y)", Z.value());
}

// ?- X=Y, Y=Z, Z=X, Q=s(X).
// Q = s(Z),
// X = Y, Y = Z
TEST(Variable, Struct8) {
    Variable X("X"), Y("Y"), Z("Z"), Q("Q");
    Struct s(Atom("s"), vector<Term *>{&X});

    ASSERT_TRUE(X.match(Y));
    ASSERT_TRUE(Y.match(Z));
    ASSERT_TRUE(Z.match(X));
    ASSERT_TRUE(Q.match(s));
    ASSERT_EQ("Y", Z.value());
    ASSERT_EQ("X", Y.value());
    ASSERT_EQ("s(Z)", Q.value());
}

#endif