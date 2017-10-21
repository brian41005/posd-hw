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
    Variable v1("X");
    Number n1(2.7182);
    ASSERT_TRUE(v1.match(n1));
    ASSERT_EQ("2.7182", n1.value());
}

// ?- X=Y, X=1.
// Y=1
TEST(Variable, varY_to_varX_and_num1_to_varX) {
    Variable v1("X"), v2("Y");
    Number n1(1);
    ASSERT_TRUE(v1.match(v2));
    ASSERT_TRUE(v1.match(n1));
    ASSERT_EQ("1", v2.value());
}

// ?- X=Y, Y=1.
// X=1
TEST(Variable, varY_to_varX_and_num1_to_varY) {
    Variable v1("X"), v2("Y");
    Number n1(1);
    ASSERT_TRUE(v1.match(v2));
    ASSERT_TRUE(v2.match(n1));
    ASSERT_EQ("1", v1.value());
}

// ?- X=X, X=1.
// X=1
TEST(Variable, varX_match_varX_and_num1_to_varX) {
    Variable v1("X");
    Number n1(1);
    ASSERT_TRUE(v1.match(v1));
    ASSERT_TRUE(v1.match(n1));
    ASSERT_EQ("1", v1.value());
}

// ?- Y=1, X=Y.
// X=1
TEST(Variable, num1_to_varY_and_varX_match_varY) {
    Variable v1("X"), v2("Y");
    Number n1(1);
    ASSERT_TRUE(v2.match(n1));
    ASSERT_TRUE(v1.match(v2));
    ASSERT_EQ("1", v1.value());
}

// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST(Variable, num1_to_varZ_to_varY_to_varX) {
    Variable v1("X"), v2("Y"), v3("Z");
    Number n1(1);
    ASSERT_TRUE(v1.match(v2));
    ASSERT_TRUE(v2.match(v3));
    ASSERT_TRUE(v3.match(n1));
    ASSERT_EQ("1", v1.value());
    ASSERT_EQ("1", v2.value());
    ASSERT_EQ("1", v3.value());
}

// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST(Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
    Variable v1("X"), v2("Y"), v3("Z");
    Number n1(1);
    ASSERT_TRUE(v1.match(v2));
    ASSERT_TRUE(v1.match(v3));
    ASSERT_TRUE(v3.match(n1));
    ASSERT_EQ("1", v1.value());
    ASSERT_EQ("1", v2.value());
    ASSERT_EQ("1", v3.value());
}

// ?- X = 1, X = Y.
// X = Y, Y = 1
TEST(Variable, X_to_Y_to_1) {
    Variable X("X"), Y("Y");
    Number n1(1);
    ASSERT_TRUE(X.match(n1));
    ASSERT_TRUE(X.match(Y));
    ASSERT_EQ("1", X.value());
    ASSERT_EQ("1", Y.value());
}

// ?- X = Y, X = 1.
// X = Y, Y = 1
TEST(Variable, X_to_1_to_Y) {
    Variable X("X"), Y("Y");
    Number n1(1);
    ASSERT_TRUE(X.match(Y));
    ASSERT_TRUE(X.match(n1));
    ASSERT_EQ("1", X.value());
    ASSERT_EQ("1", Y.value());
}

// s(tom) = X.
TEST(Vaiable, Struct0) {
    Variable X("X");
    Atom a1("tom");
    vector<Term *> v = {&a1};
    Struct s(Atom("s"), v);
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
    vector<Term *> v = {&X};
    Struct s(Atom("s"), v);
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
    vector<Term *> v = {&X};
    Struct s(Atom("s"), v);
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
    //ASSERT_EQ("s(X)", X.value()); //目前這還會爆，因為還是跟前面幾個TA的測資互相矛盾
    
}

// ?- X = X, X = s(X).
// X = s(X)
TEST(Variable, Struct4) {
    Variable X("X");
    Struct s(Atom("s"), vector<Term *>{&X});

    ASSERT_TRUE(X.match(X));
    ASSERT_TRUE(X.match(s));
    
}

// ?- X = s(X), X = X.
// X = s(X)
TEST(Variable, Struct5) {
    Variable X("X");
    Struct s(Atom("s"), vector<Term *>{&X});
    
    ASSERT_TRUE(X.match(s));
    ASSERT_TRUE(X.match(X));
    
}
#endif