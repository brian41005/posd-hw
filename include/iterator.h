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
  public:
    void first()
    {
    }
 
    void next()
    {
    }
 
    bool isDone() const
    {
        return true;
    }
 
    T currentItem() const
    {
        return nullptr;
    }
};
 
class StructIterator : public Iterator<Term *>
{
  public:
    StructIterator(Struct *container);
 
    void first()
    {
        _index = 0;
    }
 
    void next()
    {
        if (!isDone())
            _index++;
    }
 
    bool isDone() const;
    Term *currentItem() const;
 
  private:
    Struct *_container;
    int _index;
};
 
class ListIterator : public Iterator<Term *>
{
  public:
    ListIterator(List *container);
 
    void first()
    {
        _index = 0;
    }
 
    void next();
    bool isDone() const;
    Term *currentItem() const;
 
  private:
    List *_container;
    int _index;
};
 
template <class T>
class BFSIterator : public Iterator<T>
{
  public:
    BFSIterator(Iterator<T> *origin) : _origin(origin), _activeIt(origin)
    {
    }
 
    void first()
    {
        _activeIt = _origin;
        _activeIt->first();
    }
 
    void next()
    {
        // check if current item is compound item or not //
        Iterator<T> *temp = _activeIt->currentItem()->createIterator();
        if (!temp->isDone())
            _itQueue.push(temp);
 
        _activeIt->next();
        if (_activeIt->isDone() && !_itQueue.empty())
        {
            _activeIt = _itQueue.front();
            _itQueue.pop();
        }
    }
 
    bool isDone() const
    {
        return (_itQueue.empty() && _activeIt->isDone());
    }
 
    T currentItem() const
    {
        //std::cout << _activeIt->currentItem() << std::endl;
        return _activeIt->currentItem();
    }
 
  private:
    Iterator<T> *_origin;
    Iterator<T> *_activeIt;
    queue<Iterator<T> *> _itQueue;
};
 
template <class T>
class DFSIterator : public Iterator<T>
{
  public:
    DFSIterator(Iterator<T> *origin) : _origin(origin), _activeIt(origin)
    {
    }
 
    void first()
    {
        _activeIt = _origin;
        _activeIt->first();
    }
 
    void next()
    {
        Iterator<T> *temp = _activeIt->currentItem()->createIterator();
        if (!temp->isDone())
        {
            _itStack.push(_activeIt);
            _activeIt = temp;
        }
        else
        {
            _activeIt->next();
            while (_activeIt->isDone() && !_itStack.empty())
            {
                _activeIt = _itStack.top();
                _itStack.pop();
                _activeIt->next();
            }
        }
    }
 
    bool isDone() const
    {
        return (_itStack.empty() && _activeIt->isDone());
    }
 
    T currentItem() const
    {
        return _activeIt->currentItem();
    }
 
  private:
    Iterator<T> *_origin;
    Iterator<T> *_activeIt;
    stack<Iterator<T> *> _itStack;
};
 
#endif