#include "include/Sort.h"
#include <algorithm> 

using namespace std;



void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList){
    shapeList->sort([](const Shape *s1, const Shape *s2){ return s1->perimeter() < s2->perimeter();});
}
void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList){
    shapeList->sort([](const Shape *s1, const Shape *s2){ return s1->perimeter() > s2->perimeter();});
}
void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList){
    shapeList->sort([](const Shape *s1, const Shape *s2){ return s1->area() < s2->area();});
}
void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList){
    shapeList->sort([](const Shape *s1, const Shape *s2){ return s1->area() > s2->area();});
}
void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList){
    shapeList->sort([](const Shape *s1, const Shape *s2){ return (s1->area()/s1->perimeter()) < (s2->area()/s2->perimeter());});
}