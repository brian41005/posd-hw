#ifndef EXP_H
#define EXP_H

#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
#include <list>
#include <string> 
#include <iostream>
using namespace std;

TEST (Sort, sortByIncreasingPerimeter) {

    list<Shape *> *shapes = new list<Shape*>();
    shapes->push_back(new Circle(0, 0, 10, "4"));
    shapes->push_back(new Circle(0, 0, 9, "3"));
    shapes->push_back(new Rectangle(0, 0, 8, 8, "2"));
    shapes->push_back(new Rectangle(0, 0, 7, 7, "1"));
    //vertex v1,v2, v2 = {0, 0}, {0, 1}, {}
    //shapes->push_back(new Triangle(0, 0, 7,7, "4"));
    Sort::sortByIncreasingPerimeter(shapes);
    list<Shape*>::iterator it = shapes->begin(); 
    for(int i=1;i<=4;i++){
        ASSERT_EQ((*it)->name, to_string(i));
        it++;
    }
    
}

TEST (Sort, sortByDecreasingPerimeter) {
    list<Shape *> *shapes = new list<Shape*>();
    shapes->push_back(new Rectangle(0, 0, 7, 7, "4"));
    shapes->push_back(new Rectangle(0, 0, 8, 8, "3"));
    shapes->push_back(new Circle(0, 0, 9, "2"));
    shapes->push_back(new Circle(0, 0, 10, "1"));
    //vertex v1,v2, v2 = {0, 0}, {0, 1}, {}
    //shapes->push_back(new Triangle(0, 0, 7,7, "4"));
    Sort::sortByDecreasingPerimeter(shapes);
    list<Shape*>::iterator it = shapes->begin(); 
    for(int i=1;i<=4;i++){
        ASSERT_EQ((*it)->name, to_string(i));
        it++;
    }
}

TEST (Sort, sortByIncreasingArea) {
    list<Shape *> *shapes = new list<Shape*>();
    shapes->push_back(new Circle(0, 0, 10, "4"));
    shapes->push_back(new Circle(0, 0, 9, "3"));
    shapes->push_back(new Rectangle(0, 0, 8, 8, "2"));
    shapes->push_back(new Rectangle(0, 0, 7, 7, "1"));
    //vertex v1,v2, v2 = {0, 0}, {0, 1}, {}
    //shapes->push_back(new Triangle(0, 0, 7,7, "4"));
    Sort::sortByIncreasingArea(shapes);
    list<Shape*>::iterator it = shapes->begin(); 
    for(int i=1;i<=4;i++){
        ASSERT_EQ((*it)->name, to_string(i));
        it++;
    }
}

TEST (Sort, sortByDecreasingArea) {
    list<Shape *> *shapes = new list<Shape*>();
    shapes->push_back(new Rectangle(0, 0, 7, 7, "4"));
    shapes->push_back(new Rectangle(0, 0, 8, 8, "3"));
    shapes->push_back(new Circle(0, 0, 9, "2"));
    shapes->push_back(new Circle(0, 0, 10, "1"));
    //vertex v1,v2, v2 = {0, 0}, {0, 1}, {}
    //shapes->push_back(new Triangle(0, 0, 7,7, "4"));
    Sort::sortByDecreasingArea(shapes);
    list<Shape*>::iterator it = shapes->begin(); 
    for(int i=1;i<=4;i++){
        ASSERT_EQ((*it)->name, to_string(i));
        it++;
    }
}

TEST (Sort, sortByIncreasingCompactness) {

}

#endif
