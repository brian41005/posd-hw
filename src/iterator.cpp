#include "../include/iterator.h"
#include "../include/list.h"
StructIterator::StructIterator(Struct* structure) : _container(structure),_index(0) {}

void StructIterator::first() { _index = 0; }

void StructIterator::next() { _index++; }

bool StructIterator::isDone() const{ return _index == _container->arity(); }

Term* StructIterator::currentItem() const{ return _container->args(_index); }



ListIterator::ListIterator(List* list) : _origin(list) {}

void ListIterator::first() { _current = _origin; }

void ListIterator::next() { _current = _current->tail(); }

bool ListIterator::isDone() const { return !_current->arity(); }

Term* ListIterator::currentItem() const{ return _current->head(); }
