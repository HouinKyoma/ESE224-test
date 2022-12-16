#include"BST.h"
#include"Book.h"
#include"User.h"
#include<iostream>
#include<algorithm>
template<typename Comparable>
bool lessThan(const Comparable& x, const Comparable&y){
     
     std::string s1 = x->getKey();
    std::string s2 = y->getKey();
    return std::lexicographical_compare(s1.begin(),s1.end(),s2.begin(),s2.end());



}

template<typename Comparable>
std::string toString(const Comparable&x){
     return x->toString();
}



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
   
     else if(lessThan(x,t->data)){
          //cout<<"x less than data"<<endl;
          insert(x,t->left);
     }
     else if(lessThan(t->data,x)){
          insert(x,t->right);
     }
    
    /*else if(x < t->data){
        insert(x, t->left);
    }
    else if(t->data < x){
        insert(x, t->right);
    }*/
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
   if(typeid(x)==typeid(User)||typeid(x)==typeid(Book)||typeid(x)==typeid(BookCopy)){
     std::cout<<"is defined type"<<std::endl;
   }
   if(lessThan(x,t->data)){
        remove(x, t->left);
   }
   else if(lessThan(t->data,x)){
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
      else if(lessThan(x,t->data)){
          //cout<<"x less than data"<<endl;
          return contains(x,t->left);
     }
     else if(lessThan(t->data,x)){
          return contains(x,t->right);
     }
     /*
     else if(t->data<x){
          return contains(x,t->left);
     }
     else if(x<t->data){
          return contains(x,t->right);
     }
     */
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
     else if(lessThan(x,t->data)){
          return search(x,t->left);
     }
     else if(lessThan(t->data,x)){
          return search(x,t->right);
     }
     else {
          Comparable* ret = &(t->data);
          return ret;
     }

}
/**
 * @brief using a recursive call, find the object in the BST, if not exist, the return is nullptr 
 * 
 * @tparam Comparable 
 * @param key search using the main_key of objects 
 * @return Comparable* the return of the function is a pointer to an object
 */
template <typename Comparable>
Comparable* BST<Comparable>::search(const std::string& key)const{
     return search(key, root);
}

template <typename Comparable>
Comparable* BST<Comparable>::search(const std::string& key, BSTNode<Comparable> *t)const{
     std::string s1,s2;
     bool S1lessthanS2, S2lessthanS1;
     if(t!=nullptr) {
          s2 = t->data->getKey();
          s1 = key;
          S1lessthanS2 = std::lexicographical_compare(s1.begin(),s1.end(),s2.begin(),s2.end());
          S2lessthanS1 = std::lexicographical_compare(s2.begin(),s2.end(),s1.begin(),s1.end());}
     if(t == nullptr){
          return nullptr;
     }
     else if(S1lessthanS2){
          return search(key,t->left);
     }
     else if(S2lessthanS1){
          return search(key,t->right);
     }
     else {
          Comparable* ret = &(t->data);
          return ret;
     }




}



template <typename Comparable>
void BST<Comparable>:: printCurrentLevel(BSTNode<Comparable>*t, int level,std::ofstream& os){
   if(t==nullptr){
     return;
   } 
   if(level == 1){
     os<<toString(t->data)<<std::endl;
   }
   else if(level > 1){
     printCurrentLevel(t->left, level-1,os);
     printCurrentLevel(t->right, level-1,os);
   }
}



template <typename Comparable>
int BST<Comparable>:: height(const BSTNode<Comparable>* t)const{
     if(t == nullptr){
          return 0;
     }
     else{
          int lheight = height(t->left);
        int rheight = height(t->right);
 
        /* use the larger one */
        if (lheight > rheight) {
            return (lheight + 1);
        }
        else {
            return (rheight + 1);
        }
     }
}

template <typename Comparable>
void BST<Comparable>:: printLevelOrder(std::ofstream& os){
     int h = height(root);
    int i;
    for (i = 1; i <= h; i++){
        printCurrentLevel(root, i,os);
     }
}

