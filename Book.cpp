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

void Book::removeCopy(int id){
    int index = 0;
    for(auto i:copyList){
        if(i.getID()==id){
            copyList.erase(copyList.begin()+index);
        }
        index++;
    }
}
void Book::addCopy(BookCopy& c){
    copyList.push_back(c);
}
Reader Book::popReaderList(){
//Does it return copy or the original object?
            Reader ret = readers.front();
            readers.pop_front();
            return ret;
            
}
void Book::removeReaderList(Reader& r){
            std::list<Reader>::iterator it = readers.begin();
            for(auto i:readers){
                if(i.getUsername()==r.getUsername()){
                    readers.erase(it);
                }
                ++it;
            }
}