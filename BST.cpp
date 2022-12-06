#include"BST.h"


template<typename Comparable>
void BST<Comparable>::insert(const Comparable &x) {
    
}
template <typename Comparable>
void BST<Comparable>::remove(const Comparable &x) {
    
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
void BST<Comparable>::insert(const Comparable &x, BSTNode<Comparable>*&t) const {
    if( t == nullptr){
        t = new BSTNode(x);

    }
    else if(x < t->data){
        insert(x, t->left);
    }
    else if(x > t->data){
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
        BSTNode* oldNode = t;
        t = (t->left != nullptr) ? t->left:t->right;
        delete oldNode;
   }
}


