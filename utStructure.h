#ifndef UTSTRUCTURE_H
#define UTSTRUCTURE_H

#include "include/atom.h"
#include "include/number.h"
#include "include/variable.h"
#include "include/structure.h"
#include <vector>

//triangle(point(1,1), point(0,0), point(0,1)).
TEST(Structure, ctor){
    Atom a1("point");
    Number n1(1), n2(1);
    vector<Term*> v1 = {&a1, &n1, &n2};
    Structure s1(v1);
    ASSERT_EQ("point11", s1.symbol());
    //ASSERT_TRUE(s1.match(s1));
}

#endif