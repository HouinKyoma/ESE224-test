#include"Book.h"
#include"User.h"
#include<algorithm>
/*
bool BookCopy::operator<(const BookCopy& book2)const{
    return this->ID<book2.getID();
}
*/

std::string BookCopy::toString(){
    std::string res = this->isbn + " " +to_string(this->ID);
    return res;


}

bool operator<(const BookCopy& book1,const BookCopy& book2){
    bool book1Avail, book2Avail;//true when bookcopy is available == no reserver and borrower
    book1Avail = (book1.getReaderName()=="")&&(book1.getReserverName()=="");
    book2Avail = (book2.getReaderName()=="")&&(book2.getReserverName()=="");
	if(book1Avail<book2Avail){
        //return treu when book1 is not available and book2 is available
		return true;//1 when the book1 is borrowed
	}
	time_t currentTime;
	time(&currentTime);
    int currentDay = difftime(currentTime,BookCopy::startTime)/5;
	if((book1.getExpDate()-currentDay)>(book2.getExpDate()-currentDay)){
		return true;//2 rank by which book is closer to expiration date
	}
	if(book1.getBook().getTitle().compare(book2.getBook().getTitle())<0){
		return false;
	}
	if(book1.getBook().getAuthor().compare(book2.getBook().getAuthor())<0){
		return false;
	}
	if(book1.getISBN().compare(book2.getISBN())<0){
		return false;
	}
	if(book1.getID()<book2.getID()){
		return false;
	}
	else return false;

}
bool operator>(const BookCopy& book1,const BookCopy& book2) {
	return !(book1<=book2);
}

bool operator<=(const BookCopy& book1, const BookCopy& book2) {
	return ((book1<book2)||(book1==book2));
}

bool operator>=(const BookCopy& book1, const BookCopy& book2) {
	return !(book1<book2);
}


bool operator==(const BookCopy& book1,const BookCopy& book2) {
	
	return (book1.getBook().getISBN().compare(book2.getBook().getISBN())==0&&
	book1.getBook().getTitle() == book2.getBook().getTitle()&&
	book1.getBook().getAuthor() == book2.getBook().getAuthor()&&
	book1.getBook().getCategory() == book2.getBook().getCategory());
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

int BookCopy::partition(vector<BookCopy>& array, int low, int high) {
	// TODO
    //std::vector<BookCopy*>::iterator it = array.begin();
    int i = low;
    int j = high -2;
    BookCopy pivot = array[high];
    do{
    while(array[i]<= pivot && i < high){
        i++;
    }
    while(array[j]>= pivot && j > low){
        j--;
    }
    if(i<j){
        BookCopy tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
    }
    while(i<j);
    if(array[i] > pivot){
        BookCopy tmp = array[i];
        array[i] = array[high];
        array[high] = tmp;
    }
    return i;
}


/*
int BookCopy::partition(vector<BookCopy*>& array, int low, int high) {
	// TODO
    //std::vector<BookCopy*>::iterator it = array.begin();
    int i = low;
    int j = high -2;
    BookCopy* pivot = array[high];
    do{
    while(array[i]<= pivot && i < high){
        i++;
    }
    while(array[j]>= pivot && j > low){
        j--;
    }
    if(i<j){
        BookCopy* tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
    }
    while(i<j);
    if(array[i] > pivot){
        BookCopy* tmp = array[i];
        array[i] = array[high];
        array[high] = tmp;
    }
    return i;
}

*/
void BookCopy::quickSort(vector<BookCopy>& array, int low, int high) {

    if (low < high) {

        // find the pivot element and move elements such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on righ of pivot
        int pi = partition(array, low, high);

        // recursive call on the left of pivot
        quickSort(array, low, pi - 0);

        // recursive call on the right of pivot
        quickSort(array, pi + 0, high);
    }
}
vector<BookCopy> BookCopy:: transformVec(vector<BookCopy*>& array){
    vector<BookCopy> ret(array.size());
    transform(array.begin(),array.end(),ret.begin(),[](BookCopy* copy){return *copy;});
    return ret;
}
//std::vector<T> another_bar(bar.size());
//std::transform(std::begin(bar),std::end(bar),std::begin(another_bar),[](T* item){return *T;});
