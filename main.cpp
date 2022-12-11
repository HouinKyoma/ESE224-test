#include<iostream>
#include"BST.h"
#include"BST.cpp"
#include"Book.h"
using namespace std;

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
    string s = "9781283329705";
    string s2 = "9781493938438	";
    long int isbn = stol(s);
    long int isbn2 = stol(s2);
    cout<<isbn;
    cout<<isbn2<<endl;;
    cout<<(isbn<isbn2);
}
