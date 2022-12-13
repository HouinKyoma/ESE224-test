#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<list>
class User;
using namespace std;
class Book{
    private:
        string ISBN;
        string title;
        string author;
        string category;
        string main_key = ISBN;
        int favor;//we assume favorite count will not be saved and read from txt files
        list<User> readers;
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

        string getKey() const{return main_key;}
        //--------------------operators---------------------------
        bool operator<(const Book& book2);

        //-------------------class methods----------------------
        void favorCount(){favor++;};
        
        Book(){
            favor = 0;
        };
        ~Book(){};

        friend std::ostream &operator<<(std::ostream &os, const Book &rhs) {
            os << "ISBN: " << rhs.ISBN
               << " title: " << rhs.title
               << " author: " << rhs.author
               << " category: " << rhs.category;
            return os;
        }
        friend std::istream &operator>>(std::istream &is,  Book &rhs){
            string ISBN;
            string title;
            string author;
            string category;
            is>>ISBN>>title>>author>>category;
            rhs.setISBN(ISBN);
            rhs.setTitle(title);
            rhs.setAuthor(author);
            rhs.setCategory(category);
            return is;
        }
        
};
class BookCopy{
    private:
        Book book;
        int ID;
        string isbn;//for temp input<< purpose
        string readerName;
        string reserverName;
        string main_key = to_string(ID);
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
        friend std::ostream &operator<<(std::ostream &os, const BookCopy &rhs) {
            os << "book: " << rhs.book
               << " ID: " << rhs.ID
               << " readerName: " << rhs.readerName
               << " reserverName: " << rhs.reserverName
               << " reserveDate: " << rhs.reserveDate
               << " startDate: " << rhs.startDate
               << " expDate: " << rhs.expDate;
            return os;
        }
        friend std::istream& operator>>(std::istream &is,  BookCopy &rhs){
            string ISBN;
            int id;
            is >> ISBN >> id;
            rhs.setID(id);
            rhs.setISBN(ISBN);//we are only getting ISBN here? additional work will have to be done to set the Book member with according isbn
            return is;
        }
        



        //--------getter/setters-------------------------

        Book getBook() const { return book; }
        void setBook(const Book &book_) { book = book_; }
        void setISBN(const string &isbn_) {isbn = isbn_; }
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

        string getKey()const {return main_key;}
       
    

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