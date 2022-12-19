#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <list>
#include "Book.h"
#include "BST.h"

using namespace std;
class BookCopy;
class Book;
class User
{
private:
    int type;
    string password;
    string username;
    string main_key = username;

public:
    //-----------------------setter and getters------------------------------------
    string getKey() const { return main_key; }
    void setKey() { main_key = username; }
    string getPassword() const { return password; }
    void setPassword(const string &password_) { password = password_; }
    string getUsername() const { return username; }
    void setUsername(const string &username_)
    {
        username = username_;
        main_key = username;
    }
    void setType(int i) { type = i; }

    //------------------operators---------------------------------------------------
    friend std::istream &operator>>(std::istream &is, User &rhs)
    {
        string name, password;
        is >> name >> password;
        rhs.setPassword(password);
        rhs.setUsername(name);
        rhs.setKey();
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, User &rhs)
    {
        os << rhs.getType() << " " << rhs.getUsername() << " " << rhs.getPassword() << endl;
        return os;
    }
    bool operator<(const User &user2) const;

    //--------------------Constructors and virtual functions--------------------------
    User(){};
    virtual ~User(){};
    virtual int getType() { return NULL; };

    //------------------------other methods---------------------------
    std::string toString();
};
class Reader : public virtual User
{
private:
    vector<BookCopy> borrowedList;
    vector<Book> reservedList;
    int penalty;

protected:
    int MAX_COPIES;
    int MAX_BORROW_PERIOD;

public:
    virtual void setMax_Copies(){};
    virtual void setMax_Period(){};
    void borrowBook(int id, BST<BookCopy *> &lib);
    void returnBook(int id, BST<BookCopy *> &lib);
    void renewBook(int id, BST<BookCopy *> &lib);
    void reserveBook(std::string isbn, BST<Book *> &lib);
    void cancelReserve(std::string isbn, BST<Book *> &lib);
    vector<BookCopy> searchBook(vector<string> &searchArgs, vector<BookCopy> &list);
    bool canBorrow() const;
    void clearReserve();
    int numBorrowed();
    vector<Book> getReservedList() { return reservedList; } // this only returns copy, since it will only be called for printing purposes
    vector<BookCopy> getBorrowedList() { return borrowedList; }
};
class Student : public virtual Reader
{
public:
    Student()
    {
        setMax_Copies();
        setMax_Period();
    };
    ~Student(){};
    void setMax_Copies() { MAX_COPIES = 5; };
    void setMax_Period() { MAX_BORROW_PERIOD = 10; };
    friend std::istream &operator>>(std::istream &is, Student &rhs)
    {
        string name, password;
        is >> name >> password;
        rhs.setPassword(password);
        rhs.setUsername(name);
        return is;
    }
    int getType() { return 0; }
};
class Teacher : public virtual Reader
{
public:
    Teacher()
    {
        setMax_Period();
        setMax_Copies();
    };
    ~Teacher(){};
    void setMax_Copies() { MAX_COPIES = 10; };
    void setMax_Period() { MAX_BORROW_PERIOD = 20; };
    int getType() { return 1; }
    void testFunction()
    {
    std:;
        cout << "This is a teacher" << endl;
    }
    friend std::istream &operator>>(std::istream &is, Teacher &rhs)
    {
        string name, password;
        is >> name >> password;
        rhs.setPassword(password);
        rhs.setUsername(name);
        return is;
    }
};
class Librarian : public virtual User
{
    // ALL subject to change
public:
    Librarian(){};
    ~Librarian(){};
    void addUser(BST<User *> &list);
    void addBook(BST<Book *> &lib, BST<BookCopy *> &copys);
    void deleteUser(std::string name, BST<User *> &list);
    void deleteBook(int id, BST<Book *> &lib, BST<BookCopy *> &copys);
    void searchUser(BST<User *> &list);
    int getType() { return 2; };
    friend std::istream &operator>>(std::istream &is, Librarian &rhs)
    {
        string name, password;
        is >> name >> password;
        rhs.setPassword(password);
        rhs.setUsername(name);
        return is;
    };
};
