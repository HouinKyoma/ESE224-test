#include"BST.h"


template<typename Comparable>
void BST<Comparable>::insert(const Comparable &x) {
   insert(x,root); 
}
template <typename Comparable>
void BST<Comparable>::remove(const Comparable &x) {
     remove(x,root);
}
/**
 * @brief 
 * internal method for recursion
 * 
 * @tparam Comparable 
 * @param x the item to insert
 * @param t the node that is root of subtree
 * the method will set the new subtree root
 */
template <typename Comparable>
void BST<Comparable>::insert(const Comparable& x, BSTNode<Comparable>*& t) const {
    if( t == nullptr){
        t = new BSTNode<Comparable>(x);

    }
    else if(x < t->data){
        insert(x, t->left);
    }
    else if(t->data < x){
        insert(x, t->right);
    }
    else
        //duplicate do nothing
        ;
    
}
/**
 * @brief Internal recursion method for remove 
 * 
 * @tparam Comparable 
 * @param x the item to be removed
 * @param t is the root of the subtree
 * will set the new root of the subtree
 */
template <typename Comparable>
void BST<Comparable>::remove(const Comparable &x, BSTNode<Comparable> *&t) const {
   if(t == nullptr){
        return;
   } 
   if(x<t->data){
        remove(x, t->left);
   }
   else if(x > t->data){
        remove(x, t->right);
   }
   else if(t->left!=nullptr && t->right!=nullptr){
        t->data = findMin(t->right)->data;
        remove(t->data, t->right);
   }
   else{
        BSTNode<Comparable> * oldNode = t;
        t = (t->left != nullptr) ? t->left:t->right;
        delete oldNode;
   }
}



template <typename Comparable>
BSTNode<Comparable> * BST<Comparable>::  findMin( BSTNode<Comparable> *t) const{
     if (t!=nullptr){
          while(t->left !=nullptr){
               t = t->left;
          }
          return t;
     }
}

template <typename Comparable>
const Comparable& BST<Comparable>:: findMin() const{
     return findMin(root);
}

/**
 * @brief 
 * Internal method, for recursively find
 * @tparam Comparable 
 * @param x item to search for
 * @param t root of the subtree
 * @return true 
 * @return false 
 */
template <typename Comparable>
bool BST<Comparable>::contains(const Comparable&x, BSTNode<Comparable> *t)const{
     if(t == nullptr){
          return false;
     }
     else if(t->data<x){
          return contains(x,t->left);
     }
     else if(x<t->data){
          return contains(x,t->right);
     }
     else 
          return true;


}

template <typename Comparable>
bool BST<Comparable>::contains(const Comparable&x)const{
     return contains(x, root);

}

template <typename Comparable>
Comparable* BST<Comparable>::search(const Comparable& x)const{
     return search(x,root);
}
template <typename Comparable>
Comparable* BST<Comparable>::search(const Comparable&x, BSTNode<Comparable> *t)const{
     if(t == nullptr){
          return nullptr;
     }
     else if(t->data<x){
          return search(x,t->left);
     }
     else if(x<t->data){
          return search(x,t->right);
     }
     else {
          Comparable* ret = &(t->data);
          return ret;
     }

}

template <typename Comparable>
Comparable* BST<Comparable>::search(const std::string& key)const{
     return search(key, root);
}

template <typename Comparable>
Comparable* BST<Comparable>::search(const std::string& key, BSTNode<Comparable> *t)const{
     if(t == nullptr){
          return nullptr;
     }
     else if(t->data->getKey()<key){
          return search(key,t->left);
     }
     else if(key<t->data->getKey()){
          return search(key,t->right);
     }
     else {
          Comparable* ret = &(t->data);
          return ret;
     }




}