#include"Book.h"
#include"User.h"
#include<algorithm>
bool BookCopy::operator<(const BookCopy& book2)const{
    return this->ID<book2.getID();
}

std::string BookCopy::toString(){
    std::string res = this->isbn + " " +to_string(this->ID);
    return res;


}





bool Book:: operator<(const Book& book2)const{
    std::string s1 = this->getISBN();
    std::string s2 = book2.getISBN();
    return std::lexicographical_compare(s1.begin(),s1.end(),s2.begin(),s2.end());
    //return this->getISBN()<book2.getISBN();
    //return stol(this->getISBN())<stol(book2.getISBN());
    
}
std::string Book::toString(){
    std::string res = this->ISBN+" "+this->title+" "+this->author+" "+this->category;
    return res;
}