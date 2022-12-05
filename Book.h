#pragma once
#include<string>
#include<vector>
#include<iostream>
using namespace std;
class Book{
    private:
        string ISBN;
        string title;
        string author;
        string category;
        string main_key = ISBN;
    public:


};
class BookCopy{

};
class User{
    private:
    string password;
    string username;
    string main_key = username;
    public:
    Book searchBook(vector<Book> bookList, int id);

};
class Reader:virtual User{
    private:
    int MAX_COPIES;
    int MAX_BORROW_PERIOD;
    vector<BookCopy> borroweList;
    int penalty;
    public:
    virtual void setMax_Copies(int n);
    virtual void setMax_Period(int n);

    
};
class Student:virtual Reader{
    public:
        void setMax_Copies(int n);
        void setMax_Period(int n);


};
class Teacher:virtual Reader{
    public:
        void setMax_Copies(int n);
        void setMax_Period(int n);



};
class Librarian:virtual User{
    //ALL subject to change
    public:
        void addUser();
        void addBook();
        void deleteUser(); 
        void deleteBook();
        void searchUser();
};
template<class T>
class DataHolder{
    //book bookcopies users

    /*
        book: ISBN
        bookcopy: ID
        user: username
    
    
    */
    public:
        int main_key = T.main_key;
        DataHolder search(T.main_key, BST& list);
        void addElement(DataHolder d, BST& list);
        void removeElement(int key, BST& list);
        DataHolder searchBook(vector<string> keys);

};
