
#include "HashTable.h"

template <class HASHOBJ>
void HashTable<HASHOBJ>::PrintItAll()
{
    for (int i = 0; i < linkedlists.size(); i ++)
    {
        cout << "HASH[" << i << "] = " << endl;
        linkedlists[i].printer();
        cout << endl;
    }
}




bool isPrime( int n ) //checks if n is a prime number
{
    if ( n == 2 || n == 3 )
        return true;
    
    if ( n == 1 || n % 2 == 0 )
        return false;
    
    for ( int i = 3; i * i <= n; i += 2 )
        if ( n % i == 0 )
            return false;
    return true;
}



int nextPrime( int n ) //finds the next prime after n if n isnt a prime
{
    if ( n % 2 == 0 )
        n++;
    for ( ; ! isPrime( n ); n += 2 )
        ;
    
    return n;
}


long long int hashh(const string & S, int tableSize) //hashing function
{
    long long int L = 0;
    int d = 26;
    
    for (int i=0; i < S.length(); i++)
    {
        L = L + d * S[i];
        d = d * 43;
    }
    L = L % tableSize;
    if (L < 0)
        L = L + tableSize;
    return L;

}






template <class HASHOBJ>
void HashTable<HASHOBJ>::update_document_info(const HASHOBJ & x, const string & y, const bool & t){
    
    List<HASHOBJ> & whichList = linkedlists[hashh( x, linkedlists.size( ) ) ];
    ListItr<HASHOBJ> itr = whichList.find( x );
    if (!itr.isPastEnd( ))
        whichList.changeInfo(itr, y, t);
}



template <class HASHOBJ>
string HashTable<HASHOBJ>::final_Doc_info_in_specific_file_for_word(const HASHOBJ & x){
    
    List<HASHOBJ> & whichList = linkedlists[hashh( x, linkedlists.size( ) ) ];
    ListItr<HASHOBJ> itr = whichList.find( x );
    return itr.retrieveInfo();
    
}


template <class HASHOBJ>
const vector<string> & HashTable<HASHOBJ>::return_document_vector(const HASHOBJ & x)
{
    List<HASHOBJ> & whichList = linkedlists[hashh( x, linkedlists.size( ) ) ];
    ListItr<HASHOBJ> itr = whichList.find( x );
    return itr.AllInfo();
}

template <class HASHOBJ>
void HashTable<HASHOBJ>::loadfactor_wordcount_info()
{
    double load = double(count)/linkedlists.size();
    cout << "After preprocessing, the unique word count is " << count << ". Current load ratio is " << load << "." << endl;
}






template <class HASHOBJ>
HashTable<HASHOBJ>::HashTable(const HASHOBJ & notFound, int size, int count )
: NULLITEM( notFound ), linkedlists( nextPrime(size ) )
{
}




template <class HASHOBJ>
void HashTable<HASHOBJ>::insertList(List<HASHOBJ> & l)
{
    if (l.isEmpty())
        return;
    ListItr<HASHOBJ> itr = l.first();
    while (!itr.isPastEnd())
    {
        string s = itr.retrieve();
        insert(s);
        for (int i=0; i< itr.infosize(); i++)
        {
            update_document_info(s, itr.infAt(i), true);
        }
        itr.advance();
    }
}





template <class HASHOBJ>
void HashTable<HASHOBJ>::rehashing()
{
    vector<List<HASHOBJ>> temp = linkedlists;
    linkedlists.clear();
    count = 0;
    linkedlists.resize(nextPrime(temp.size()*2));
    for (int i = 0; i < temp.size(); i ++)
    {
        insertList(temp[i]);
    }
    
}



template <class HASHOBJ>
void HashTable<HASHOBJ>::makeEmpty( )
{
    for( int i = 0; i < linkedlists.size( ); i++ )
        linkedlists[ i ].makeEmpty( );
}



template <class HASHOBJ>
void HashTable<HASHOBJ>::insert(const HASHOBJ & x){
    
    
    List<HASHOBJ> & whichList = linkedlists[hashh( x, linkedlists.size())];
    
    
    ListItr<HASHOBJ> itr = whichList.find( x );
    
    if (itr.isPastEnd( ))
    {
        whichList.insert(x, whichList.zeroth( ));
        count++;
        
    }
    double load = double(count)/linkedlists.size();
    if (load > 0.9) //if the load factor exceeds 0.9  we start to rehashing
    {
        int prev = linkedlists.size();
        rehashing();
        load = double(count)/linkedlists.size();
        /*
        cout << "rehashed..." << endl;
        cout << "previous table size: " << prev << ", new table size: " << linkedlists.size() << ", current unique word count " << count + 1 << ", current load factor: " << load << endl;
         */
        
          
        
    }
}









template <class HASHOBJ>
void HashTable<HASHOBJ>::remove( const HASHOBJ & x )
{
    
    linkedlists[hashh( x, linkedlists.size( ) )].remove( x );
    count--;
    
}


template <class HASHOBJ>
const HASHOBJ & HashTable<HASHOBJ>::find (const HASHOBJ & x) const
{
    ListItr<HASHOBJ> itr;
    itr = linkedlists[ hashh( x, linkedlists.size( ) ) ].find( x );
    if (itr.isPastEnd( ) )
        return NULLITEM;
    return itr.retrieve( );
}



template <class HASHOBJ>
HashTable<HASHOBJ>::~HashTable()
{
    makeEmpty();
}




