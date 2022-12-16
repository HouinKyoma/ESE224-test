#include"User.h"
#include"BST.h"
#include<algorithm>
#include<ctime>
bool User::operator<(const User& user2)const{
    std::string s1 = this->getUsername();
    std::string s2 = user2.getUsername();

    return std::lexicographical_compare(s1.begin(),s1.end(),s2.begin(),s2.end());
    
    //return username<user2.getUsername();
}
std::string User::toString(){
    std::string res;
    if(this->getUsername()!=""){
        res = to_string(this->getType())+" "+this->getUsername()+" "+this->getPassword()+" ";}
    return res;
}

/**
 * @brief implements the borrow function of the system, change the readers list, start date, reader name of the BookCopy objects found
 * @precondtion:  BST is initialized, and copy with the said id exists, the reader have no overdue book
 * @postcondition: BST's node's member is changed, a bookcopy is added to reader's borrowed list.
 * @param id id of the book reader wants to borrow
 * @param lib the BST that stores all the copy of the books 
 */
void Reader::borrowBook(int id, BST<BookCopy*>& lib){
    BookCopy** bcptr = lib.search(to_string(id));
    if(bcptr==nullptr){
        throw std::invalid_argument("the copy of the id does not exist in library.");
    }



    BookCopy borrowed = **(bcptr);

    //check if already borrowed

    if(borrowed.getReaderName()!=""){
        throw std::invalid_argument("the copy is already been lent to other readers");
    }
    //check if the reader can borrow
    if(!(this->canBorrow())){
        std::cout<<"can not borrow book due to overdue book or over maximum allowed copies"<<endl;
        return;
    }
    //check if there is reserver
    if(borrowed.getReserverName()!=""){
        throw std::invalid_argument("the copy is already been reserved to other readers");
    }
    
    time_t currentTime;
    time(&currentTime);
    borrowed.setStartDate((currentTime-BookCopy::startTime)/5);//this gives the day that the book was borrowed, day start at day 0, 5 sec = 1 day
    borrowed.setExpDate(((currentTime-BookCopy::startTime)/5)+MAX_BORROW_PERIOD);
    this->borrowedList.push_back(borrowed);
    //borrowed.getBook().addReaderList(*this);//add to the Book class reader list
    borrowed.setReaderName(this->getUsername());//add to the BookCopy readerName

    cout<<"You have successfully borrowed the book "<<borrowed.getBook().getTitle()<<" ."<<endl;

}
/**
 * @brief a function to test if a reader can still borrow book. A reader can not borrow book if:
 * 1.have overdue copy
 * 2.have more than maximum 
 * 
 * @return true 
 * @return false 
 */

bool Reader::canBorrow()const{
    time_t currentTime;
    time(&currentTime);
    int currentDay = difftime(currentTime,BookCopy::startTime)/5;
    if(borrowedList.empty()){return true;}
    //check if more than maximum
    if(borrowedList.size()==MAX_COPIES){return false;}
    for(auto i:borrowedList){
        if(i.getExpDate()<currentDay){
            return false;
        }
    }


}

/**
 * @brief return through the id, 
 * @postcondition: the copy becomes available again, readername updated 
 * 
 * @param id 
 */
void Reader::returnBook(int id,BST<BookCopy*>& lib){
    time_t currentTime;
    time(&currentTime);
    int currentDay = difftime(currentTime,BookCopy::startTime)/5;
    BookCopy** bcptr = lib.search(to_string(id));
    if(bcptr==nullptr){
        throw std::invalid_argument("the copy of the id does not exist in library.");
    }
    BookCopy borrowed = **(bcptr);
    //check if overdue
    if(borrowed.getExpDate()<currentDay){
        //TODO
        //add penalty
        cout<<"this returned book is overdue!"<<endl;
    }
    
    borrowed.setReaderName(""); //set back the reader name of the copy to default;

    //remove the copy from reader's borrowed list.
    std::vector<BookCopy>::iterator it = borrowedList.begin();
    for(auto c:this->borrowedList){
        if(c.getID()==id){
            borrowedList.erase(it);

        }
        it++;
    }
    //check the reserver list.
    if(borrowed.getBook().sizeReaderList()!=0){
        Reader r = borrowed.getBook().popReaderList();
        borrowed.setReserverName(r.getUsername());
        borrowed.setReserveDate(currentDay);
    }

    //ask if user like the book
    std::cout<<"Do you like the book you just returned?(y/n)"<<endl;
    char c;
    std::cin>>c;
    if(c=='Y'||c=='y'){borrowed.getBook().favorCount();}
    


}

void Reader::renewBook(int id,BST<BookCopy*>& lib){
    time_t currentTime;
    time(&currentTime);
    int currentDay = difftime(currentTime,BookCopy::startTime)/5;
    BookCopy** bcptr = lib.search(to_string(id));
    if(bcptr==nullptr){
        throw std::invalid_argument("the copy of the id does not exist in library.");
    }
    BookCopy borrowed = **(bcptr);
    if(borrowed.getBook().sizeReaderList()!=0){
        cout<<"This book has been reserved by others, can not extend its duration"<<endl;
        return;
    }
    borrowed.setExpDate(borrowed.getExpDate()+this->MAX_BORROW_PERIOD);
}

void Reader::reserveBook(std::string isbn,BST<Book*>& lib){
    Book** bpptr = lib.search(isbn);
    Book reserved = **(bpptr);
    reserved.addReaderList(*this);

}
void Reader::cancelReserve(std::string isbn, BST<Book*>& lib){
    Book** bpptr = lib.search(isbn);
    Book reserved = **(bpptr);
    reserved.removeReaderList(*this);
}