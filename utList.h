#ifndef UTLIST_H
#define UTLIST_H

#include <string>
#include <vector>
using std::string;
using std::vector;

#include "include/atom.h"
#include "include/list.h"
#include "include/number.h"
#include "include/struct.h"
#include "include/variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST(List, constructor) {
    List l1;
    ASSERT_EQ("[]", l1.symbol());
}

// Given there are two perfect numbers: 8128
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128]"
TEST(List, Numbers) {
    Number n1(8128);
    vector<Term*> v1 = {&n1};
    List l1(v1);
    ASSERT_EQ("[8128]", l1.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao,
// alan_mathison_turing]"
TEST(List, Atoms) {
    Atom a1("terence_tao"), a2("alan_mathison_turing");
    List l1(vector<Term*>{&a1, &a2});
    ASSERT_EQ("[terence_tao, alan_mathison_turing]", l1.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
    Variable v1("X"), v2("Y");
    List l1(vector<Term*>{&v1, &v2});
    ASSERT_EQ("[X, Y]", l1.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
    Atom a1("tom"), a2("terence_tao");
    Number n1(496);
    Variable v1("X");
    List l1(vector<Term*>{&n1, &v1, &a2});
    ASSERT_FALSE(a1.match(l1));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
    Atom a1("terence_tao");
    Number n1(496), n2(8128);
    Variable v1("X");
    List l1(vector<Term*>{&n1, &v1, &a1});
    ASSERT_FALSE(n2.match(l1));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
    Atom a1("terence_tao");
    Number n1(496);
    Variable v1("X");
    List l1(vector<Term*>{&n1, &v1, &a1});
    Struct s1(Atom("s"), vector<Term*>{&v1});
    ASSERT_FALSE(s1.match(l1));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
    Atom a1("terence_tao");
    Number n1(496);
    Variable X("X");
    List l1(vector<Term*>{&n1, &X, &a1});
    Variable Y("Y");
    ASSERT_TRUE(Y.match(l1));
    ASSERT_EQ("[496, X, terence_tao]", l1.symbol());
    ASSERT_EQ("[496, X, terence_tao]", l1.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
    Atom a1("terence_tao");
    Number n1(496);
    Variable X("X");
    List l1(vector<Term*>{&n1, &X, &a1});
    X.match(l1);
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {}

// Example:
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
// TEST(List, headAndTailMatching1) {
//     Atom f("first"), s("second"), t("third");
//     vector<Term *> args = {&f, &s, &t};
//     List l(args);

//     EXPECT_EQ(string("first"), l.head()->symbol());
//     EXPECT_EQ(string("[second, third]"), l.tail()->value());
// }

// // Example:
// // ?- [first, second, third] = [first, H|T].
// // H = second, T = [third].
// TEST(List, headAndTailMatching2) {
//     Atom f("first"), s("second"), t("third");
//     vector<Term *> args = {&f, &s, &t};
//     List l(args);

//     EXPECT_EQ(string("second"), l.tail()->head()->value());
//     EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
// }

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an
// exception.
TEST(List, emptyExecptionOfHead) {}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an
// exception.
TEST(List, emptyExecptionOfTail) {}

#endif