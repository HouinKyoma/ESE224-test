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
        int favor;

    public:
        //----------------setter/getters--------------------
        string getISBN() const { return ISBN; }
        void setISBN(const string &iSBN) { ISBN = iSBN; }

        string getTitle() const { return title; }
        void setTitle(const string &title_) { title = title_; }

        string getAuthor() const { return author; }
        void setAuthor(const string &author_) { author = author_; }

        string getCategory() const { return category; }
        void setCategory(const string &category_) { category = category_; }
        //--------------------operators---------------------------
        bool operator<(const Book& book2);

        //-------------------class methods----------------------
        void favorCount(){favor++;};

        Book(){
            favor = 0;
        };
        ~Book(){};
        
};
class BookCopy{
    private:
        Book book;
        int ID;
        string readerName;
        string reserverName;
        int reserveDate;
        int startDate;
        int expDate;
    public:
    //-----------------------constructors---------------
        BookCopy(){

        };
        ~BookCopy(){};
    //---------------------operators--------------------
        bool operator<(const BookCopy& book2);




        //--------getter/setters-------------------------

        Book getBook() const { return book; }
        void setBook(const Book &book_) { book = book_; }

        int getID() const { return ID; }
        void setID(int iD) { ID = iD; }

        string getReaderName() const { return readerName; }
        void setReaderName(const string &readerName_) { readerName = readerName_; }

        string getReserverName() const { return reserverName; }
        void setReserverName(const string &reserverName_) { reserverName = reserverName_; }

        int getReserveDate() const { return reserveDate; }
        void setReserveDate(int reserveDate_) { reserveDate = reserveDate_; }

        int getStartDate() const { return startDate; }
        void setStartDate(int startDate_) { startDate = startDate_; }

        int getExpDate() const { return expDate; }
        void setExpDate(int expDate_) { expDate = expDate_; }
        
    

};
class User{
    private:
    string password;
    string username;
    string main_key = username;
public:
    
    string getPassword() const { return password; }
    void setPassword(const string &password_) { password = password_; }
    string getUsername() const { return username; }
    void setUsername(const string &username_) { username = username_; }
    public:

};
class Reader:virtual User{
    private:
    int MAX_COPIES;
    int MAX_BORROW_PERIOD;
    vector<BookCopy> borrowedList;
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

/*

//----THIS class will be replaced by BST-----
template<class T>
class DataHolder{
    //book bookcopies users

    /*
        book: ISBN
        bookcopy: ID
        user: username
    
    
    
    public:
        int main_key = T.main_key;
        DataHolder search(T.main_key, BST& list);
        void addElement(DataHolder d, BST& list);
        void removeElement(int key, BST& list);
        DataHolder searchBook(vector<string> keys);

};
*/