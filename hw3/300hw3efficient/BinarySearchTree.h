

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

class BSTNode  // it can be also in public or private.

{
    public:
    
    // the modifications made in public or private classes, will affect the original, no need to use reference types a lot in function parameters.
    
    
    Objectt obj;
    
    BSTNode  *left;
    
    BSTNode  *right;
    
    vector<string> info; //to store the document vector.
    
    BSTNode(const Objectt & objectt,  BSTNode *lt = NULL, BSTNode *rt = NULL): obj(objectt), left(lt), right(rt)
    
    
    {}
    
    
    friend class BinarySearchTree<Objectt>;
    
};




template <class Objectt>
class BinarySearchTree{
    
public:
    
    
    explicit BinarySearchTree(const Objectt & notFound );
    
    
    BinarySearchTree(const BinarySearchTree & rhs);
    
    ~BinarySearchTree( );
    
    vector<string> & doc_infos(Objectt & y);
    
    const Objectt & findMin() const;
    
    const Objectt & findMax() const;
    
    const Objectt & find(const Objectt & x ) const;
    
    bool isEmpty( ) const;
    
    const Objectt & infoAt(BSTNode<Objectt> * t) const;
    // if we have defined the BSTNode in private, this wouldn't work beacuse infoAt function is in public and we call the BSTNode  in public . What we could do for another way is defined below:
    
    
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
    
    void printTree( ) const;
    
    void makeEmpty();
    
    void insert( const Objectt & x );
    
    void remove(const Objectt & x);

    const BinarySearchTree<Objectt> & operator=(const BinarySearchTree<Objectt> & rhs);
    
    void update_document_info(Objectt & x, string & d, const bool & a);
    
    
private:
    
    
    const Objectt NULLITEM;
    
    BSTNode<Objectt> *root;
    
    
    
    
    
    void printTree(BSTNode<Objectt> *t) const;
    
    
    
    void displaySections(BSTNode<Objectt> * t) const;
    
    BSTNode<Objectt> * findMin( BSTNode<Objectt> *t ) const;
    
    
    BSTNode<Objectt> * findMax( BSTNode<Objectt> *t ) const;
    
    
    const Objectt & elementAt(BSTNode<Objectt> *t) const;
    
    void makeEmpty(BSTNode<Objectt> * & t) const;

    
    void insert( const Objectt & x, BSTNode<Objectt> * & t ) const;
    
    
    BSTNode<Objectt> * find( const Objectt & x, BSTNode<Objectt> *t ) const;
    

    
    
    void remove( const Objectt & x, BSTNode<Objectt> * & t ) const;
    
    

    

    
    
    BSTNode<Objectt> * clone( BSTNode<Objectt> *t ) const;
};




#include "BinarySearchTree.cpp"

#endif

