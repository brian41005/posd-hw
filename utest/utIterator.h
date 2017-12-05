#ifndef UTITERATOR_H
#define UTITERATOR_H

#include <iostream>
#include "./include/atom.h"
#include "./include/iterator.h"
#include "./include/list.h"
#include "./include/nullIterator.h"
#include "./include/number.h"
#include "./include/struct.h"
#include "./include/variable.h"
using std::cout;
using std::endl;

TEST(Iterator, test) {
    Number one(1);
    Iterator<Term *> *it = one.createIterator();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

TEST(Iterator, number_nullIterator) {
    Number one(1);
    Iterator<Term *> *it = one.createIterator();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

TEST(Iterator, variable_nullIterator) {
    Variable X("X");
    Iterator<Term *> *it = X.createIterator();
    ASSERT_EQ("X", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

TEST(Iterator, atom_nullIterator) {
    Atom tom("tom");
    Iterator<Term *> *it = tom.createIterator();
    ASSERT_EQ("tom", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

TEST(Iterator, struct_iterator) {
    // s(X, tom, 1.22)
    Variable X("X");
    Atom tom("tom");
    Number n(1.22);
    Struct s(Atom("s"), {&X, &tom, &n});
    Iterator<Term *> *it = s.createBFSIterator();
    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("tom", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("1.22", it->currentItem()->symbol());
    it->next();

    ASSERT_TRUE(it->isDone());
}

TEST(Iterator, complex_struct_iterator) {
    // triangle(point(1, 2), point(2, 3), point(4, 5));
    Number one(11);
    Number two(22);
    Number three(33);
    Number four(44);
    Number five(55);

    Struct p1(Atom("point"), {&one, &two});
    Struct p2(Atom("point"), {&two, &three});
    Struct p3(Atom("point"), {&four, &five});
    Struct t(Atom("triangle"), {&p1, &p2, &p3});
    ASSERT_EQ("triangle(point(11, 22), point(22, 33), point(44, 55))",
              t.symbol());
    Iterator<Term *> *it = t.createBFSIterator();
    it->first();  // initialize

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("point(11, 22)", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("point(22, 33)", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("point(44, 55)", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("11", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("22", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("22", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("33", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("44", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("55", it->currentItem()->symbol());
    it->next();

    ASSERT_TRUE(it->isDone());
}

TEST(BFSIterator, struct_bfs) {
    Variable X("X");
    Number two(2);
    Number three(3);

    Struct s(Atom("s"), {&X});
    Struct s1(Atom("s"), {&s, &two, &three});
    Iterator<Term *> *it = s1.createBFSIterator();
    it->first();  // initialize

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("s(X)", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("3", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_TRUE(it->isDone());
}

TEST(DFSIterator, struct_dfs) {
    Variable X("X");
    Number two(2);
    Number three(3);
    Struct s(Atom("s"), {&X});
    Struct s1(Atom("s"), {&s, &two, &three});
    Iterator<Term *> *it = s1.createDFSIterator();
    it->first();  // initialize

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("s(X)", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("3", it->currentItem()->symbol());
    it->next();

    ASSERT_TRUE(it->isDone());
}

TEST(BFSIterator, simple_list_iterator) {
    // [496, X, terence_tao]
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    List l({&n, &X, &terence_tao});
    Iterator<Term *> *it = l.createDFSIterator();

    it->first();  // initialize

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("496", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("terence_tao", it->currentItem()->symbol());
    it->next();

    ASSERT_TRUE(it->isDone());
}

TEST(BFSIterator, complex_list_bfsiterator) {
    // [[496, X, terence_tao], tom, jerry]
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    List l({&n, &X, &terence_tao});
    Atom tom("tom");
    Atom jerry("jerry");
    List l2({&l, &tom, &jerry});

    Iterator<Term *> *it = l2.createBFSIterator();

    it->first();  // initialize

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("[496, X, terence_tao]", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("tom", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("jerry", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("496", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("terence_tao", it->currentItem()->symbol());
    it->next();

    ASSERT_TRUE(it->isDone());
}

TEST(DFSIterator, complex_list_dfsiterator) {
    // [[496, X, terence_tao], tom, jerry]
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    List l({&n, &X, &terence_tao});
    Atom tom("tom");
    Atom jerry("jerry");
    List l2({&l, &tom, &jerry});

    Iterator<Term *> *it = l2.createDFSIterator();

    it->first();  // initialize

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("[496, X, terence_tao]", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("496", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("terence_tao", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("tom", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("jerry", it->currentItem()->symbol());
    it->next();

    ASSERT_TRUE(it->isDone());
}

TEST(BFSIterator, complex_list_bfsiterator2) {
    // [[[496, X, terence_tao], tom, jerry], s(X, Y, [1, 2]), tom]
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    List l({&n, &X, &terence_tao});

    Atom tom("tom");
    Variable Y("Y");
    Number one(1);
    Number two(2);
    List l3({&one, &two});
    Struct s(Atom("s"), {&X, &Y, &l3});
    List l4({&l, &s, &tom});
    ASSERT_EQ("[[496, X, terence_tao], s(X, Y, [1, 2]), tom]", l4.symbol());

    Iterator<Term *> *it = l4.createBFSIterator();
    it->first();  // initialize

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("[496, X, terence_tao]", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("s(X, Y, [1, 2])", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("tom", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("496", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("terence_tao", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("[1, 2]", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_FALSE(it->isDone());

    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST(DFSIterator, complext_list_dfsiterator2) {
    // [[[496, X, terence_tao], tom, jerry], s(X, Y, [1, 2]), tom]
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    List l({&n, &X, &terence_tao});

    Atom tom("tom");
    Variable Y("Y");
    Number one(1);
    Number two(2);
    List l3({&one, &two});
    Struct s(Atom("s"), {&X, &Y, &l3});
    List l4({&l, &s, &tom});
    ASSERT_EQ("[[496, X, terence_tao], s(X, Y, [1, 2]), tom]", l4.symbol());

    Iterator<Term *> *it = l4.createDFSIterator();
    it->first();  // initialize
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("[496, X, terence_tao]", it->currentItem()->symbol());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("496", it->currentItem()->symbol());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("terence_tao", it->currentItem()->symbol());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("s(X, Y, [1, 2])", it->currentItem()->symbol());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("Y", it->currentItem()->symbol());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("[1, 2]", it->currentItem()->symbol());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("1", it->currentItem()->symbol());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("2", it->currentItem()->symbol());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("tom", it->currentItem()->symbol());

    it->next();
    ASSERT_TRUE(it->isDone());
}
/*
TEST(Iterator, empty_list_bfs) {
    // [[], []]
    List l1;
    List l2;
    List l3({ &l1, &l2 });

    Iterator<Term*> *it = l3.createBFSIterator();
    it->first();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("[]", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("[]", it->currentItem()->symbol());
    it->next();

    ASSERT_TRUE(it->isDone());
}
*/

TEST(Iterator, empty_struct_bfs) {
    // s(s(), s(2))
    Struct s1(Atom("s"), {});
    Number two(2);
    Struct s2(Atom("s"), {&two});
    Struct s3(Atom("s"), {&s1, &s2});
    Iterator<Term *> *it = s3.createBFSIterator();

    it->first();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("s()", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("s(2)", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();

    ASSERT_TRUE(it->isDone());
}

TEST(iterator, combo1_BFS) {
    Atom bun("bun");
    Atom beefPatty("beefPatty");
    Atom shreddedLettuce("shreddedLettuce");
    Atom sauce("sauce");
    Atom cheese("cheese");
    Atom pickleSlice1("pickleSlice1");
    Atom pickleSlice2("pickleSlice2");
    Atom onion1("onion1");
    Atom onion2("onion2");
    Atom coke("coke");
    Atom fries1("fries1");
    Atom fries2("fries2");
    List pickleSlice({&pickleSlice1, &pickleSlice2});
    List onion({&onion1, &onion2});
    List fries({&fries1, &fries2});
    Struct bigMac(Atom("bigMac"), {&bun, &beefPatty, &shreddedLettuce, &sauce,
                                   &cheese, &pickleSlice, &onion});
    Struct combo1(Atom("combo1"), {&bigMac, &coke, &fries});

    Iterator<Term *> *bfsIt = combo1.createBFSIterator();
    bfsIt->first();

    ASSERT_EQ(
        "bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, "
        "pickleSlice2], [onion1, onion2])",
        bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("coke", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[fries1, fries2]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("bun", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("beefPatty", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("shreddedLettuce", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("sauce", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("cheese", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[pickleSlice1, pickleSlice2]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[onion1, onion2]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("fries1", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("fries2", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("pickleSlice1", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("pickleSlice2", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("onion1", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("onion2", bfsIt->currentItem()->symbol());

    bfsIt->next();
    ASSERT_TRUE(bfsIt->isDone());
}

TEST(iterator, combo1_DFS) {
    Atom bun("bun");
    Atom beefPatty("beefPatty");
    Atom shreddedLettuce("shreddedLettuce");
    Atom sauce("sauce");
    Atom cheese("cheese");
    Atom pickleSlice1("pickleSlice1");
    Atom pickleSlice2("pickleSlice2");
    Atom onion1("onion1");
    Atom onion2("onion2");
    Atom coke("coke");
    Atom fries1("fries1");
    Atom fries2("fries2");
    List pickleSlice({&pickleSlice1, &pickleSlice2});
    List onion({&onion1, &onion2});
    List fries({&fries1, &fries2});
    Struct bigMac(Atom("bigMac"), {&bun, &beefPatty, &shreddedLettuce, &sauce,
                                   &cheese, &pickleSlice, &onion});
    Struct combo1(Atom("combo1"), {&bigMac, &coke, &fries});

    Iterator<Term *> *dfsIt = combo1.createDFSIterator();
    dfsIt->first();

    ASSERT_EQ(
        "bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, "
        "pickleSlice2], [onion1, onion2])",
        dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("bun", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("beefPatty", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("shreddedLettuce", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("sauce", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("cheese", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("[pickleSlice1, pickleSlice2]", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("pickleSlice1", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("pickleSlice2", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("[onion1, onion2]", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("onion1", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("onion2", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("coke", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("[fries1, fries2]", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("fries1", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("fries2", dfsIt->currentItem()->symbol());

    dfsIt->next();
    ASSERT_TRUE(dfsIt->isDone());
}

TEST(iterator, manyBendedKrait_BFS) {
    List band1;
    List band2;
    List band3;
    List band4;
    Struct manyBendedKrait(Atom("manyBendedKrait"),
                           {&band1, &band2, &band3, &band4});

    Iterator<Term *> *bfsIt = manyBendedKrait.createBFSIterator();
    bfsIt->first();

    ASSERT_EQ("[]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[]", bfsIt->currentItem()->symbol());

    bfsIt->next();
    ASSERT_TRUE(bfsIt->isDone());
}

TEST(iterator, manyBendedKrait_DFS) {
    List band1;
    List band2;
    List band3;
    List band4;
    Struct manyBendedKrait(Atom("manyBendedKrait"),
                           {&band1, &band2, &band3, &band4});

    Iterator<Term *> *dfsIt = manyBendedKrait.createDFSIterator();
    dfsIt->first();

    ASSERT_EQ("[]", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("[]", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("[]", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("[]", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_TRUE(dfsIt->isDone());
}

TEST(iterator, shadowCloneJutsu_BFS) {
    Atom naruto("naruto");
    List forest1({&naruto});
    List forest2_1({&naruto});
    List forest2_2({&naruto});
    List forest2({&forest2_1, &forest2_2});
    List forest3_1({&naruto});
    List forest3_2({&naruto});
    List forest3_3({&naruto});
    List forest3({&forest3_1, &forest3_2, &forest3_3});
    List forest4({&naruto, &forest3, &forest2, &forest1});

    Iterator<Term *> *bfsIt = forest4.createBFSIterator();
    cout << forest4.symbol() << endl;
    bfsIt->first();

    ASSERT_EQ("naruto", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[[naruto], [naruto], [naruto]]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[[naruto], [naruto]]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[naruto]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[naruto]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[naruto]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[naruto]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[naruto]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[naruto]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("naruto", bfsIt->currentItem()->symbol());
    bfsIt->next();

    ASSERT_EQ("naruto", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("naruto", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("naruto", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("naruto", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("naruto", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_TRUE(bfsIt->isDone());
}

TEST(iterator, shadowCloneJutsu_DFS) {
    Atom naruto("naruto");
    List forest1({&naruto});
    List forest2_1({&naruto});
    List forest2_2({&naruto});
    List forest2({&forest2_1, &forest2_2});
    List forest3_1({&naruto});
    List forest3_2({&naruto});
    List forest3_3({&naruto});
    List forest3({&forest3_1, &forest3_2, &forest3_3});
    List forest4({&naruto, &forest3, &forest2, &forest1});
    cout << forest4.symbol() << endl;
    Iterator<Term *> *dfsIt = forest4.createDFSIterator();
    dfsIt->first();

    ASSERT_EQ("naruto", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("[[naruto], [naruto], [naruto]]", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("[naruto]", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("naruto", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("[naruto]", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("naruto", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("[naruto]", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("naruto", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("[[naruto], [naruto]]", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("[naruto]", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("naruto", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("[naruto]", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("naruto", dfsIt->currentItem()->symbol());
    dfsIt->next();

    ASSERT_EQ("[naruto]", dfsIt->currentItem()->symbol());
    dfsIt->next();
    ASSERT_EQ("naruto", dfsIt->currentItem()->symbol());
    dfsIt->next();

    ASSERT_TRUE(dfsIt->isDone());
}

TEST(iterator, unbalanceTree_BFS) {
    Number num1(1);
    Struct s1(Atom("s"), {&num1});
    List list1({&s1});
    Struct s2(Atom("s"), {&list1});
    List list2({&s2});
    Struct s3(Atom("s"), {&list2});
    List list3({&s3});
    Struct s4(Atom("s"), {&list3});
    Number num(3);
    List list4({&s4, &num});

    Iterator<Term *> *bfsIt = list4.createBFSIterator();
    bfsIt->first();
    ASSERT_EQ("s([s([s([s(1)])])])", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("3", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[s([s([s(1)])])]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("s([s([s(1)])])", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[s([s(1)])]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("s([s(1)])", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[s(1)]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("s(1)", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("1", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_TRUE(bfsIt->isDone());
}

TEST(iterator, unbalanceTree_DFS) {
    Number num1(1);
    Struct s1(Atom("s"), {&num1});
    List list1({&s1});
    Struct s2(Atom("s"), {&list1});
    List list2({&s2});
    Struct s3(Atom("s"), {&list2});
    List list3({&s3});
    Struct s4(Atom("s"), {&list3});
    Number num3(3);
    List list4({&s4, &num3});

    Iterator<Term *> *bfsIt = list4.createDFSIterator();
    cout << list4.symbol() << endl;
    bfsIt->first();

    ASSERT_EQ("s([s([s([s(1)])])])", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[s([s([s(1)])])]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("s([s([s(1)])])", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[s([s(1)])]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("s([s(1)])", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("[s(1)]", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("s(1)", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("1", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_EQ("3", bfsIt->currentItem()->symbol());
    bfsIt->next();
    ASSERT_TRUE(bfsIt->isDone());
}
#endif