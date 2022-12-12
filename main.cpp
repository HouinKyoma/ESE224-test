#include<iostream>
#include<fstream>
#include"BST.h"
#include"BST.cpp"
#include"Book.h"
#include"User.h"
using namespace std;
BST<User> users;
void scanFile(){
    int type;
	ifstream fin("student.txt");
	if (fin.fail()) {
		cerr << "Error opening student file.";
		exit(1);
	}

	//Teacher myTeacher;
	Student student;
    Teacher teacher;
    Librarian lib;
	do {
		fin >> type;
		if (type == 0) {
		    fin >> student;
            users.insert(student);
		//	//teacherList.push_back(myTeacher);
		}
		else if( type == 1) {
			fin >> teacher;
            users.insert(teacher);
        }
        else {
            fin>>lib;
            users.insert(lib);

        }
	} while (!fin.eof());
};


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
    BST<int> bst = BST<int>();
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
    cout<<(isbn<isbn2);
    //--------------------testing for file input ------------------
    users = BST<User>();
    scanFile();
}
