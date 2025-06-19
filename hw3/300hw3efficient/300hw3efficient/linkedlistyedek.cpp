
//(I AM USİNG XCODE)


#ifndef linkedlist_h
#define linkedlist_h



#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class Comparable>
class ListItr;
template <class Comparable>
class List;


template <class Object>
        class ListNode
        {
            ListNode( const Object & theElement = Object( ), ListNode * n = NULL)
                  : element( theElement ), next( n ){ }

            Object element;
            vector<string> info;
            ListNode *next;
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
        return current->element;
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
    
    ListNode<Object> *current;
    
    ListItr( ListNode<Object> *theNode ): current( theNode ) { }
    
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
            ListNode<Object> *header;
 };

template <class Object>
List<Object>::List( ){
    header = new ListNode<Object>;
}

template <class Object>
bool List<Object>::isEmpty( ) const{
    return header->next == NULL;
}

template <class Object>
void List<Object>::insert( const Object & x, const ListItr<Object> & p){
    if ( p.current != NULL )
        p.current->next = new ListNode<Object>( x, p.current->next);
}

template <class Object>
void List<Object>::printer(){
    ListNode<Object> *itr = header->next;
    while ( itr != NULL)
    {
        cout << itr->element << " ";
        for (int g=0; g < itr->info.size(); g++)
            cout  << itr->info[g] << " ";
        cout << endl;
        itr = itr->next;
    }
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
    ListNode<Object> *itr = header->next;
    while ( itr != NULL && itr->element != x )
        itr = itr->next;
    return ListItr<Object>( itr );
}

template <class Object>
ListItr<Object> List<Object>::findPrevious( const Object & x ) const{
     ListNode<Object> *itr = header;
     while ( itr->next != NULL && itr->next->element != x )
             itr = itr->next;
    return ListItr<Object>( itr );
}


