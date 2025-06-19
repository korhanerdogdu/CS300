

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




/*
 
 vector<List<HashedObj>> linkedlists:

 Bu, hash table'ın temel veri yapısını oluşturur. vector, hash table'ın kovalarını (buckets) temsil eder ve her kova, List<HashedObj> tipinde bir bağlı liste içerir.
 HashedObj tipi, bu hash table'da saklanacak olan nesnelerin türünü belirtir. Bu tür, template parametresi olarak belirtilir, böylece hash table farklı veri türleri için kullanılabilir.
 Her bir liste, aynı hash değerine sahip öğeleri saklar, böylece hash çakışmaları yönetilebilir.
 
 
 
 
 const HASHOBJ NULLITEM:

 Bu değişken, aranan bir öğe hash table'da bulunamadığında döndürülecek olan özel bir değeri temsil eder.
 Genellikle, arama işlemlerinde bir öğenin bulunup bulunmadığını kontrol etmek için kullanılır. Eğer bir öğe hash table'da yoksa, bu ITEM_NOT_FOUND değeri döndürülür.
 
 
 
 
 int count:

 Bu değişken, hash table'da şu anda saklanan benzersiz öğelerin sayısını tutar.
 Bu sayı, yeni öğeler eklendiğinde artar ve öğeler silindiğinde azalır. Hash table'ın doluluk oranını (load factor) hesaplamak için kullanılır.
 
 
 */






#include "HashTable.cpp"


#endif /* theHash_hpp */
