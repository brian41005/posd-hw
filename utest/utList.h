#ifndef UTLIST_H
#define UTLIST_H

#include <string>
#include <vector>
using std::string;
using std::vector;

#include "../include/atom.h"
#include "../include/list.h"
#include "../include/number.h"
#include "../include/struct.h"
#include "../include/variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST(List, constructor) {
    List l1;
    ASSERT_EQ("[]", l1.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128, 496]"
TEST(List, Numbers) {
    Number n1(8128), n2(496);
    List l1(vector<Term *>{&n1, &n2});
    ASSERT_EQ("[8128, 496]", l1.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao,
// alan_mathison_turing]"
TEST(List, Atoms) {
    Atom a1("terence_tao"), a2("alan_mathison_turing");
    List l1(vector<Term *>{&a1, &a2});
    ASSERT_EQ("[terence_tao, alan_mathison_turing]", l1.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
    Variable v1("X"), v2("Y");
    List l1(vector<Term *>{&v1, &v2});
    ASSERT_EQ("[X, Y]", l1.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
    Atom a1("tom"), a2("terence_tao");
    Number n1(496);
    Variable v1("X");
    List l1(vector<Term *>{&n1, &v1, &a2});
    ASSERT_FALSE(a1.match(l1));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
    Atom a1("terence_tao");
    Number n1(496), n2(8128);
    Variable v1("X");
    List l1(vector<Term *>{&n1, &v1, &a1});
    ASSERT_FALSE(n2.match(l1));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
    Atom a1("terence_tao");
    Number n1(496);
    Variable v1("X");
    List l1(vector<Term *>{&n1, &v1, &a1});
    Struct s1(Atom("s"), vector<Term *>{&v1});
    ASSERT_FALSE(s1.match(l1));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
    Atom a1("terence_tao");
    Number n1(496);
    Variable X("X");
    List l1(vector<Term *>{&n1, &X, &a1});
    Variable Y("Y");
    ASSERT_TRUE(Y.match(l1));
    ASSERT_EQ("[496, X, terence_tao]", l1.symbol());
    ASSERT_EQ("[496, X, terence_tao]", l1.value());
}

// ?- X = [496, X, terence_tao].
// false.QQ
TEST(List, matchToVarOccuredInListShouldFail) {
    Atom a1("terence_tao");
    Number n1(496);
    Variable X("X");
    List l1(vector<Term *>{&n1, &X, &a1});
    ASSERT_EQ("X", X.value());
    ASSERT_TRUE(X.match(l1));
    ASSERT_EQ("[496, X, terence_tao]", X.value());
}

// ?- X = [X].
//  X = [X]
TEST(List, matchToVarOccuredInListShouldSucceed) {
    Variable X("X");
    List l1(vector<Term *>{&X});
    ASSERT_EQ("X", X.value());
    ASSERT_TRUE(X.match(l1));
    ASSERT_EQ("[X]", X.value());
}

// ?- X = [X], X = 1.
//  false.
TEST(List, specialCase1) {
    Variable X("X");
    List l1(vector<Term *>{&X});
    Number n1(1);
    ASSERT_EQ("X", X.value());
    ASSERT_TRUE(X.match(l1));
    ASSERT_EQ("[X]", X.value());
    ASSERT_FALSE(X.match(n1));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
    Atom a1("terence_tao");
    Number n1(496);
    Variable X("X");
    List l1(vector<Term *>{&n1, &X, &a1}), l2(vector<Term *>{&n1, &X, &a1});

    ASSERT_TRUE(l1.match(l2));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
    Atom a1("terence_tao");
    Number n1(496);
    Variable X("X"), Y("Y");
    List l1(vector<Term *>{&n1, &X, &a1}), l2(vector<Term *>{&n1, &Y, &a1});

    ASSERT_TRUE(l1.match(l2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
    Atom a1("terence_tao");
    Number n1(496), n2(8128);
    Variable X("X");
    List l1(vector<Term *>{&n1, &X, &a1}), l2(vector<Term *>{&n1, &n2, &a1});

    ASSERT_TRUE(l1.match(l2));
    ASSERT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
    Atom a1("terence_tao"), a2("alan_mathison_turing");
    Number n1(496);
    Variable X("X"), Y("Y");
    List l1(vector<Term *>{&n1, &X, &a1});

    ASSERT_TRUE(Y.match(l1));
    ASSERT_TRUE(X.match(a2));

    ASSERT_EQ("alan_mathison_turing", X.value());
    ASSERT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
}

// Example:
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
    Atom f("first"), s("second"), t("third");
    List l(vector<Term *>{&f, &s, &t});

    EXPECT_EQ(string("first"), l.head()->symbol());
    EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// // Example:
// // ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
    Atom f("first"), s("second"), t("third");
    List l(vector<Term *>{&f, &s, &t});

    EXPECT_EQ(string("second"), l.tail()->head()->value());
    EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
    Atom f("first"), s("second"), t("third");
    List l1(vector<Term *>{&f});
    List l2(vector<Term *>{&l1, &s, &t});

    EXPECT_EQ("[first]", l2.head()->value());
    EXPECT_EQ("[second, third]", l2.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
    Atom f("first"), s("second"), t("third");
    List l(vector<Term *>{&f, &s, &t});

    EXPECT_EQ("third", l.tail()->tail()->head()->value());
    EXPECT_EQ("[]", l.tail()->tail()->tail()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an
// exception.
TEST(List, emptyExecptionOfHead) {
    List l;

    ASSERT_THROW(l.head(), string);
    try {
        l.head();
    } catch (string s) {
        EXPECT_EQ("Accessing head in an empty list", s);
    }
}

// Given there is a empty list
// When client still want to get the tail of list
// Then it should throw a string: "Accessing tail in an empty list" as an
// exception.
TEST(List, emptyExecptionOfTail) {
    List l;

    ASSERT_THROW(l.tail(), string);
    try {
        l.tail();
    } catch (string s) {
        EXPECT_EQ("Accessing tail in an empty list", s);
    }
}

#endif