#include "include/Sort.h"
#include <algorithm>

using namespace std;

void Sort::sortByIncreasingPerimeter(list<Shape *> *shapeList)
{
    shapeList->sort([](const Shape *shape1, const Shape *shape2) { return shape1->perimeter() < shape2->perimeter(); });
}
void Sort::sortByDecreasingPerimeter(list<Shape *> *shapeList)
{
    shapeList->sort([](const Shape *shape1, const Shape *shape2) { return shape1->perimeter() > shape2->perimeter(); });
}
void Sort::sortByIncreasingArea(list<Shape *> *shapeList)
{
    shapeList->sort([](const Shape *shape1, const Shape *shape2) { return shape1->area() < shape2->area(); });
}
void Sort::sortByDecreasingArea(list<Shape *> *shapeList)
{
    shapeList->sort([](const Shape *shape1, const Shape *shape2) { return shape1->area() > shape2->area(); });
}
void Sort::sortByIncreasingCompactness(list<Shape *> *shapeList)
{
    shapeList->sort([](const Shape *shape1, const Shape *shape2) { return (shape1->area() / shape1->perimeter()) < (shape2->area() / shape2->perimeter()); });
}