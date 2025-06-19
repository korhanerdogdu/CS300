// AVLSearchTree.cpp

#include "AVLSEARCHTREE.h"

template <class Key, class Value>
AVLSearchTree<Key, Value>::AVLSearchTree() : root(nullptr) {}

template <class Key, class Value>
AVLSearchTree<Key, Value>::~AVLSearchTree() {
    makeEmpty();
}



template <class Key, class Value>
int AVLSearchTree<Key, Value>::height(AvlNode* t) const {
    return t == nullptr ? -1 : t->height;
}




template <class Key, class Value>
int AVLSearchTree<Key, Value>::max(int lhs, int rhs) const {
    return lhs > rhs ? lhs : rhs;
}



template <class Key, class Value>
void AVLSearchTree<Key, Value>::rotateWithLeftChild(AvlNode*& k2) {
    AvlNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}



template <class Key, class Value>
void AVLSearchTree<Key, Value>::rotateWithRightChild(AvlNode*& k1) {
    AvlNode* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::doubleWithLeftChild(AvlNode*& k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::doubleWithRightChild(AvlNode*& k1) {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}




template <class Key, class Value>
void AVLSearchTree<Key, Value>::insert(const Key& key, Value* value, AvlNode*& t) {
    if (t == nullptr)
        t = new AvlNode(key, value, nullptr, nullptr);
    
    else if (key < t->key) {
        
        insert(key, value, t->left);
        
        if (height(t->left) - height(t->right) == 2) {
            
            if (key < t->left->key)
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        }
    }
    
    else if (t->key < key) {
        
        insert(key, value, t->right);
        if (height(t->right) - height(t->left) == 2) {
            
            if (t->right->key < key)
                rotateWithRightChild(t);
            
            
            else
                doubleWithRightChild(t);
        }
    }
    
    
    else {
        
        // Duplicate key, update value
        t->value = value;
    }

    t->height = max(height(t->left), height(t->right)) + 1;
}



template <class Key, class Value>
void AVLSearchTree<Key, Value>::insert(const Key& key, Value* value) {
    insert(key, value, root);
}



template <class Key, class Value>
Value* AVLSearchTree<Key, Value>::find(const Key& key, AvlNode* t) const {
    while (t != nullptr) {
        if (key < t->key)
            t = t->left;
        else if (t->key < key)
            t = t->right;
        else
            return t->value;  
    }
    return nullptr;  // No match
}


template <class Key, class Value>
Value* AVLSearchTree<Key, Value>::find(const Key& key) const {
    return find(key, root);
}





template <class Key, class Value>
void AVLSearchTree<Key, Value>::remove(const Key& key, AvlNode*& t) {
    AvlNode* removedNode = nullptr;

    if (t == nullptr) {
        return;
    }

    if (key < t->key) {
        remove(key, t->left);
        
    } else if (t->key < key) {
        remove(key, t->right);
        
    } else {
        removedNode = t;
        if (t->left != nullptr && t->right != nullptr) {
            
            t->key = findMin(t->right)->key;
            t->value = findMin(t->right)->value;
            remove(t->key, t->right);
        } else {
            
            AvlNode* oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode->value;
            delete oldNode;
        }

        // Update height and balance factor
        if (t != nullptr) {
            t->height = max(height(t->left), height(t->right)) + 1;
            t->balanceFactor = height(t->left) - height(t->right);
        }

        // Perform AVL tree rotations if needed
        balance(t);
        
        
        delete removedNode->value;
        delete removedNode;
    }
}



template <class Key, class Value>
void AVLSearchTree<Key, Value>::remove(const Key& key) {
    
    remove(key, root);

}


template <class Key, class Value>
void AVLSearchTree<Key, Value>::makeEmpty(AvlNode*& t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}




template <class Key, class Value>
void AVLSearchTree<Key, Value>::makeEmpty() {
    makeEmpty(root);
}



// Function to find the node with the smallest key in a subtree
template <class Key, class Value>
typename AVLSearchTree<Key, Value>::AvlNode* AVLSearchTree<Key, Value>::findMin(AvlNode* t) const {
    if (t == nullptr) {
        return nullptr;
    }

    while (t->left != nullptr) {
        t = t->left;
    }

    return t;
}

// Function to perform AVL tree rotations
template <class Key, class Value>
void AVLSearchTree<Key, Value>::balance(AvlNode*& t) {
    if (t == nullptr) {
        return;
    }

    // Left heavy
    if (t->balanceFactor > 1) {
        if (height(t->left->left) >= height(t->left->right)) {
            rotateWithLeftChild(t);
        } else {
            doubleWithLeftChild(t);
        }
    }
    // Right heavy
    else if (t->balanceFactor < -1) {
        if (height(t->right->right) >= height(t->right->left)) {
            rotateWithRightChild(t);
        } else {
            doubleWithRightChild(t);
        }
    }
}


 




