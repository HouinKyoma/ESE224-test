#include"Book.h"
#include"User.h"
#include<algorithm>
bool BookCopy::operator<(const BookCopy& book2)const{
    return this->ID<book2.getID();
}

bool Book:: operator<(const Book& book2)const{
    std::string s1 = this->getISBN();
    std::string s2 = book2.getISBN();
    return std::lexicographical_compare(s1.begin(),s1.end(),s2.begin(),s2.end());
    //return this->getISBN()<book2.getISBN();
    //return stol(this->getISBN())<stol(book2.getISBN());
    
}
