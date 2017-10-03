#ifndef UTTERM_H
#define UTTERM_H

#include "include/atom.h"
#include "include/number.h"
#include "include/variable.h"

//test Number.value()
TEST (Number, ctor) {
    Number n1(-1), n2(0), n3(1);
    ASSERT_EQ(n1.value(), "-1");
    ASSERT_EQ(n2.value(), "0");
    ASSERT_EQ(n3.value(), "1");


}

//test Number.symbol()
TEST (Number, symbol) {
    Number n1(-1), n2(0), n3(1);
    ASSERT_EQ(n1.symbol(), "-1");
    ASSERT_EQ(n2.symbol(), "0");
    ASSERT_EQ(n3.symbol(), "1");
}

//?- 25=25.
//true.
TEST (Number, matchSuccess) {
    Number* n1 = new Number(-1);
    Number* n2 = new Number(-1);
    ASSERT_TRUE(n1->match(n2));
    delete n1, n2;

    n1 = new Number(0);
    n2 = new Number(0);
    ASSERT_TRUE(n1->match(n2));
    delete n1, n2;

    n1 = new Number(1);
    n2 = new Number(1);
    ASSERT_TRUE(n1->match(n2));
    delete n1, n2;

    n1 = new Number(25);
    n2 = new Number(25);
    ASSERT_TRUE(n1->match(n2));
    delete n1, n2;
}

//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
    Number* n1 = new Number(-1);
    Number* n2 = new Number(-2);
    ASSERT_FALSE(n1->match(n2));
    delete n1, n2;

    n1 = new Number(0);
    n2 = new Number(1);
    ASSERT_FALSE(n1->match(n2));
    delete n1, n2;

    n1 = new Number(1);
    n2 = new Number(100);
    ASSERT_FALSE(n1->match(n2));
    delete n1, n2;

    n1 = new Number(25);
    n2 = new Number(0);
    ASSERT_FALSE(n1->match(n2));
    delete n1, n2;
}

//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
    Number* n1 = new Number(-1);
    Atom* a2 = new Atom("tom");
    ASSERT_FALSE(n1->match(a2));
    delete n1, a2;
}

//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
    Number* n1 = new Number(25);
    Variable* v2 = new Variable("X");
    ASSERT_TRUE(n1->match(v2));
    ASSERT_EQ(v2->value(), "25");
    ASSERT_TRUE(n1->match(v2));
    delete n1, v2;


}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
    Atom* a1 = new Atom("tom");
    Number* n2 = new Number(25);
    ASSERT_FALSE(a1->match(n2));
    delete a1, n2;
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    Atom* a1 = new Atom("tom");
    Variable* v2 = new Variable("X");
    ASSERT_TRUE(a1->match(v2));
    ASSERT_EQ(v2->value(), "tom");
    delete a1, v2;
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
    Atom* a1 = new Atom("tom");
    Variable* v2 = new Variable("X");
    ASSERT_TRUE(v2->match(a1));
    ASSERT_TRUE(a1->match(v2));
    ASSERT_EQ(v2->value(), "tom");
    delete a1, v2;
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
    Atom* a1 = new Atom("tom");
    Atom* a2 = new Atom("jerry");
    Variable* v3 = new Variable("X");

    ASSERT_TRUE(v3->match(a2));
    ASSERT_FALSE(a1->match(v3));
    ASSERT_EQ(v3->value(), "jerry");
    delete a1, a2, v3;
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
    Variable* v1 = new Variable("X");
    Number* n2 = new Number(5);
    ASSERT_TRUE(v1->match(n2));
    ASSERT_EQ(v1->value(), "5");
    delete v1, n2;
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
    Variable* v1 = new Variable("X");
    Number* n2 = new Number(25);
    Number* n3 = new Number(100);
    ASSERT_TRUE(v1->match(n2));
    ASSERT_FALSE(v1->match(n3));
    ASSERT_EQ(v1->value(), "25");
    delete v1, n2, n3;
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
    Variable* v1 = new Variable("X");
    Atom* a2 = new Atom("tom");
    Number* n3 = new Number(25);
    ASSERT_TRUE(v1->match(a2));
    ASSERT_FALSE(v1->match(n3));
    ASSERT_EQ(v1->value(), "tom");
    delete v1, a2, n3;
}

//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
    Variable* v1 = new Variable("X");
    Atom* a2 = new Atom("tom");
    Number* n3 = new Number(25);
    ASSERT_TRUE(a2->match(v1));
    ASSERT_FALSE(n3->match(v1));
    ASSERT_EQ(v1->value(), "tom");
    delete v1, a2, n3;
}

//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
    Variable* v1 = new Variable("X");
    Atom* a2 = new Atom("tom");
    Atom* a3 = new Atom("tom");
    ASSERT_TRUE(v1->match(a2));
    ASSERT_TRUE(v1->match(a2));
    ASSERT_TRUE(v1->match(a3));
    ASSERT_EQ(v1->value(), "tom");
    delete v1, a2, a3;
}
#endif