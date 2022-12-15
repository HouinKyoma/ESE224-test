#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<list>
#include"Book.h"

using namespace std;
class BookCopy;
class User{
    private:
    int type;
    string password;
    string username;
    string main_key = username;
    public:
    //-----------------------setter and getters------------------------------------
    string getKey() const{return main_key;}
    void setKey(){main_key = username;}
    string getPassword() const { return password; }
    void setPassword(const string &password_) { password = password_; }
    string getUsername() const { return username; }
    void setUsername(const string &username_) { username = username_;main_key = username; }



    //------------------operators---------------------------------------------------
    friend std::istream& operator>>(std::istream& is, User& rhs){
        string name, password;
        is>>name>>password;
        rhs.setPassword(password);
        rhs.setUsername(name);
        rhs.setKey(); 
        return is;
    }   
    friend std::ostream& operator<<(std::ostream& os, User& rhs){
        os<<rhs.getType()<<" "<<rhs.getUsername()<<" "<<rhs.getPassword()<<endl;
        
    }
    bool operator<(const User& user2)const;


    //--------------------Constructors and virtual functions--------------------------
    User(){};
    virtual ~User(){};
    virtual int getType(){};

};
class Reader:public virtual User{
    private:
    int MAX_COPIES;
    int MAX_BORROW_PERIOD;
    vector<BookCopy> borrowedList;
    int penalty;
    public:
    virtual void setMax_Copies(int n){};
    virtual void setMax_Period(int n){};

    
};
class Student:public virtual Reader{
    public:
    Student(){};
    ~Student(){};
    void setMax_Copies(int n){};
    void setMax_Period(int n){};
    friend std::istream& operator>>(std::istream& is, Student& rhs){
        string name, password;
        is>>name>>password;
        rhs.setPassword(password);
        rhs.setUsername(name);
        return is;
    }
    int getType(){return 0;}

};
class Teacher:public virtual Reader{
    public:
    Teacher(){};
    ~Teacher(){};
    void setMax_Copies(int n){};
    void setMax_Period(int n){std::cout<<"teacher"<<endl;};
    int getType(){return 1;}
    void testFunction(){std:;cout<<"This is a teacher"<<endl;}
    friend std::istream& operator>>(std::istream& is, Teacher& rhs){
        string name, password;
        is>>name>>password;
        rhs.setPassword(password);
        rhs.setUsername(name);
        return is;
    }
    
};
class Librarian:public virtual User{
    //ALL subject to change
    public:
    Librarian(){};
    ~Librarian(){};
    void addUser();
    void addBook();
    void deleteUser(); 
    void deleteBook();
    void searchUser();
    int getType(){return 2;};
    friend std::istream& operator>>(std::istream& is, Librarian& rhs){
        string name, password;
        is>>name>>password;
        rhs.setPassword(password);
        rhs.setUsername(name);
        return is;
    }
};

