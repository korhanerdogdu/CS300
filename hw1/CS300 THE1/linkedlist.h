

#ifndef linkedlist_h
#define linkedlist_h

#include <stdio.h>

#endif




template <class Object>
struct ListNode{
    Object element;
    ListNode *next;
    ListNode(Object theElement, ListNode * n = NULL ) : element( theElement ), next( n ) { }
};  


template <class Object>
    class Stack{
public:
        
        
        Stack( );
        Stack(const Stack & rhs );
        ~Stack( );
    
        bool isEmpty( ) const;
        bool isFull( ) const;
        void makeEmpty( );
    
        void pop(Object &x);
        void push(const Object & x );
        
        Object topAndPop( );  // we are going to return a value which is a Object type
        const Object & top( ) const;
    
        const Stack & operator=( const Stack & rhs );
        
private:
        
        ListNode<Object> *topOfStack;
        
        //ListNode *topOfStack;  // list itself is the stack
  };









    
    
    
