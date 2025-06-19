
#include "BinarySearchTree.h"



template <class Objectt>
BinarySearchTree<Objectt>::BinarySearchTree(const Objectt & noitem ) : NULLITEM(noitem), root(NULL){


}


template <class Objectt>
bool BinarySearchTree<Objectt>::isEmpty() const{

    if (root == NULL)
        return true;
    return false;
}


template <class Objectt>
void BinarySearchTree<Objectt>::update_document_info(Objectt & word, string & newInfo, const bool & flag){
    
    BSTNode<Objectt> * location = find(word, root);
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
    
    
    BSTNode<Objectt> * c = find(y,root);
    return c->info;
    
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
const Objectt & BinarySearchTree<Objectt>::elementAt(BSTNode<Objectt> * t) const{
    
    return t == NULL ? NULLITEM : t->obj;
}


template <class Objectt>
BSTNode<Objectt> * BinarySearchTree<Objectt>::find(const Objectt & x, BSTNode<Objectt> * t) const
{
    if ( t == NULL )
        return NULL;
    else if(x < t->obj)
        return find(x, t->left);
    else if(t->obj < x)
        return find(x, t->right);
    else
        return t;
}




template <class Objectt>
const Objectt & BinarySearchTree<Objectt>::findMax() const{
    
    return elementAt(findMax(root));
}





template <class Objectt>
const Objectt & BinarySearchTree<Objectt>::find(const Objectt & x) const{
    
    return elementAt(find( x, root));
}





template <class Objectt>
void BinarySearchTree<Objectt>::insert(const Objectt & x, BSTNode<Objectt> * & t ) const{
    
    if( t == NULL )
        t = new BSTNode<Objectt>(x);
    else if(x < t->obj)
        insert( x, t->left);
    else if(t->obj < x)
        insert(x, t->right);
    else
        ;
}

template <class Objectt>
void BinarySearchTree<Objectt>::insert( const Objectt & x ){
    
    insert(x, root);
}




template <class Objectt>
BSTNode<Objectt> * BinarySearchTree<Objectt>::findMin( BSTNode<Objectt> *t ) const{
    
    
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
BSTNode<Objectt> * BinarySearchTree<Objectt>::findMax(BSTNode<Objectt> *t)const{
    
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;
}




template <class Objectt>
void BinarySearchTree<Objectt>::remove(const Objectt & x, BSTNode<Objectt> * & t) const{
    
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
        BSTNode<Objectt> *oldNode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldNode;
    }
}


template <class Objectt>
void BinarySearchTree<Objectt>::remove(const Objectt & x){
   
    remove(x, root);
}

template <class Objectt>
void BinarySearchTree<Objectt>::makeEmpty( BSTNode<Objectt> * & t ) const{
    
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
void BinarySearchTree<Objectt>::printTree(BSTNode<Objectt> * t) const{
    
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
BinarySearchTree<Objectt>::BinarySearchTree(const BinarySearchTree<Objectt> & rhs): root( NULL ), NULLITEM( rhs.NULLITEM)
{
    *this = rhs;
}


template <class Objectt>
BSTNode<Objectt> * BinarySearchTree<Objectt>:: clone( BSTNode<Objectt> * t ) const{
    
    if (t == NULL )
        return NULL;
    else
    {
        BSTNode<Objectt> temp = new BSTNode<Objectt> (t->element);
        for(int i=0; i < t->info.size(); i++){
            
            temp->info.push_back(t->info[i]);
        }
        temp->left = clone(t->left);
        temp->right = clone(t->right);
        return temp;
    }
}








