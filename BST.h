#pragma once
#include<vector>
#include<string>
#include<typeinfo>
template <typename Comparable>
class Data{
    private:
    Comparable data;
    std::string key;
    public:
    std::string getKey(){return key;};
    void setKey(std::string key_){key = key_;};



};
template <typename Comparable>
class BSTNode
{   public:
    BSTNode *left;
    BSTNode *right;
    Comparable data;
    //Data<Comparable> data;
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
    bool contains(const Comparable &x) const;
    Comparable* search(const Comparable &x) const;
    Comparable* search(const std::string &key) const;
    Comparable* searchBook(std::vector<std::string>& searchArgs);\
    int height(const BSTNode<Comparable>* t)const;
    void printLevelOrder(std::ofstream& os);
    

private:
    void insert(const Comparable &x, BSTNode<Comparable>*&t) const;
    void remove(const Comparable &x, BSTNode<Comparable>*&t) const;
    BSTNode<Comparable> * findMin( BSTNode<Comparable> *t) const;
    BSTNode<Comparable> * findMax( BSTNode<Comparable> *t) const;
    bool contains(const Comparable&x, BSTNode<Comparable> *t)const;
    Comparable* search(const Comparable&x, BSTNode<Comparable> *t)const;
    Comparable* search(const std::string& key, BSTNode<Comparable> *t)const;
    void printCurrentLevel(BSTNode<Comparable>*t, int level,std::ofstream& os);
};

