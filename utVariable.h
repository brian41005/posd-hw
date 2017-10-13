#ifndef UTVARIABLE_H
#define UTVARIABLE_H

#include "include/variable.h"
#include "include/atom.h"
#include "include/number.h"
#include "include/struct.h"
#include <iostream>

TEST(Variable, constructor){
  Variable X("X");
  ASSERT_EQ("X", X.symbol());
}

TEST(Variable , matching){
  Atom tom("tom");
  Variable X("X");
  X.match(tom);
  ASSERT_EQ( "tom", X.value());
}

TEST (Variable , haveValue){
  Atom tom ("tom");
  Atom jerry ("jerry");
  Variable X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_FALSE(X.match(jerry));
}

// ?- X=2.7182.
// X=2.7182
TEST(Variable , numE_to_varX){
    Variable v1("X");
    double n = 2.718211;
    Number n1(n);
    ASSERT_TRUE(v1.match(n1));
    ASSERT_EQ("2.718211", n1.value());
}

// ?- X=Y, X=1.
// Y=1
TEST (Variable, varY_to_varX_and_num1_to_varX) {
    Variable v1("X"), v2("Y");
    int n = 1;
    Number n1(n);
    ASSERT_TRUE(v1.match(v2));
    //cout << "out\"" <<v1.value() << "\""<< endl;
    ASSERT_TRUE(v1.match(n1));
    ASSERT_EQ("1", v2.value());
}
  
// ?- X=Y, Y=1.
// X=1
TEST (Variable, varY_to_varX_and_num1_to_varY) {
    // Variable v1("X"), v2("Y");
    // int n = 1;
    // Number n1(n);
    // ASSERT_TRUE(v1.match(v2));
    // ASSERT_TRUE(v2.match(n1));
    // ASSERT_EQ("1", v1.value());
}

// ?- X=X, X=1.
// X=1
TEST (Variable, varX_match_varX_and_num1_to_varX) {

}

// ?- Y=1, X=Y.
// X=1
TEST (Variable, num1_to_varY_and_varX_match_varY) {

}

// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varY_to_varX) {

}

// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
  
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
TEST (Variable, Struct1) {

}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST (Variable, Struct2) {
  
}

#endif