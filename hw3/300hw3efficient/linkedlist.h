
//(I AM USİNG XCODE)


#ifndef linkedlist_h
#define linkedlist_h


#include <string>
#include <vector>
#include <iostream>



using namespace std;

template <class ListItem>
class ListItr;


template <class ListItem>
class List;


template <class Object>
        class LinkedListNode
        {
            LinkedListNode( const Object & object = Object( ), LinkedListNode * n = NULL)
                  : obj( object ), next( n ){ }

            Object obj;
            
            vector<string> info;
            
            LinkedListNode *next;
            
            friend class List<Object>;
            
            friend class ListItr<Object>;
        };



template <class Object>

class ListItr {
    
    
    
public:
    
    ListItr( ) : current( NULL ) { }
    
    bool isPastEnd( ) const{
        return current == NULL;
    }
    
    void advance( ){
        if ( ! isPastEnd( ) ){
            current = current->next;
        }
    }
    
    const Object & retrieve( ) const{
        return current->obj;
    }
    
    const string & retrieveInfo( ) const {
        return current->info[current->info.size()-1];
    }
    
    const int infosize( ) const {
        return current->info.size();
        
    }
    
    void pushInfo(string s) const {
        return current->next->info.push_back(s);
        
    }
    
    const string & infAt(int a) const {
        return current->info[a];
        
    }
    
    const vector<string> & AllInfo() const {
        return current->info;
    }
    
    
private:
    
    LinkedListNode<Object> *current;
    
    ListItr( LinkedListNode<Object> *theNode ): current( theNode ) { }
    
    friend class List<Object>;
    
    
};

template <class Object>
class List

{
      public:
    
            List( );
    
    
            List( const List & rhs );
    
    
            ~List( );
    
            bool isEmpty( ) const;
    
    
            void makeEmpty( );
    
    
            ListItr<Object> zeroth( ) const;
    
    
            ListItr<Object> first( ) const;
    
    
            void insert( const Object & x, const ListItr<Object> & p);
    
    
            void changeInfo(const ListItr<Object> & p, const string & y, const bool &);
    
    
            ListItr<Object> find( const Object & x ) const;
    
    
            ListItr<Object> findPrevious( const Object & x ) const;
    
    
            void remove( const Object & x );
    
    
            void printer();
    
    
            const List<Object> & operator=( const List<Object> & rhs );

       private:
            LinkedListNode<Object> *header;
 };



template <class Object>
List<Object>::List( const List<Object> & rhs ){
       header = new LinkedListNode<Object>;
      *this = rhs;
}



template <class Object>
void List<Object>::insert( const Object & x, const ListItr<Object> & p){
    if ( p.current != NULL )
        p.current->next = new LinkedListNode<Object>( x, p.current->next);
}


template <class Object>
void List<Object>::printer(){
    LinkedListNode<Object> *itr = header->next;
    while ( itr != NULL)
    {
        cout << itr->obj << " ";
        for (int g=0; g < itr->info.size(); g++)
            cout  << itr->info[g] << " ";
        cout << endl;
        itr = itr->next;
    }
}



template <class Object>
List<Object>::List( ){
    header = new LinkedListNode<Object>;
}


template <class Object>
bool List<Object>::isEmpty( ) const{
    return header->next == NULL;
}





template <class Object>
void List<Object>::changeInfo(const ListItr<Object> & p, const string & newinfo, const bool & t){
      if ( p.current != NULL )
      {
          int idx = p.current->info.size() - 1;
          if (!t)
              p.current->info[idx] = newinfo;
          else
              p.current->info.push_back(newinfo);
      }
}





template <class Object>
ListItr<Object> List<Object>::find( const Object & x ) const{
    LinkedListNode<Object> *itr = header->next;
    while ( itr != NULL && itr->obj != x )
        itr = itr->next;
    return ListItr<Object>( itr );
}




template <class Object>
ListItr<Object> List<Object>::findPrevious( const Object & x ) const{
     LinkedListNode<Object> *itr = header;
     while ( itr->next != NULL && itr->next->obj != x )
             itr = itr->next;
    return ListItr<Object>( itr );
}


template <class Object>
void List<Object>::remove( const Object & x ){
    ListItr<Object> p = findPrevious( x );
    if ( p.current->next != NULL )
    {
        LinkedListNode<Object> *oldNode = p.current->next;
        p.current->next = p.current->next->next;
        delete oldNode;
    }
}





template <class Object>
ListItr<Object> List<Object>::zeroth( ) const{
   return ListItr<Object>( header );
}



template <class Object>
ListItr<Object> List<Object>::first( ) const{
    return ListItr<Object>( header->next );
}




template <class Object>
void List<Object>::makeEmpty( ){
       while ( ! isEmpty( ) )
              remove( first( ).retrieve( ) );
}




template <class Object>
const List<Object> & List<Object>::operator=( const List<Object> & rhs )
{
    if ( this != &rhs )
    {
          makeEmpty( );

          ListItr<Object> ritr = rhs.first( );
          ListItr<Object> itr = zeroth( );
        for (  ;  ! ritr.isPastEnd( ); ritr.advance( ), itr.advance( ) )
        {
            insert( ritr.retrieve( ), itr );
            for (int i=0; i < ritr.infosize(); i++)
            {
                string s = ritr.infAt(i);
                itr.pushInfo(s);
            }
        }
     }
   return *this;
}










template <class Object>
List<Object>::~List(){
    makeEmpty();
}

#endif



