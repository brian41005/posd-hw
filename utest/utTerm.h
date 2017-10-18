#ifndef UTTERM_H
#define UTTERM_H

#include "../include/atom.h"
#include "../include/number.h"
#include "../include/variable.h"

//test Number.value()
TEST (Number, ctor) {
    Number n1(-1), n2(0), n3(01);
    ASSERT_EQ("-1", n1.value());
    ASSERT_EQ("0", n2.value());
    ASSERT_EQ("1", n3.value());

    Number n4(-1.0), n5(0.1030), n6(3.1234560), n7(1.414);
    ASSERT_EQ("-1", n4.value());
    ASSERT_EQ("0.103", n5.value());
    ASSERT_EQ("3.123456", n6.value());
    ASSERT_EQ("1.414", n7.value());

    Number n8(1.000000000001), n9(1.000005), n10(3.0100), n11(1.999999), n12(1.0000000000001);
    ASSERT_EQ("1.000000000001", n8.value());
    ASSERT_EQ("1.000005", n9.value());
    ASSERT_EQ("3.01", n10.value());
    ASSERT_EQ("1.999999", n11.value());
    ASSERT_EQ("1", n12.value());


}

//test Number.symbol()
TEST (Number, symbol) {
    Number n1(-1), n2(0), n3(1);
    ASSERT_EQ("-1", n1.symbol());
    ASSERT_EQ("0", n2.symbol());
    ASSERT_EQ("1", n3.symbol());
}

//?- 25=25.
//true.
TEST (Number, matchSuccess) {
    Number n1(25);
    Number n2(25);
    ASSERT_TRUE(n1.match(n2));
}

//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
    Number n1(25), n2(0);
    ASSERT_FALSE(n1.match(n2));
}

//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
    Number n1(-1);
    Atom a2("tom");
    ASSERT_FALSE(n1.match(a2));
}

//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
    Number n1(25);
    Variable v2("X");
    ASSERT_TRUE(n1.match(v2));
    ASSERT_EQ("25", v2.value());
    ASSERT_TRUE(n1.match(v2));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
    Atom a1("tom");
    Number n2(25);
    ASSERT_FALSE(a1.match(n2));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    Atom a1("tom");
    Variable v2("X");
    ASSERT_TRUE(a1.match(v2));
    ASSERT_EQ("tom", v2.value());
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
    Atom a1("tom");
    Variable v2("X");
    ASSERT_TRUE(v2.match(a1));
    ASSERT_TRUE(a1.match(v2));
    ASSERT_EQ("tom", v2.value());
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
    Atom a1("tom"), a2("jerry");
    Variable v3("X");
    ASSERT_TRUE(v3.match(a2));
    ASSERT_FALSE(a1.match(v3));
    ASSERT_EQ("jerry", v3.value());
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
    Variable v1("X");
    Number n2(5);
    ASSERT_TRUE(v1.match(n2));
    ASSERT_EQ("5", v1.value());
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
    Variable v1("X");
    Number n2(25);
    Number n3(100);
    ASSERT_TRUE(v1.match(n2));
    ASSERT_FALSE(v1.match(n3));
    ASSERT_EQ("25", v1.value());
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
    Variable v1("X");
    Atom a2("tom");
    Number n3(25);
    ASSERT_TRUE(v1.match(a2));
    ASSERT_FALSE(v1.match(n3));
    ASSERT_EQ("tom", v1.value());
}

//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
    Variable v1("X");
    Atom a2("tom");
    Number n3(25);
    ASSERT_TRUE(a2.match(v1));
    ASSERT_FALSE(n3.match(v1));
    ASSERT_EQ("tom", v1.value());
}

//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
    Variable v1("X");
    Atom a2("tom");
    Atom a3("tom");
    ASSERT_TRUE(v1.match(a2));
    ASSERT_TRUE(v1.match(a2));
    ASSERT_TRUE(v1.match(a3));
    ASSERT_EQ("tom", v1.value());
}

//?- X=X.
//true.
TEST(Var, reAssignItself){
    Variable v1("X");
    ASSERT_TRUE(v1.match(v1));
}

//?- X=X, X=Y, X=Z.
//X = Y, Y = Z
TEST(Var, reAssignDifferentVar){
    Variable v1("X"), v2("Y"), v3("Z");
    ASSERT_TRUE(v1.match(v1));
    ASSERT_TRUE(v1.match(v2));
    ASSERT_TRUE(v1.match(v3));
}


#endif