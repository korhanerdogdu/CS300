

#include "linkedlistt.h"
#include <iostream>

/*
// ListNode Constructor (Template Implementation)
template <class Object>
ListNode<Object>::ListNode(const Object &theElement, ListNode *n)
    : element(theElement), next(n) {}

*/
// ListItr Class Template Implementations
template <class Object>
bool ListItr<Object>::isPastEnd() const {
    return current == NULL;
}

template <class Object>
void ListItr<Object>::advance() {
    if (!isPastEnd()) {
        current = current->next;
    }
}

template <class Object>
const Object &ListItr<Object>::retrieve() const {
    return current->element;
}

template <class Object>
const std::string &ListItr<Object>::retrieveInfo() const {
    return current->info.back();
}

template <class Object>
const int ListItr<Object>::infosize() const {
    return current->info.size();
}

template <class Object>
void ListItr<Object>::pushInfo(std::string s) const {
    current->info.push_back(s);
}

template <class Object>
const std::string &ListItr<Object>::infAt(int a) const {
    return current->info[a];
}

template <class Object>
const std::vector<std::string> &ListItr<Object>::AllInfo() const {
    return current->info;
}

// List Class Template Implementations
template <class Object>
List<Object>::List() {
    header = new ListNode<Object>();
}

template <class Object>
bool List<Object>::isEmpty() const {
    return header->next == NULL;
}

template <class Object>
void List<Object>::insert(const Object &x, const ListItr<Object> &p) {
    if (p.current != NULL) {
        p.current->next = new ListNode<Object>(x, p.current->next);
    }
}

template <class Object>
void List<Object>::printer() {
    ListNode<Object> *itr = header->next;
    while (itr != NULL) {
        std::cout << itr->element << " ";
        for (int g = 0; g < itr->info.size(); g++) {
            std::cout << itr->info[g] << " ";
        }
        std::cout << std::endl;
        itr = itr->next;
    }
}

template <class Object>
void List<Object>::changeInfo(const ListItr<Object> &p, const std::string &newinfo, const bool &t) {
    if (p.current != NULL) {
        int idx = p.current->info.size() - 1;
        if (!t)
            p.current->info[idx] = newinfo;
        else
            p.current->info.push_back(newinfo);
    }
}

template <class Object>
ListItr<Object> List<Object>::find(const Object &x) const {
    ListNode<Object> *itr = header->next;
    while (itr != NULL && itr->element != x)
        itr = itr->next;
    return ListItr<Object>(itr);
}

template <class Object>
ListItr<Object> List<Object>::findPrevious(const Object &x) const {
    ListNode<Object> *itr = header;
    while (itr->next != NULL && itr->next->element != x)
        itr = itr->next;
    return ListItr<Object>(itr);
}

template <class Object>
void List<Object>::remove(const Object &x) {
    ListItr<Object> p = findPrevious(x);
    if (p.current->next != NULL) {
        ListNode<Object> *oldNode = p.current->next;
        p.current->next = p.current->next->next;
        delete oldNode;
    }
}

template <class Object>
ListItr<Object> List<Object>::zeroth() const {
    return ListItr<Object>(header);
}

template <class Object>
ListItr<Object> List<Object>::first() const {
    return ListItr<Object>(header->next);
}

template <class Object>
void List<Object>::makeEmpty() {
    while (!isEmpty())
        remove(first().retrieve());
}

template <class Object>
const List<Object> &List<Object>::operator=(const List<Object> &rhs) {
    if (this != &rhs) {
        makeEmpty();
        ListItr<Object> ritr = rhs.first();
        ListItr<Object> itr = zeroth();
        for (; !ritr.isPastEnd(); ritr.advance(), itr.advance()) {
            insert(ritr.retrieve(), itr);
            for (int i = 0; i < ritr.infosize(); i++) {
                std::string s = ritr.infAt(i);
                itr.pushInfo(s);
            }
        }
    }
    return *this;
}

template <class Object>
List<Object>::List(const List<Object> &rhs) {
    header = new ListNode<Object>();
    *this = rhs;
}

template <class Object>
List<Object>::~List() {
    makeEmpty();
}

// Explicit template instantiation
template class List<int>; // Example for int
template class ListItr<int>;
// Add more instantiations as needed

