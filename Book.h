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

};
class BookCopy{

};
class User{
    private:
    string password;
    string username;
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
    void addUser();
    void addBook();
    void deleteUser(); 
    void deleteBook();
    void searchUser();
};
template<class T>
class DataHolder{
    public:
        int main_key = T.main_key;
};
