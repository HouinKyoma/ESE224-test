#pragma once
template<typename Comparable>
class BSTNode{
    BSTNode* left;
    BSTNode* right;
    Comparable data;
    BSTNode(){
        left = nullptr;
        right = nullptr;
    }

};
template<typename Comparable>
class BST{
    BSTNode* root; 
};
