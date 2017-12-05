#include "../include/iterator.h"
#include "../include/list.h"
StructIterator::StructIterator(Struct *container):_container(container),_index(0){

}
bool StructIterator::isDone() const{
    return (_index >= _container->arity());
}
Term *StructIterator::currentItem() const{
    if (isDone())
        return nullptr;
    return _container->args(_index);
}

ListIterator::ListIterator(List *container):_container(container),_index(0){

}
void ListIterator::next(){
    _index++;
}
bool ListIterator::isDone() const{
    return (_index >= _container->arity());
}
Term *ListIterator::currentItem() const{
    if (isDone())
        return nullptr;
    return _container->args(_index);
}