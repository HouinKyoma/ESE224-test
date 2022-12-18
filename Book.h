#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<list>
class User;
using namespace std;
class Reader;
class BookCopy;
class Book{
    private:
        string ISBN;
        string title;
        string author;
        string category;
        string main_key = ISBN;
        int favor;//we assume favorite count will not be saved and read from txt files
        list<Reader> readers;//list of reservers
        vector<BookCopy> copyList;
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
        void setKey() {main_key = ISBN;}

        //--------------------operators---------------------------
        bool operator<(const Book& book2)const;
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
       
        //-------------------class methods----------------------
        void favorCount(){favor++;};
        void addReaderList(Reader& r){
            readers.push_back(r);
        }
        void removeReaderList(Reader& r);
        Reader popReaderList(); 
        int sizeReaderList(){
            return readers.size();
        }

        std::string toString(); 
        Book(){
            favor = 0;
            readers = list<Reader>();
            copyList = vector<BookCopy>();
        };
        /*
        Book(const Book& book){
            ISBN = book.getISBN();
            title = book.getTitle();
            author = book.getAuthor();
            category = book.getCategory();
            main_key = book.getKey();
            favor = book.favor;
            readers = book.readers;
            copyList = book.copyList;
        }*/
        ~Book(){};
        int sizeCopyList(){return copyList.size();}
        void removeCopy(int id);
        void addCopy(BookCopy& c);
    

        
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
        static int IDassign;
        static time_t startTime;
    //-----------------------constructors---------------
        BookCopy(){
            readerName = "";
            reserverName = "";
        };
        BookCopy(string isbn_){
            ID = IDassign++;
            readerName = "";
            reserverName = "";
            isbn = isbn_;
            
        }
        /*BookCopy(const BookCopy& copy){
            ID = copy.getID();
            readerName = copy.getReaderName();
            reserverName = copy.getReserverName();
            isbn = copy.getISBN();
            startDate = copy.getStartDate();
            reserveDate = copy.getReserveDate();
            expDate = copy.getExpDate();
            main_key = copy.getKey();
            book = copy.getBook();

        }*/
        ~BookCopy(){};
    //---------------------operators--------------------
        //bool operator<(const BookCopy& book2)const;
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
            IDassign++;
            rhs.setISBN(ISBN);//we are only getting ISBN here? additional work will have to be done to set the Book member with according isbn
            return is;
        }
        
        friend bool operator<(const BookCopy& book1,const BookCopy& book2);
	    friend bool operator>(const BookCopy& book1,const BookCopy& book2);
	    friend bool operator<=(const BookCopy& book1, const BookCopy& book2);
	    friend bool operator>=(const BookCopy& book1, const BookCopy& book2);
	    friend bool operator==(const BookCopy& book1, const BookCopy& book2);


        //--------getter/setters-------------------------

        Book getBook() const { return book; }
        void setBook(const Book &book_) { book = book_; }
        string getISBN() const{return isbn;}
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
        void setKey(){main_key = to_string(ID);}



        //---------------------class methods--------------------
        std::string toString();

        static int partition(vector<BookCopy>& array, int low, int high);

        static void quickSort(vector<BookCopy>& array, int low, int high);
        static vector<BookCopy> transformVec(vector<BookCopy*>& array);
       
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