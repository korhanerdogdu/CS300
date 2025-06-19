// AVLSearchTree.h


#pragma once



#ifndef AVLSEARCHTREE_H
#define AVLSEARCHTREE_H

#include <string>

template <class Key, class Value>
class AVLSearchTree {
public:
    // Constructor
    AVLSearchTree();

    // Destructor
    ~AVLSearchTree();

    // Insert a key-value pair into the tree
    void insert(const Key& key, Value* value);

    // Find a key in the tree and return the associated value
    Value* find(const Key& key) const;

    // Remove a key and its associated value from the tree
    void remove(const Key& key);

    // Check if the tree is empty
    bool isEmpty() const;

    // Make the tree empty
    void makeEmpty();

private:
    
    
    struct AvlNode {
        Key key;
        Value* value;
        AvlNode* left;
        AvlNode* right;
        int height;
        int balanceFactor; // new, for delete operations

        AvlNode(const Key& k, Value* v, AvlNode* lt, AvlNode* rt, int h = 0)
            : key(k), value(v), left(lt), right(rt), height(h), balanceFactor(0){}
    };
    
    

    AvlNode* root;

    // Helper functions for AVL operations
    int height(AvlNode* t) const;
    int max(int lhs, int rhs) const;
    void rotateWithLeftChild(AvlNode*& k2);
    void rotateWithRightChild(AvlNode*& k1);
    void doubleWithLeftChild(AvlNode*& k3);
    void doubleWithRightChild(AvlNode*& k1);

    // AVL operations
    void insert(const Key& key, Value* value, AvlNode*& t);
    Value* find(const Key& key, AvlNode* t) const;
    
    
    void remove(const Key& key, AvlNode*& t);
    void makeEmpty(AvlNode*& t);
    
    AvlNode* findMin(AvlNode* t) const;
    void balance(AvlNode*& t);
    
    
    
};

// Include the implementation directly in the header file

#include "AVLSEARCHTREE.cpp"

#endif



