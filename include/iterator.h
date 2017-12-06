#ifndef ITERATOR_H
#define ITERATOR_H
#include <queue>
#include <stack>
using std::queue;
using std::stack;
#include <iostream>
 
class Struct;
class List;
class Term;
template <class T>
class Iterator
{
  public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
    virtual T currentItem() const = 0;
};
 
template <class T>
class NullIterator : public Iterator<T>
{
  private:
    T _instance;
  public:
    NullIterator(T instance) : _instance(instance) {}
    void first(){}
    void next(){}
    bool isDone() const{return true;}
    T currentItem() const{return _instance;}
};
 
class StructIterator : public Iterator<Term *>
{
  private:
    Struct *_container;
    int _index;
  public:
    StructIterator(Struct *container);
    void first();
    void next();
    bool isDone() const;
    Term *currentItem() const;
 
};
 
class ListIterator : public Iterator<Term *>
{
  private:
     List* _origin, *_current;
  public:
    ListIterator(List *container);
 
    void first();
    void next();
    bool isDone() const;
    Term *currentItem() const;
 
};
 
template <class T>
class BFSIterator : public Iterator<T>
{
  public:
    BFSIterator(Iterator<T> *origin) : _it(origin){}
 
    void first()
    {
        _itQueue = std::queue<Iterator<T>*>();
        _it->first();
        _itQueue.push(_it);
    }
 
    void next()
    {
        Iterator<T>* it = _itQueue.front();
        Iterator<T>* itemIt = it->currentItem()->createIterator();
        itemIt->first();
        it->next();
        if (!itemIt->isDone()) 
            _itQueue.push(itemIt);
        while (!_itQueue.empty() && _itQueue.front()->isDone()) _itQueue.pop();
    }
 
    bool isDone() const{return _itQueue.empty();}
 
    T currentItem() const{return _itQueue.front()->currentItem();}
 
    private:
        queue<Iterator<T>*> _itQueue;
        Iterator<T>* _it;
};
 





template <class T>
class DFSIterator : public Iterator<T>
{
  public:
    DFSIterator(Iterator<T> *origin) : _it(origin){}
 
    void first()
    {
        _itStack = std::stack<Iterator<T>*>();
        _it->first();
        _itStack.push(_it);
    }
 
    void next()
    {
        Iterator<T>* it = _itStack.top();
        Iterator<T>* itemIt = it->currentItem()->createIterator();
        itemIt->first();
        it->next();
        if (!itemIt->isDone()) _itStack.push(itemIt);
        while (!_itStack.empty() && _itStack.top()->isDone()) _itStack.pop();
    }
 
    bool isDone() const{return _itStack.empty();}
    T currentItem() const{return _itStack.top()->currentItem();}
 
  private:
    Iterator<T>* _it;
    stack<Iterator<T> *> _itStack;
};
 
#endif