template <class Object>
void List<Object>::remove( const Object & x ){
    ListItr<Object> p = findPrevious( x );
    if ( p.current->next != NULL )
    {
        ListNode<Object> *oldNode = p.current->next;
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
List<Object>::List( const List<Object> & rhs ){
       header = new ListNode<Object>;
      *this = rhs;
}



template <class Object>
List<Object>::~List(){
    makeEmpty();
}

#endif












/*
 
 
 
 Bu rehash fonksiyonu, HashTable sınıfının bir parçası olarak tanımlanmış ve karma tablonun yeniden boyutlandırılması (rehashing) için kullanılıyor. İşlevsellik olarak ne yaptığını adım adım inceleyelim:

 rehash Fonksiyonunun İşlevi
 Mevcut Liste Kopyalanıyor:

 vector<List<HashedObj>> temp = theLists; satırı mevcut listeleri (karma tablonun tüm kovalarını) geçici bir temp vektörüne kopyalar. Bu, yeniden boyutlandırma sırasında mevcut verilerin korunmasını sağlar.
 Mevcut Listeleri Temizleme ve Sayacı Sıfırlama:

 theLists.clear(); ile mevcut karma tablo temizlenir.
 count = 0; ile tabloda saklanan benzersiz öğe sayısını sıfırlar. Bu, yeniden boyutlandırıldıktan sonra öğeler yeniden eklenirken doğru sayım yapılmasını sağlar.
 Tablonun Boyutunu İki Katına Çıkararak Yeniden Boyutlandırma:

 theLists.resize(nextPrime(temp.size()*2)); satırı, mevcut tablo boyutunun iki katı olan bir sayıyı alır ve bu sayıyı bir sonraki asal sayıya yuvarlar. Bu yeni boyut, karma tablonun yeni boyutu olarak kullanılır. Asal sayı kullanılması, çakışma olasılığını azaltmaya yardımcı olur ve karma tablonun daha verimli çalışmasını sağlar.
 
 
 Eski Verileri Yeniden Ekleme:

 Son döngü (for (int i = 0; i < temp.size(); i++)), geçici temp vektöründe saklanan eski öğeleri yeni boyutlandırılmış theLists vektörüne geri ekler. insertList fonksiyonu, her listenin öğelerini tek tek yeni tabloya ekler.
 
 
 Özet
 Bu rehash fonksiyonu, karma tablonun verimliliğini korumak ve yük faktörünü yönetmek için çok önemlidir. Tablonun doluluk oranı belirli bir sınırı aştığında, bu fonksiyon tabloyu daha büyük bir boyuta yeniden boyutlandırır ve tüm öğeleri yeni tabloya yeniden dağıtır. Bu işlem, karma tablonun performansını optimize eder ve arama, ekleme ve silme işlemlerinin hızlı kalmasını sağlar.
 
 
 */



/*
 
 
 
 Hash Table:
 +---------------------------+
 | Index | Bağlı Liste       |
 |---------------------------|
 | 0     | [ ]               |
 | 1     | [ "apple", "pear" ]| <-- "apple" ve "pear" bu listede
 | 2     | [ ]               |
 | ...   | ...               |
 | n     | [ "banana" ]      |
 +---------------------------+

 linked list zaten nodelardan oluşuyor.
 
 template <class Object>
         class ListNode
         {
             ListNode( const Object & theElement = Object( ), ListNode * n = NULL)
                   : element( theElement ), next( n ){ }

             Object   element;
             vector<string> info; //vector of informations such as { a.txt, 5}
             ListNode *next;
             friend class List<Object>;
             friend class ListItr<Object>;
         };
 
 
 
 
 changeInfo Fonksiyonu Kullanımı:
 
 changeInfo("apple", "Yeni Bilgi", t)

 1. "apple" için hash değerini hesapla.
    - Örneğin, hashh("apple") = 1 döndü diyelim.

 2. İlgili kovayı bul.
    - whichList = theLists[1]

 3. Kovada "apple" stringini bul.
    - "apple" stringini listede bulana kadar liste üzerinde yineleme yap.

 4. "apple" bulunursa, bilgisini "Yeni Bilgi" ile güncelle.
    - whichList içinde "apple" öğesi bulunduğunda, onun bilgisini "Yeni Bilgi" ile güncelle.

 
 
 
 
 Hash Table Öncesi Durum:
 +---------------------------+
 | Index | Bağlı Liste       |
 |---------------------------|
 | ...   | ...               |
 | 1     | [ "apple", "pear" ]|
 | ...   | ...               |
 +---------------------------+

 changeInfo("apple", "Yeni Bilgi", t) Çağrısı Sonrası:
 +---------------------------+
 | Index | Bağlı Liste       |
 |---------------------------|
 | ...   | ...               |
 | 1     | [ "apple (Yeni Bilgi)", "pear" ]| <-- "apple" bilgisi güncellendi
 | ...   | ...               |
 +---------------------------+

 
 
 
 
 
 "apple (Yeni Bilgi)" ifadesi, bir HashTable'da saklanan bir öğenin görselleştirilmiş bir temsilidir ve genellikle iki parçadan oluşur:

 Anahtar (Key): "apple", bu durumda hash table'da saklanan öğenin kendisidir. Bu, öğenin tanımlayıcısı veya benzersiz adıdır.

 Ek Bilgi (Additional Information): "(Yeni Bilgi)", bu öğeyle ilişkilendirilmiş ek bilgiyi temsil eder. Bu ek bilgi, öğe hakkında daha fazla ayrıntı veya veri içerebilir. Örneğin, bir kelimenin hangi dosyalarda kaç kez geçtiği gibi.

 Bu yapı, bir HashTable içerisinde her bir öğenin (bu örnekte bir string) yanında ek bilgilerin de saklanabileceğini gösterir. Gerçek bir uygulamada, bu "Yeni Bilgi" herhangi bir formatta olabilir ve öğe hakkında çeşitli verileri içerebilir. Örneğin, bir kelimenin belirli bir metin içindeki frekansı, kelimenin metindeki konumu veya başka ilgili metadatalar olabilir.

 Bu tür bir yapı, genellikle özel bir sınıf veya yapı (struct) ile C++'ta temsil edilir.
 
 
 
 
 
 
 
 
 HashTable'da "apple" stringini eklemek için insert("apple") kullanılır.
 Daha sonra, "apple" stringinin bilgisini güncellemek için changeInfo("apple", "Yeni Bilgi", true) çağrılır.

 
 Hash Table:
 +--------------------------------+
 | Index | Bağlı Liste            |
 |--------------------------------|
 | ...   | ...                    |
 | k     | [ Node("apple", ...) ] | <-- "apple" ve ek bilgileri burada
 | ...   | ...                    |
 +--------------------------------+

 
 
 
 
 */







//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//! (I AM USİNG XCODE)
// I REMOVED THE REFERENCE OF BinarySearchTree.cpp FİLE, AND ADDED IT AT THE END OF THIS HEADER FILE

#pragma once
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


template <class Objectt>
class BinarySearchTree;


template <class Objectt>

class BinaryNode  // it can be also in public or private.
{
    public:
    
    // the modifications made in public or private classes, will affect the original, no need to use reference types a lot in function parameters.
    
    
    Objectt element;
    BinaryNode  *left;
    BinaryNode  *right;
    vector<string> info; //to store the description of an item
    BinaryNode(const Objectt & theElement,  BinaryNode *lt = NULL, BinaryNode *rt = NULL): element(theElement), left(lt), right(rt)
    {}
    friend class BinarySearchTree<Objectt>;
    
};




template <class Objectt>
class BinarySearchTree
{
public:
    
    
    explicit BinarySearchTree(const Objectt & notFound );
    BinarySearchTree(const BinarySearchTree & rhs);
    ~BinarySearchTree( );
    vector<string> & doc_infos(Objectt & y);
    const Objectt & findMin() const;
    const Objectt & findMax() const;
    const Objectt & find(const Objectt & x ) const;
    bool isEmpty( ) const;
    const Objectt & infoAt(BinaryNode<Objectt> * t) const;
    // if we have defined the BinaryNode in private, this wouldn't work beacuse infoAt function is in public and we call the BinaryNode  in public . What we could do for another way is defined below:
    
    
    /*
     
     
     template <class Key, class Value>
     class BinarySearchTree {
     public:
         BinarySearchTree();
         ~BinarySearchTree();

         void insert(const Key& key, Value* value);
         void remove(const Key& key);
         Value* find(const Key& key) const;
         void makeEmpty();

     private:
         struct BSTNode {  //since it is a private value, we can only call by the functions that are defined in the private part.
     
             Key key;
             Value* value;
             BSTNode *left, *right;

             BSTNode(Key k, Value* v, BSTNode* lt, BSTNode* rt);
         };

         BSTNode* root;

         void insert(const Key& key, Value* value, BSTNode*& t);
         void remove(const Key& key, BSTNode*& t);
         Value* find(const Key& key, BSTNode* t) const;
         void makeEmpty(BSTNode*& t);
         BSTNode* findMin(BSTNode* t) const;
     
     };
     */
    
    const Objectt & findInfo(const Objectt & x) const;
    void printTree( ) const; //prints the binary tree
    void makeEmpty(); //clears the tree
    void insert( const Objectt & x ); //adds a new element
    void remove(const Objectt & x); //removes the inputted element
    const BinarySearchTree<Objectt> & operator=(const BinarySearchTree<Objectt> & rhs);
    void update_document_info(Objectt & x, string & d, const bool & a);
    
private:
    
    
    //private functions help to make recursions for the public fuctions
    const Objectt ITEM_NOT_FOUND;
    BinaryNode<Objectt> *root;
    void displaySections(BinaryNode<Objectt> * t) const;
    const Objectt & elementAt(BinaryNode<Objectt> *t) const;
    void insert( const Objectt & x, BinaryNode<Objectt> * & t ) const;
    void remove( const Objectt & x, BinaryNode<Objectt> * & t ) const;
    BinaryNode<Objectt> * findMin( BinaryNode<Objectt> *t ) const;
    BinaryNode<Objectt> * findMax( BinaryNode<Objectt> *t ) const;
        
    BinaryNode<Objectt> * find( const Objectt & x, BinaryNode<Objectt> *t ) const;
    void makeEmpty(BinaryNode<Objectt> * & t) const;
    void printTree(BinaryNode<Objectt> *t) const;
    BinaryNode<Objectt> * clone( BinaryNode<Objectt> *t ) const;
};




#include "BinarySearchTree.cpp"

#endif










//
//  BST.cpp
//  300hw3efficient
//
//  Created by KORHAN ERDOĞDU on 20.12.2023.
//

#include "BinarySearchTree.h"



template <class Objectt>
BinarySearchTree<Objectt>::BinarySearchTree(const Objectt & noitem ) : ITEM_NOT_FOUND(noitem), root(NULL){


}


template <class Objectt>
bool BinarySearchTree<Objectt>::isEmpty() const{

    if (root == NULL)
        return true;
    return false;
}




template <class Objectt>
const BinarySearchTree<Objectt> & BinarySearchTree<Objectt>::operator=(const BinarySearchTree<Objectt> & rhs)
{
    if (this != &rhs){
        
        makeEmpty();
        root = rhs.clone(rhs.root);
    }
    return *this;
}



template <class Objectt>
const Objectt & BinarySearchTree<Objectt>::elementAt(BinaryNode<Objectt> * t) const{
    
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}


template <class Objectt>
BinaryNode<Objectt> * BinarySearchTree<Objectt>::find(const Objectt & x, BinaryNode<Objectt> * t) const
{
    if ( t == NULL )
        return NULL;
    else if(x < t->element)
        return find(x, t->left);
    else if(t->element < x)
        return find(x, t->right);
    else
        return t;
}




template <class Objectt>
const Objectt & BinarySearchTree<Objectt>::find(const Objectt & x) const{
    
    return elementAt(find( x, root));
}




template <class Objectt>
BinaryNode<Objectt> * BinarySearchTree<Objectt>::findMin( BinaryNode<Objectt> *t ) const{
    
    
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
    
}





template <class Objectt>
const Objectt & BinarySearchTree<Objectt>::findMin()const{
    
    return elementAt(findMin(root));
}




template <class Objectt>
BinaryNode<Objectt> * BinarySearchTree<Objectt>::findMax(BinaryNode<Objectt> *t)const{
    
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;
}




template <class Objectt>
const Objectt & BinarySearchTree<Objectt>::findMax() const{
    
    return elementAt(findMax(root));
}

template <class Objectt>
void BinarySearchTree<Objectt>::insert(const Objectt & x, BinaryNode<Objectt> * & t ) const{
    
    if( t == NULL )
        t = new BinaryNode<Objectt>(x);
    else if(x < t->element)
        insert( x, t->left);
    else if(t->element < x)
        insert(x, t->right);
    else
        ;
}

template <class Objectt>
void BinarySearchTree<Objectt>::insert( const Objectt & x ){
    
    insert(x, root);
}


template <class Objectt>
void BinarySearchTree<Objectt>::remove(const Objectt & x, BinaryNode<Objectt> * & t) const{
    
    if(t == NULL)
        return;
    if (x < t->element)
        remove(x, t->left);
    else if(t->element < x)
        remove(x, t->right);
    else if(t->left != NULL && t->right != NULL)
    {
        t->element = findMin( t->right )->element;
        remove( t->element, t->right );
    }
    else
    {
        BinaryNode<Objectt> *oldNode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldNode;
    }
}


template <class Objectt>
void BinarySearchTree<Objectt>::remove(const Objectt & x){
   
    remove(x, root);
}

template <class Objectt>
void BinarySearchTree<Objectt>::makeEmpty( BinaryNode<Objectt> * & t ) const{
    
    if( t != NULL )
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = NULL;
}


template <class Objectt>
void BinarySearchTree<Objectt>::makeEmpty( ){
    
    makeEmpty(root);
}


template <class Objectt>
void BinarySearchTree<Objectt>::printTree(BinaryNode<Objectt> * t) const{
    
      if ( t != NULL )
      {
            printTree (t->left);
            cout << t->element << endl;
          string a = "{";
          for (int i = 0; i < t->info.size(); i++)
          {
              a = a + " " + t->info[i];
          }
          a = a + "}";
          cout << a << endl;
          printTree(t->right);
      }
}

template <class Objectt>
void BinarySearchTree<Objectt>::printTree() const{
    
   
    if(isEmpty())
        cout << "Empty tree" << endl;
    else
    {
        printTree(root);
    }
}


template <class Objectt>
BinarySearchTree<Objectt>::~BinarySearchTree()
{
    makeEmpty( );
}



template <class Objectt>
BinaryNode<Objectt> * BinarySearchTree<Objectt>:: clone( BinaryNode<Objectt> * t ) const{
    
    if (t == NULL )
        return NULL;
    else
    {
        BinaryNode<Objectt> temp = new BinaryNode<Objectt> (t->element);
        for(int i=0; i < t->info.size(); i++){
            
            temp->info.push_back(t->info[i]);
        }
        temp->left = clone(t->left);
        temp->right = clone(t->right);
        return temp;
    }
}


template <class Objectt>
BinarySearchTree<Objectt>::BinarySearchTree(const BinarySearchTree<Objectt> & rhs): root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND)
{
    *this = rhs;
}

template <class Objectt>
void BinarySearchTree<Objectt>::update_document_info(Objectt & word, string & newInfo, const bool & flag){
    
    BinaryNode<Objectt> * location = find(word, root);
    if (location != NULL )
        
    {
        unsigned long int idx = location->info.size() - 1;
        if (!flag)
            location->info[idx] = newInfo;
        else
            location->info.push_back(newInfo);
    }
}



template <class Objectt>
vector<string> & BinarySearchTree<Objectt>::doc_infos(Objectt & y){
    
    
    BinaryNode<Objectt> * c = find(y,root);
    return c->info;
    
    
}












