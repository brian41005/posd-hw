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
    shapes->push_back(new Triangle({0.0, 0.0}, {0.0, 21.0}, {20.0, 0.0}, "5"));
    shapes->push_back(new Triangle({0.0, 0.0}, {0.0, 20.0}, {20.0, 0.0}, "4"));
    shapes->push_back(new Circle(0, 0, 10, "3"));
    shapes->push_back(new Circle(0, 0, 9, "2"));
    shapes->push_back(new Rectangle(0, 0, 8, 8, "1"));
    shapes->push_back(new Rectangle(0, 0, 7, 7, "0"));
    
    Sort::sortByIncreasingPerimeter(shapes);
    list<Shape*>::iterator it = shapes->begin(); 
    for(int i=0; i<6; i++){
        ASSERT_EQ((*it)->name, to_string(i));
        it++;
    }
    
}

TEST (Sort, sortByDecreasingPerimeter) {
    list<Shape *> *shapes = new list<Shape*>();
    
    shapes->push_back(new Triangle({0.0, 0.0}, {0.0, 21.0}, {20.0, 0.0}, "0"));
    shapes->push_back(new Triangle({0.0, 0.0}, {0.0, 20.0}, {20.0, 0.0}, "1"));
    shapes->push_back(new Circle(0, 0, 10, "2"));
    shapes->push_back(new Circle(0, 0, 9, "3"));
    shapes->push_back(new Rectangle(0, 0, 8, 8, "4"));
    shapes->push_back(new Rectangle(0, 0, 7, 7, "5"));
    
    Sort::sortByDecreasingPerimeter(shapes);
    list<Shape*>::iterator it = shapes->begin(); 
    for(int i=0; i<6; i++){
        ASSERT_EQ((*it)->name, to_string(i));
        it++;
    }
}

TEST (Sort, sortByIncreasingArea) {
    list<Shape *> *shapes = new list<Shape*>();

    shapes->push_back(new Triangle({0.0, 0.0}, {0.0, 27.0}, {27.0, 0.0}, "5"));
    shapes->push_back(new Triangle({0.0, 0.0}, {0.0, 26.0}, {26.0, 0.0}, "4"));
    shapes->push_back(new Circle(0, 0, 10, "3"));
    shapes->push_back(new Circle(0, 0, 9, "2"));
    shapes->push_back(new Rectangle(0, 0, 8, 8, "1"));
    shapes->push_back(new Rectangle(0, 0, 7, 7, "0"));
    
    Sort::sortByIncreasingArea(shapes);
    list<Shape*>::iterator it = shapes->begin(); 
    for(int i=0; i<6; i++){
        ASSERT_EQ((*it)->name, to_string(i));
        it++;
    }
}

TEST (Sort, sortByDecreasingArea) {
    list<Shape *> *shapes = new list<Shape*>();
    shapes->push_back(new Triangle({0.0, 0.0}, {0.0, 27.0}, {27.0, 0.0}, "0"));
    shapes->push_back(new Triangle({0.0, 0.0}, {0.0, 26.0}, {26.0, 0.0}, "1"));
    shapes->push_back(new Circle(0, 0, 10, "2"));
    shapes->push_back(new Circle(0, 0, 9, "3"));
    shapes->push_back(new Rectangle(0, 0, 8, 8, "4"));
    shapes->push_back(new Rectangle(0, 0, 7, 7, "5"));
    Sort::sortByDecreasingArea(shapes);
    list<Shape*>::iterator it = shapes->begin(); 
    for(int i=0; i<6; i++){
        ASSERT_EQ((*it)->name, to_string(i));
        it++;
    }
}

TEST (Sort, sortByIncreasingCompactness) {
    list<Shape *> *shapes = new list<Shape*>();
    
    shapes->push_back(new Triangle({0.0, 0.0}, {0.0, 27.0}, {27.0, 0.0}, "5"));
    shapes->push_back(new Triangle({0.0, 0.0}, {0.0, 26.0}, {26.0, 0.0}, "4"));
    shapes->push_back(new Circle(0, 0, 10, "3"));
    shapes->push_back(new Circle(0, 0, 9, "2"));
    shapes->push_back(new Rectangle(0, 0, 8, 8, "1"));
    shapes->push_back(new Rectangle(0, 0, 7, 7, "0"));
    
    Sort::sortByIncreasingCompactness(shapes);
    list<Shape*>::iterator it = shapes->begin(); 
    for(int i=0; i<6; i++){
        ASSERT_EQ((*it)->name, to_string(i));
        it++;
    }

}

#endif
