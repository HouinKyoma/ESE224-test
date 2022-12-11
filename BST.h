#pragma once
template <typename Comparable>
class BSTNode
{   public:
    BSTNode *left;
    BSTNode *right;
    Comparable data;
    BSTNode()
    {
        left = nullptr;
        right = nullptr;
    }
    BSTNode(const Comparable& x){
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
    BST(){
        root = nullptr;
    };
    ~BST(){};
    void insert(const Comparable &x);
    void remove(const Comparable &x);
    const Comparable & findMin() const;
    const Comparable & findMax() const;

private:
    void insert(const Comparable &x, BSTNode<Comparable>*&t) const;
    void remove(const Comparable &x, BSTNode<Comparable>*&t) const;
    BSTNode<Comparable> * findMin( BSTNode<Comparable> *t) const;
    BSTNode<Comparable> * findMax( BSTNode<Comparable> *t) const;
};

