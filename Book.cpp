#include"Book.h"
#include"User.h"
bool BookCopy::operator<(const BookCopy& book2)const{
    return this->ID<book2.getID();
}

bool Book:: operator<(const Book& book2)const{
    return stol(this->getISBN())<stol(book2.getISBN());
    
}
