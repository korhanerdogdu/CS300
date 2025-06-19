
#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
#include <vector>

template <class Comparable>
class ListItr;
template <class Comparable>
class List;

template <class Object>
class ListNode
{
    ListNode(const Object &theElement = Object(), ListNode *n = NULL)
        : element(theElement), next(n) {}

    Object element;
    std::vector<std::string> info;
    ListNode *next;

    friend class List<Object>;
    friend class ListItr<Object>;
};

template <class Object>
class ListItr
{
public:
    ListItr() : current(NULL) {}
    bool isPastEnd() const;
    void advance();
    const Object &retrieve() const;
    const std::string &retrieveInfo() const;
    const int infosize() const;
    void pushInfo(std::string s) const;
    const std::string &infAt(int a) const;
    const std::vector<std::string> &AllInfo() const;

private:
    ListNode<Object> *current;
    ListItr(ListNode<Object> *theNode) : current(theNode) {}
    friend class List<Object>;
};

template <class Object>
class List
{
public:
    List();
    List(const List &rhs);
    ~List();
    bool isEmpty() const;
    void makeEmpty();
    ListItr<Object> zeroth() const;
    ListItr<Object> first() const;
    void insert(const Object &x, const ListItr<Object> &p);
    void changeInfo(const ListItr<Object> &p, const std::string &y, const bool &);
    ListItr<Object> find(const Object &x) const;
    ListItr<Object> findPrevious(const Object &x) const;
    void remove(const Object &x);
    void printer();
    const List<Object> &operator=(const List<Object> &rhs);

private:
    ListNode<Object> *header;
};


#include "linkedlistt.cpp"

#endif // LINKEDLIST_H

