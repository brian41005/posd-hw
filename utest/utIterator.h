#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "../include/iterator.h"
#include "../include/list.h"
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), {&X, &two});
    Struct s(Atom("s"), {&one, &t, &Y});
    Iterator<Term*>* itStruct = s.createIterator();
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), {&X, &two});
    Struct s(Atom("s"), {&one, &t, &Y});
    Iterator<Term*>* it = s.createIterator();
    it->first();
    it->next();
    Struct* s2 = dynamic_cast<Struct*>(it->currentItem());
    Iterator<Term*>* it2 = s2->createIterator();

    it2->first();
    ASSERT_EQ("X", it2->currentItem()->symbol());
    ASSERT_FALSE(it2->isDone());
    it2->next();
    ASSERT_EQ("2", it2->currentItem()->symbol());
    ASSERT_FALSE(it2->isDone());
    it2->next();
    ASSERT_TRUE(it2->isDone());
}

TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), {&X, &two});
    List l({&one, &t, &Y});
    Iterator<Term*>* itList = l.createIterator();

    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator) {
    Number one(1);
    Iterator<Term*>* nullIterator = one.createIterator();
    nullIterator->first();
    ASSERT_TRUE(nullIterator->isDone());
}

TEST(iterator, structDFSIteratorData1) {
    Struct s(Atom("s"),
             {new Struct(Atom("a"), {new Atom("b"), new Atom("c")}),
              new Struct(Atom("d"), {new Atom("e"), new Atom("f")}),
              new Struct(Atom("g"), {new Atom("h"), new Atom("i")})});

    Iterator<Term*>* it = s.createDFSIterator();
    it->first();
    EXPECT_EQ("a(b, c)", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("b", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("c", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("d(e, f)", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("e", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("f", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("g(h, i)", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("h", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("i", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_TRUE(it->isDone());
}

TEST(iterator, structDFSIteratorData2) {
    Struct s(Atom("s"), {new Number(1),
                         new Struct(Atom("d"), {new Atom("e"), new Atom("f")}),
                         new Struct(Atom("g"), {new Variable("X")})});

    Iterator<Term*>* it = s.createDFSIterator();
    it->first();
    EXPECT_EQ("1", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("d(e, f)", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("e", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("f", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("g(X)", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("X", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_TRUE(it->isDone());
}

TEST(iterator, listDFSIteratorData1) {
    List l({new List({new Atom("b"), new Atom("c")}),
            new List({new Atom("e"), new Atom("f")}),
            new List({new Atom("h"), new Atom("i")})});

    Iterator<Term*>* it = l.createDFSIterator();
    it->first();
    EXPECT_EQ("[b, c]", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("b", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("c", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("[e, f]", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("e", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("f", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("[h, i]", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("h", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("i", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_TRUE(it->isDone());
}

TEST(iterator, listDFSIteratorData2) {
    List l({new Number(1), new List({new Atom("e"), new Atom("f")}),
            new List({new Variable("X")})});

    Iterator<Term*>* it = l.createDFSIterator();
    it->first();
    EXPECT_EQ("1", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("[e, f]", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("e", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("f", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("[X]", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("X", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_TRUE(it->isDone());
}

TEST(iterator, structBFSIteratorData1) {
    Struct s(Atom("s"),
             {new Struct(Atom("a"), {new Atom("b"), new Atom("c")}),
              new Struct(Atom("d"), {new Atom("e"), new Atom("f")}),
              new Struct(Atom("g"), {new Atom("h"), new Atom("i")})});

    Iterator<Term*>* it = s.createBFSIterator();
    it->first();
    EXPECT_EQ("a(b, c)", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("d(e, f)", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("g(h, i)", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("b", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("c", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("e", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("f", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("h", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("i", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_TRUE(it->isDone());
}

TEST(iterator, structBFSIteratorData2) {
    Struct s(Atom("s"), {new Number(1),
                         new Struct(Atom("d"), {new Atom("e"), new Atom("f")}),
                         new Struct(Atom("g"), {new Variable("X")})});

    Iterator<Term*>* it = s.createBFSIterator();
    it->first();
    EXPECT_EQ("1", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("d(e, f)", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("g(X)", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("e", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("f", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("X", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_TRUE(it->isDone());
}

TEST(iterator, listBFSIteratorData1) {
    List l({new List({new Atom("b"), new Atom("c")}),
            new List({new Atom("e"), new Atom("f")}),
            new List({new Atom("h"), new Atom("i")})});

    Iterator<Term*>* it = l.createBFSIterator();
    it->first();
    EXPECT_EQ("[b, c]", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("[e, f]", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("[h, i]", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("b", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("c", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("e", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("f", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("h", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("i", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_TRUE(it->isDone());
}

TEST(iterator, listBFSIteratorData2) {
    List l({new Number(1), new List({new Atom("e"), new Atom("f")}),
            new List({new Variable("X")})});

    Iterator<Term*>* it = l.createBFSIterator();
    it->first();
    EXPECT_EQ("1", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("[e, f]", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("[X]", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("e", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("f", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_EQ("X", it->currentItem()->symbol());
    EXPECT_FALSE(it->isDone());

    it->next();
    EXPECT_TRUE(it->isDone());
}
#endif