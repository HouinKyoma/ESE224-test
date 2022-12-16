#include<iostream>
#include<fstream>
#include"BST.h"
#include"BST.cpp"
#include"Book.h"
#include"User.h"
using namespace std;
BST<User*> users;
BST<Book*> books;
BST<BookCopy*> copys;
/**
 * @brief function to read file into bst
 * To support polymorphism, a pointer to the object is used instead of object. 
 * 
 */
void scanFile(){
    int type;
	ifstream fin("student.txt");
	if (fin.fail()) {
		cerr << "Error opening student file.";
		exit(1);
	}

	while(true) {
		fin >> type;
		if (type == 0) {

            Student* student = new Student();
		    fin >> *(student);
            User* user = student;
            user->setKey();
            users.insert(user);
		}
		else if( type == 1) {

            Teacher* teacher= new Teacher();

			fin >> *(teacher);
            User* user = teacher;
            user->setKey();
            user->setType(2);
            users.insert(user);
        }
        else {

            Librarian* lib = new Librarian();
            fin>>*(lib);
            User* user = lib;
            user->setKey();
            users.insert(user);

        }

        if(fin.eof()){break;}
	} 



    ifstream fin2("book.txt");
	if (fin2.fail()) {
		cerr << "Error opening book file.";
		exit(1);
	}

	while(true){
        Book* book = new Book();
        fin2>>*(book);
        book->setKey();
        books.insert(book);
        if(fin2.eof()){ break;}
	} 
    
    ifstream fin3("copy.txt");
    if (fin3.fail()) {
		cerr << "Error opening copy file.";
		exit(1);
	}

	while (true)
    {
        /* code */
        BookCopy* copy = new BookCopy();
        fin3>>*(copy);

        string isbn = copy->getISBN();
        Book** bpptr = books.search(isbn);
        Book    b  = **(bpptr);
        copy->setBook(b);
        copy->setKey();

        copys.insert(copy);
        if(fin3.eof()){break;}
    }
    
        


};
void outputFile(){

    ofstream myfile;
    myfile.open("student2.txt");
    if (myfile.is_open())
  {
    users.printLevelOrder(myfile);
  }
  else cout << "Unable to open file";

    myfile.close();
  ofstream myfile2;
    myfile2.open("book2.txt");
    if (myfile2.is_open())
  {
    books.printLevelOrder(myfile2);
  }
  else cout << "Unable to open file";

    myfile2.close();
ofstream myfile3;
    myfile3.open("copy2.txt");
    if (myfile3.is_open())
  {
    copys.printLevelOrder(myfile3);
  }
  else cout << "Unable to open file";

    myfile3.close();




}


int main(){
    //Load from file
        //load into a BST
    
    //login
        //reader login
            //print reader menu
            //        


        //librarian login
            //print lib menu
                //request new book copy
                //delete existing copy
                //search users
                //add new users
                //delete old users



    //when ending, update the txt files 
    //testing code 
    /*BST<int> bst = BST<int>();
    bst.insert(1);
    bst.insert(3);
    bst.insert(10);
    bst.remove(1);
    bst.insert(0);
    bst.remove(3);
    int rest = *(bst.search(10));
    cout<<"search: "<<rest<<endl;
    cout<<bst.contains(10)<<endl;
    cout<<bst.contains(8);
    string s = "9781283329705";
    string s2 = "9781493938438	";
    long int isbn = stol(s);
    long int isbn2 = stol(s2);
    cout<<isbn;
    cout<<isbn2<<endl;
    cout<<(isbn<isbn2);*/
    //--------------------testing for file input ------------------
    users = BST<User*>();
    books = BST<Book*>();
    copys = BST<BookCopy*>();
    scanFile();
    User** u1 = users.search("James");
    User** u2 = users.search("HaHa");
    cout<<endl;
    cout<<(**(u1)<**(u2));
    //User** u = users.search("Bob");
    //Librarian* t =dynamic_cast<Librarian*>(*(u));
    //t->setMax_Period(1);
    cout<<endl;
    //bst.printLevelOrder();
    BookCopy** c = copys.search("18");
    outputFile();
}
