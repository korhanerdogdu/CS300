

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//! (I AM USİNG XCODE)
// I REMOVED THE REFERENCE OF HashTable.cpp FİLE, AND ADDED IT AT THE END OF THIS HEADER FILE


#pragma once
#ifndef HashTable_h
#define HashTable_h



#include <vector>

#include "linkedlist.h"


using namespace std;

template <class HASHOBJ>
class HashTable

{
    
    
    public:
        HashTable( const HASHOBJ & notFound,
                  int size = 53, int count = 0); // count helps us to count the unique words
    
    
        void rehashing(); //changes the size of the vector

        void loadfactor_wordcount_info();
    
        void insertList(List<HASHOBJ> & l);
    
        HashTable( const HashTable & rhs )
        : NULLITEM( rhs.NULLITEM ),
        linkedlists( rhs.linkedlists ), count(rhs.count) { }
    
    
        void update_document_info(const HASHOBJ & x, const string & y, const bool &);
    
        string final_Doc_info_in_specific_file_for_word(const HASHOBJ & x);
    
    
    
        
    
        void makeEmpty( );

        const HASHOBJ & find( const HASHOBJ & x ) const;
    
    
        void remove( const HASHOBJ & x );

    

        void insert( const HASHOBJ & x); // inserting the string to the hash table
    
    
        const vector<string> & return_document_vector(const HASHOBJ & x);
    
    
        const HashTable & operator =( const HashTable & rhs);
    
    

    
        void PrintItAll();
    
    
        ~HashTable();
    
    
    
    private:
        vector<List<HASHOBJ>> linkedlists;
        const HASHOBJ NULLITEM;
        int count;
    
};






#include "HashTable.cpp"


#endif 

