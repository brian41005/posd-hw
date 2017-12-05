#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "../include/iterator.h"
#include "../include/list.h"
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

TEST(Iterator, empty_list_bfs) {
    // [[], []]
    List l1;
    List l2;
    List l3(&l1, &l2);

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


// TEST(Iterator, empty_struct_bfs) {
//     // s(s(), s(2))
//     Struct s1(Atom("s"), {});
//     Number two(2);
//     Struct s2(Atom("s"), { &two });
//     Struct s3(Atom("s"), { &s1, &s2 });
//     Iterator<Term*> *it = s3.createBFSIterator();

//     it->first();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("s()", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("s(2)", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("2", it->currentItem()->symbol());
//     it->next();

//     ASSERT_TRUE(it->isDone());
//     delete it;


// }

// TEST(Iterator, test) {
//     Number one(1);
//     Iterator<Term*> *it = one.createIterator();
//     cout << it << endl;
//     ASSERT_EQ("1", it->currentItem()->symbol());
//     ASSERT_TRUE(it->isDone());
//     delete it;
// }

// TEST (Iterator, number_nullIterator) {
//     Number one(1);
//     Iterator<Term*> *it = one.createIterator();
//     cout << it << endl;
//     ASSERT_EQ("1", it->currentItem()->symbol());
//     ASSERT_TRUE(it->isDone());
//     delete it;
// }

// TEST (Iterator, variable_nullIterator) {
//     Variable X("X");
//     Iterator<Term*> *it = X.createIterator();
//     cout << it << endl;
//     ASSERT_EQ("X", it->currentItem()->symbol());
//     ASSERT_TRUE(it->isDone());
//     delete it; 
// }

// TEST (Iterator, atom_nullIterator) {
//     Atom tom("tom");
//     Iterator<Term*> *it = tom.createIterator();
//     cout << it << endl;
//     ASSERT_EQ("tom", it->currentItem()->symbol());
//     ASSERT_TRUE(it->isDone());
//     delete it;
// }

// TEST(Iterator, struct_iterator) {
//     // s(X, tom, 1.22)
//     Variable X("X");
//     Atom tom("tom");
//     Number n(1.22);
//     Struct s(Atom("s"), { &X, &tom, &n });
//     Iterator<Term*> *it = s.createBFSIterator();
//     cout << it << endl;
//     it->first();
//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("X", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("tom", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("1.22", it->currentItem()->symbol());
//     it->next();

//     ASSERT_TRUE(it->isDone());
//     delete it;
// }

// TEST(Iterator, complex_struct_iterator) {
//     // triangle(point(1, 2), point(2, 3), point(4, 5));
//     Number one(11);
//     Number two(22);
//     Number three(33);
//     Number four(44);
//     Number five(55);

//     Struct p1(Atom("point"), { &one, &two });
//     Struct p2(Atom("point"), { &two, &three });
//     Struct p3(Atom("point"), { &four, &five });
//     Struct t(Atom("triangle"), { &p1, &p2, &p3 });
//     ASSERT_EQ("triangle(point(11, 22), point(22, 33), point(44, 55))", t.symbol());
//     Iterator<Term*> *it = t.createBFSIterator();
//     cout << it << endl;
//     it->first(); // initialize

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("point(11, 22)", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("point(22, 33)", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("point(44, 55)", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("11", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("22", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("22", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("33", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("44", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("55", it->currentItem()->symbol());
//     it->next();

//     ASSERT_TRUE(it->isDone());

// }   

// TEST(BFSIterator, struct_bfs) {
//     // s(s(X), 2, 3)
//     Variable X("X");
//     Number two(2);
//     Number three(3);
    
//     Struct s(Atom("s"), { &X });
//     Struct s1(Atom("s"), { &s, &two, &three });
//     Iterator<Term*> *it = s1.createBFSIterator();
//     it->first(); // initialize


//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("s(X)", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("2", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("3", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("X", it->currentItem()->symbol());
//     it->next();

//     ASSERT_TRUE(it->isDone());

//     delete it;
// }

// TEST(DFSIterator, struct_dfs) {
//     Variable X("X");
//     Number two(2);
//     Number three(3);
//     Struct s(Atom("s"), { &X });
//     Struct s1(Atom("s"), { &s, &two, &three });
//     Iterator<Term*> *it = s1.createDFSIterator();
//     cout << it << endl;
//     it->first(); // initialize

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("s(X)", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("X", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("2", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("3", it->currentItem()->symbol());
//     it->next();
    
//     ASSERT_TRUE(it->isDone());
//     delete it;
// }

// TEST(BFSIterator, simple_list_iterator) {
//     // [496, X, terence_tao]
//     Number n(496);
//     Variable X("X");
//     Atom terence_tao("terence_tao");
//     List l({ &n, &X, &terence_tao });
//     Iterator<Term*> *it = l.createDFSIterator();
//     cout << it << endl;
    
//     it->first(); // initialize

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("496", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("X", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("terence_tao", it->currentItem()->symbol());
//     it->next();

//     ASSERT_TRUE(it->isDone());
//     delete it;
// }

// TEST(BFSIterator, complex_list_bfsiterator) {
//     // [[496, X, terence_tao], tom, jerry]
//     Number n(496);
//     Variable X("X");
//     Atom terence_tao("terence_tao");
//     List l({ &n, &X, &terence_tao });
//     Atom tom("tom");
//     Atom jerry("jerry");
//     List l2({ &l, &tom, &jerry });
    
//     Iterator<Term*> *it = l2.createBFSIterator();
//         cout << it << endl;

//     it->first(); // initialize

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("[496, X, terence_tao]", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("tom", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("jerry", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("496", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("X", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("terence_tao", it->currentItem()->symbol());
//     it->next();

//     ASSERT_TRUE(it->isDone());
//     delete it;
// }

// TEST(DFSIterator, complex_list_dfsiterator) {
//     // [[496, X, terence_tao], tom, jerry]
//     Number n(496);
//     Variable X("X");
//     Atom terence_tao("terence_tao");
//     List l({ &n, &X, &terence_tao });
//     Atom tom("tom");
//     Atom jerry("jerry");
//     List l2({ &l, &tom, &jerry });
    
//     Iterator<Term*> *it = l2.createDFSIterator();
//     cout << it << endl;
    
//     it->first(); // initialize

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("[496, X, terence_tao]", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("496", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("X", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("terence_tao", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("tom", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("jerry", it->currentItem()->symbol());
//     it->next();

//     ASSERT_TRUE(it->isDone());
//     delete it;
// }

// TEST(BFSIterator, complex_list_bfsiterator2) {
//     // [[[496, X, terence_tao], tom, jerry], s(X, Y, [1, 2]), tom]
//     Number n(496);
//     Variable X("X");
//     Atom terence_tao("terence_tao");
//     List l({ &n, &X, &terence_tao });

//     Atom tom("tom");
//     Variable Y("Y");
//     Number one(1);
//     Number two(2);
//     List l3({ &one, &two });
//     Struct s(Atom("s"), { &X, &Y, &l3 });
//     List l4({ &l, &s, &tom });
//     ASSERT_EQ("[[496, X, terence_tao], s(X, Y, [1, 2]), tom]", l4.symbol());

//     Iterator<Term*> *it = l4.createBFSIterator();
//     cout << it << endl;
//     it->first(); // initialize
    
//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("[496, X, terence_tao]", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("s(X, Y, [1, 2])", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("tom", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("496", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("X", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("terence_tao", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("X", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("Y", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("[1, 2]", it->currentItem()->symbol());
//     it->next();

//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("1", it->currentItem()->symbol());
//     it->next();    ASSERT_FALSE(it->isDone());
    
//     ASSERT_EQ("2", it->currentItem()->symbol());
//     it->next();
//     ASSERT_TRUE(it->isDone());
//     delete it;
// }

// TEST(DFSIterator, complext_list_dfsiterator2) {
//     // [[[496, X, terence_tao], tom, jerry], s(X, Y, [1, 2]), tom]
//     Number n(496);
//     Variable X("X");
//     Atom terence_tao("terence_tao");
//     List l({ &n, &X, &terence_tao });

//     Atom tom("tom");
//     Variable Y("Y");
//     Number one(1);
//     Number two(2);
//     List l3({ &one, &two });
//     Struct s(Atom("s"), { &X, &Y, &l3 });
//     List l4({ &l, &s, &tom });
//     ASSERT_EQ("[[496, X, terence_tao], s(X, Y, [1, 2]), tom]", l4.symbol());

//     Iterator<Term*> *it = l4.createDFSIterator();
//     cout << it << endl;
//     it->first(); // initialize
//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("[496, X, terence_tao]", it->currentItem()->symbol());
    
//     it->next();
//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("496", it->currentItem()->symbol());
    
//     it->next();
//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("X", it->currentItem()->symbol());
    
//     it->next();
//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("terence_tao", it->currentItem()->symbol());
    
//     it->next();
//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("s(X, Y, [1, 2])", it->currentItem()->symbol());
    
//     it->next();
//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("X", it->currentItem()->symbol());
    
//     it->next();
//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("Y", it->currentItem()->symbol());
    
//     it->next();
//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("[1, 2]", it->currentItem()->symbol());
    
//     it->next();
//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("1", it->currentItem()->symbol());
    
//     it->next();
//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("2", it->currentItem()->symbol());
    
//     it->next(); 
//     ASSERT_FALSE(it->isDone());
//     ASSERT_EQ("tom", it->currentItem()->symbol());
    
//     it->next();
//     ASSERT_TRUE(it->isDone());
//     delete it;
// }

#endif