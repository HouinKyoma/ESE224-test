#include"User.h"
#include"BST.h"
#include"BST.cpp"
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
    this->reservedList.push_back(reserved);

}
void Reader::cancelReserve(std::string isbn, BST<Book*>& lib){
    Book** bpptr = lib.search(isbn);
    Book reserved = **(bpptr);
    reserved.removeReaderList(*this);
}
/**
 * @brief this function must be used when delete a reader, iterate through the reserved list of reader, and remove the Book object from the vector, and linkedlist of Book class readerlist
 * 
 */
void Reader::clearReserve(){
    //
    std::vector<Book>::iterator it = reservedList.begin();
    for(auto i:reservedList){
        i.removeReaderList(*this);//remove the reader from the Book's reserver list
        this->reservedList.erase(it);
        it++;//
    }
}
int Reader::numBorrowed(){
    return borrowedList.size();
}



void Librarian::addUser(BST<User*>& list){
    //Prompt user
    string username;
    string password;
    int type;
    cout<<"Enter account type(0 = student, 1 = teacher, 2=librarian";
    cin>>type;
    cout<<endl;
    cout<<"Enter Username:";
    cin>>username;
    cout<<endl;
    cout<<"Enter Password:";
    cin>>password;
    switch (type)
    {
    case 0 :
        {Student* s = new Student();
        s->setUsername(username);
        s->setPassword(password);
        list.insert(s);
        break;}
    case 1:
        {Teacher* t = new Teacher();
        t->setUsername(username);
        t->setPassword(password);
        list.insert(t);
        break;}
    case 2:
        {Librarian* l = new Librarian();
        l->setUsername(username);
        l->setPassword(password);
        list.insert(l);
        break;
        }
    default:
        break;
    }
    

}

void Librarian:: addBook(BST<Book*>& lib,BST<BookCopy*>& copys){
        
        std::string title,author,category,isbn;
        cout <<"Adding book--Please enter prompted information"<<endl;

        cout << "Enter title: ";
		cin >> title;
        cout << "Enter author: ";
		cin >> author; 
		cout << "Enter category: ";
		cin >> category; 
		cout << "Enter ISBN: ";
		cin >> isbn;
        //search for book
        Book** bpptr = lib.search(isbn);
        //case when the book already exist;

        BookCopy* newCopy = new BookCopy(isbn);
        if(bpptr != nullptr){
            
            Book addedBook = **(bpptr);
            addedBook.addCopy(*newCopy);//add the book to the copy list;
            newCopy->setBook(addedBook);
            copys.insert(newCopy);
            std::cout<<"A new copy has been added to book "<<addedBook.getTitle()<<endl;
        }
        else{
            Book* newBook = new Book();
            newBook->setAuthor(author);
            newBook->setISBN(isbn);
            newBook->setCategory(category);
            newBook->setTitle(title);
            lib.insert(newBook);
            newCopy->setBook(*newBook);
            newBook->addCopy(*newCopy);
            copys.insert(newCopy);
            std::cout<<" The book with name "<<newBook->getTitle()<<" and a new copy is added to the library."<<endl;

        }
        //case when the book doesn't exist, first add a new Book to BST, then add a copy to copy BST, also do all the required member update 
}
void Librarian:: deleteUser(std::string name, BST<User*>& list){
    //check if the student have any copy left
    User** uptr = list.search(name);
    if(uptr==nullptr){std::cerr<<"the user with the name does not exist."<<std::endl;return;}
    Librarian* l =dynamic_cast<Librarian*>(*(uptr));
    Reader* t =dynamic_cast<Reader*>(*(uptr));
    if(l!=nullptr){
        //since not reader just remove
        list.remove(l);
        std::cout<<"The librarian "<<l->getUsername()<<" has been successfully delted."<<std::endl;
        return;
    }
    else if(t!=nullptr){
        if(t->numBorrowed()>0){
            std::cerr<<"The reader still have unreturned book, please delete after all books are returned"<<endl;
            return;
        }
        else{
            t->clearReserve();
            list.remove(t);
            std::cout<<"The reader "<<t->getUsername()<<" has been successfully deleted."<<std::endl;
            return;
        }
    }


    //remove all the reserved books
}
void Librarian:: deleteBook(int id, BST<Book*>& lib, BST<BookCopy*>& copys){
    BookCopy** cptr = copys.search(to_string(id));
    if(cptr == nullptr){std::cerr<<"the copy with the id does not exist!"<<std::endl;}
    BookCopy deleteCopy = **(cptr);
    deleteCopy.getBook().removeCopy(id); // remove the copy from its Book
    std::cout<<"BookCopy "<<deleteCopy.getID()<<" has been deleted from Copy list."<<std::endl;
    if(deleteCopy.getBook().sizeCopyList()==0){//if there is no copy left from that book
        //what should the behavior of the user who reserved the book be? this is sth unspecified in doc
        Book** deleteBook = lib.search(deleteCopy.getISBN());
        lib.remove(*(deleteBook));
        std::cout<<"Book "<< (**deleteBook).getTitle()<<" has been deleted from Book list because there is 0 copies left."<<std::endl;
    }
    copys.remove(*cptr);
}
void Librarian:: searchUser(){
    std::string username;
    std::cout<<"input username to search:"<<std::endl;
    std::cin>>username;
    //TODO copy the code from delete user, since shares the same structure
}