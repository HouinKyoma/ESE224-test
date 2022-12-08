#pragma once
template <typename Comparable>
class BSTNode
{
    BSTNode *left;
    BSTNode *right;
    Comparable data;
    BSTNode()
    {
        left = nullptr;
        right = nullptr;
    }
    BSTNode(Comparable& x){
        data = x;
        left = nullptr;
        right = nullptr;
    }
    
};
template <typename Comparable>
class BST
{
    BSTNode<Comparable> *root;

public:
    BST();
    ~BST();
    void insert(const Comparable &x);
    void remove(const Comparable &x);

private:
    void insert(const Comparable &x, BSTNode<Comparable>*&t) const;
    void remove(const Comparable &x, BSTNode<Comparable>*&t) const;
};

