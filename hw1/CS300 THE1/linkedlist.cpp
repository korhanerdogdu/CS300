

#include "linkedlist.h"
using namespace std;


// defining constructor
template <class Object>

Stack<Object>::Stack( ){
    
    topOfStack = NULL;
}



template <class Object>

bool Stack<Object>::isFull( ) const{
    return false;
}




/*
       * Test if the stack is logically empty.
       * Return true if empty, false, otherwise.
       */


template <class Object>
bool Stack<Object>::isEmpty( ) const{
    
    return topOfStack == NULL;
}

/*
       * Get the most recently inserted item in the stack.
       * Return the most recently inserted item in the stack
       * or throw an exception if empty.
       */

template <class Object>
const Object & Stack<Object>::top( ) const{
    
    return topOfStack->element;
        
}



template <class Object>
void Stack<Object>::pop(Object &x ) {
    
     ListNode<Object> *oldTop = topOfStack;
     topOfStack = topOfStack->next;
     delete oldTop;
}


template <class Object>
void Stack<Object>::push( const Object & x ){
    
    

     topOfStack = new ListNode( x, topOfStack );
    
}



template <class Object>
Object Stack<Object>::topAndPop( ){
    
     Object topItem = top( );
     pop( );
     return topItem;
}



/*
       * Make the stack logically empty.
       */


template <class Object>

void Stack<Object>::makeEmpty( ){
    
    while ( ! isEmpty( ) )
         pop( );
}







template <class Object>
const Stack<Object> & Stack<Object>:: operator=( const Stack<Object> & rhs ){
    
    if ( this != &rhs ){
        
        makeEmpty( );
        if ( rhs.isEmpty( ) )
            return *this;
        
        ListNode<Object> *rptr = rhs.topOfStack;
        ListNode<Object> *ptr  = new ListNode( rptr->element );
        topOfStack = ptr;

        for ( rptr = rptr->next; rptr != NULL; rptr = rptr->next )
            
            ptr = ptr->next = new ListNode( rptr->element );
        
    }
    return *this;
}





/*
* Copy constructor.
*/

template <class Object>

Stack<Object>::Stack( const Stack<Object> & rhs ){
    
       topOfStack = NULL;
       *this = rhs; // deep copy
}





/*
       * Destructor.
       */

template <class Object>
Stack<Object>::~Stack( ){
    
      makeEmpty( );
}

















