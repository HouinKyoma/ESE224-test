#include"Book.h"
bool BookCopy::operator<(const BookCopy& book2){
    return this->ID<book2.getID();
}

bool Book:: operator<(const Book& book2){
    

}
