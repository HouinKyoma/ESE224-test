#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "BST.h"
#include "BST.cpp"
#include "Book.h"
#include "User.h"

using namespace std;
BST<User *> users;
BST<Book *> books;
BST<BookCopy *> copys;
time_t startDate;
time_t BookCopy::startTime;
int BookCopy::IDassign = 1;
//------------------function declarations----------------
void searchBook();
void borrowBook(Reader *r);
void returnBook(Reader *r);
void reserveBook(Reader *r);

void deleteBook(Librarian *l);
void deleteUser(Librarian *l);

int dateCounter()
{
    time_t currentTime;
    time(&currentTime);
    return difftime(currentTime, startDate) / 5; // return the number of time passed in day;
}

void searchBook()
{
    vector<string> searchArgs = vector<string>(4);
    system("clear");
    cout << "Please enter book information to search for books:" << endl;
    cout << "Enter title: ";
    cin >> searchArgs[0];
    cout << "Enter author: ";
    cin >> searchArgs[1];
    cout << "Enter category: ";
    cin >> searchArgs[2];
    cout << "Enter ISBN: ";
    cin >> searchArgs[3];
    vector<BookCopy> result = copys.searchBook(searchArgs);
    printf("%-35s|%-30s|%-20s|%-20s|%-5s|%-10s\n", "Title", "Author", "Category", "ISBN", "ID", "Status");
    for (int i = 0; i < 140; i++)
    {
        cout << "-";
    }
    cout << endl;
    char yes[] = "YES";
    char no[] = "NO";
    for (auto copy : result)
    {
        bool status = copy.getReaderName() == "" && copy.getReserverName() == "";
        printf("%-35s|%-30s|%-20s|%-20s|%-5s|%-10s\n", copy.getBook()->getTitle().c_str(), copy.getBook()->getAuthor().c_str(), copy.getBook()->getCategory().c_str(), copy.getISBN().c_str(), copy.getKey().c_str(), status ? yes : no);
    }
    // cout<<
    // then print
}

void borrowBook(Reader *r)
{
    int ID;
    cout << "Enter the ID of the book copy you want to borrow" << endl;
    cin >> ID;
    r->borrowBook(ID, copys);
}
void returnBook(Reader *r)
{
    int ID;
    cout << "Enter the ID of the book copy you want to return" << endl;
    cin >> ID;
    r->returnBook(ID, copys);
}

void renewBook(Reader *r)
{
    int ID;
    cout << "Enter the ID of the book copy you want to renew" << endl;
    cin >> ID;
    r->renewBook(ID, copys);
}

void reserveBook(Reader *r)
{
    string isbn;
    cout << "Enter the ISBN of the book copy you want to reserve" << endl;
    cin >> isbn;
    r->reserveBook(isbn, books);
}
void cancelBook(Reader *r)
{
    string isbn;
    cout << "Enter the ISBN of the book copy you want to cancel reserve" << endl;
    cin >> isbn;
    r->cancelReserve(isbn, books);
}

void deleteBook(Librarian *l)
{
    int ID;
    cout << "Enter the ID of the book to be removed" << endl;
    cin >> ID;
    l->deleteBook(ID, books, copys);
}

void deleteUser(Librarian *l)
{
    string name;
    cout << "Enter the name of the user to be removed" << endl;
    cin >> name;
    l->deleteUser(name, users);
}

/**
 * @brief student version for printing all the information of a user, including name, account type, list of borrowed book, list of reservation
 *
 * @param s a pointer of Student object
 */
void myInfo(Reader *s)
{
    system("clear");
    time_t currentTime;
    time(&currentTime);
    char yes[] = "YES";
    char no[] = "NO";
    int currentDay = (currentTime - startDate) / 5;

    cout << "Account Type: Student" << endl;
    cout << "Username: " << s->getUsername() << endl;
    // cout<<"Penalty: "<<
    cout << "List of borrowed book:" << endl;
    printf("%-35s|%-30s|%-20s|%-20s|%-5s|%-10s\n", "Title", "Author", "Category", "ISBN", "ID", "Overdue?");
    for (int i = 0; i < 140; i++)
    {
        cout << "-";
    }
    cout << endl;
    for (auto copy : s->getBorrowedList())
    {
        bool status = copy.getExpDate() < currentDay; // when current day past the expday, it is overdue, true = overdue, false = not overdue
        printf("%-35s|%-30s|%-20s|%-20s|%-5s|%-10s\n", copy.getBook()->getTitle().c_str(), copy.getBook()->getAuthor().c_str(), copy.getBook()->getCategory().c_str(), copy.getISBN().c_str(), copy.getKey().c_str(), status ? yes : no);
    }
    cout << "List of book reservation:" << endl;
    for (auto book : s->getReservedList())
    {
        cout << book.getTitle() << endl;
    }
    string chr;
    cout << "Enter any character to go back to main menu" << endl;
    cin >> chr;
}
/**
 * @brief librarian version of my information, only password and user name is shown
 * 
 * @param l 
 */
void myInfo(Librarian *l) {

}

void changePassword(User *u)
{
    string newPassword, oldPassword;
    cout << "Enter your old password:";
    cin >> oldPassword;
    if (oldPassword != (*u).getPassword())
    {
        cout << "Password does not match" << endl;
        return;
    }
    cout << "Enter your new password:";
    cin >> newPassword;
    (*u).setPassword(newPassword);
}
/**
 * @brief function to read file into bst
 * To support polymorphism, a pointer to the object is used instead of object.
 *
 */
void scanFile()
{
    int type;
    ifstream fin("student.txt");
    if (fin.fail())
    {
        cerr << "Error opening student file.";
        exit(1);
    }

    while (true)
    {
        fin >> type;
        if (type == 0)
        {

            Student *student = new Student();
            fin >> *(student);
            User *user = student;
            user->setKey();
            user->setType(0);
            users.insert(user);
        }
        else if (type == 1)
        {

            Teacher *teacher = new Teacher();

            fin >> *(teacher);
            User *user = teacher;
            user->setKey();
            user->setType(1);
            users.insert(user);
        }
        else
        {

            Librarian *lib = new Librarian();
            fin >> *(lib);
            User *user = lib;
            user->setKey();
            user->setType(2);
            users.insert(user);
        }

        if (fin.eof())
        {
            break;
        }
    }

    ifstream fin2("book.txt");
    if (fin2.fail())
    {
        cerr << "Error opening book file.";
        exit(1);
    }

    while (true)
    {
        Book *book = new Book();
        fin2 >> *(book);
        book->setKey();
        books.insert(book);
        if (fin2.eof())
        {
            break;
        }
    }

    ifstream fin3("copy.txt");
    if (fin3.fail())
    {
        cerr << "Error opening copy file.";
        exit(1);
    }

    while (true)
    {
        /* code */
        BookCopy *copy = new BookCopy();
        fin3 >> *(copy);

        string isbn = copy->getISBN();
        Book **bpptr = books.search(isbn);
        Book *&b = *(bpptr);
        copy->setBook(b);
        b->addCopy(*copy);
        copy->setKey();

        copys.insert(copy);
        if (fin3.eof())
        {
            break;
        }
    }
};
void outputFile()
{
    //separate input and output file name are used during testing for preventing corruption of origin data.
    ofstream myfile;
    myfile.open("student2.txt");
    if (myfile.is_open())
    {
        users.printLevelOrder(myfile);
    }
    else
        cout << "Unable to open file";

    myfile.close();
    ofstream myfile2;
    myfile2.open("book2.txt");
    if (myfile2.is_open())
    {
        books.printLevelOrder(myfile2);
    }
    else
        cout << "Unable to open file";

    myfile2.close();
    ofstream myfile3;
    myfile3.open("copy2.txt");
    if (myfile3.is_open())
    {
        copys.printLevelOrder(myfile3);
    }
    else
        cout << "Unable to open file";

    myfile3.close();
}
int login(Librarian *&l, Teacher *&t, Student *&s)
{

    string name;
    string password;
    cout << "Username: ";
    cin >> name;

    User **u = users.search(name);
    if (u == nullptr)
    {
        cout << "User with name " << name << " does not exist." << endl;
        return -1;
    }

    // convert to the according derived class
    l = dynamic_cast<Librarian *>(*(u));
    t = dynamic_cast<Teacher *>(*(u));
    s = dynamic_cast<Student *>(*(u));
    cout << "Enter Password: ";
    cin >> password;
    if ((*u)->getPassword() == password)
    {

        if (l != nullptr)
        {

            return 2;
        }
        else if (t != nullptr)
        {
            return 1;
        }
        else if (s != nullptr)
        {

            return 0;
        }
        // check if user with the username exist
    }
    else
    {
        cout << "Incorrect password!" << endl;
        return -1;
    }
}
void printLibrarianMenu()
{
    time_t currentTime;
    time(&currentTime);
    int currentDay = (currentTime - startDate) / 5;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "-\t\t\tWelcome to My Library!\t\t\t-" << endl;
    cout << "-\t\t\tCurrent day: " << currentDay << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "\nWelcome back, Student" << endl;
    cout << "\nPlease choose:" << endl;
    cout << "\t1 -- Add Book" << endl;
    cout << "\t2 -- Delete Book" << endl;
    cout << "\t3 -- Search Users" << endl;
    cout << "\t4 -- Add Users" << endl;
    cout << "\t5 -- Delete Users" << endl;
    cout << "\t6 -- My Information" << endl;
    cout << "\t7 -- Change Password" << endl;
    cout << "\t0 -- Log Out\n"
         << endl;
}
void printStudentMenu(bool isTeacher)
{
    time_t currentTime;
    time(&currentTime);
    int currentDay = (currentTime - startDate) / 5;

    cout << "-----------------------------------------------------------------" << endl;
    cout << "-\t\t\tWelcome to My Library!\t\t\t-" << endl;
    cout << "-\t\t\tCurrent day: " << currentDay << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "\nWelcome back, " << (isTeacher ? "Teacher" : "Student") << endl;
    cout << "\nPlease choose:" << endl;
    cout << "\t1 -- Search Book" << endl;
    cout << "\t2 -- Borrow Book" << endl;
    cout << "\t3 -- Return Book" << endl;
    cout << "\t4 -- Renew Book" << endl;
    cout << "\t5 -- Reserve Book" << endl;
    cout << "\t6 -- Cancel Book" << endl;
    cout << "\t7 -- My Information" << endl;
    cout << "\t8 -- Change Password" << endl;
    cout << "\t9 -- I'm Feeling Lucky" << endl;
    cout << "\t0 -- Log Out\n"
         << endl;
}

void studentSystem(Reader *s)
{
    int input;
    bool isTeacher = s->getType() == 1;
    do
    {
        printStudentMenu(isTeacher);
        cin >> input;
        switch (input)
        {
        case 1:
            searchBook();
            break;
        case 2:
            borrowBook(s);
            break;
        case 3:
            returnBook(s);
            break;
        case 4:
            renewBook(s);
            break;
        case 5:
            reserveBook(s);
            break;
        case 6:
            cancelBook(s);
            break;
        case 7:
            myInfo(s);
            break;
        case 8:
            changePassword(s);
            break;
        default:
            break;
        }
    } while (input != 0);
}
void librarianSystem(Librarian *l)
{
    int input;
    do
    {
        printLibrarianMenu();
        cin >> input;
        switch (input)
        {
        case 1:
            l->addBook(books, copys);
            break;
        case 2:
            deleteBook(l);
            break;
        case 3:
            l->searchUser(users);
            break;
        case 4:
            l->addUser(users);
            break;
        case 5:
            deleteUser(l);
            break;
        case 6:
            myInfo(l);

            break;
        case 7:

            changePassword(l);
            break;
        default:
            break;
        }
    } while (input != 0);
}

int main()
{
    // configurations:
    // setup time
    time(&startDate);
    time(&BookCopy::startTime);
    // Load from file
    // load into a BST
    users = BST<User *>();
    books = BST<Book *>();
    copys = BST<BookCopy *>();
    scanFile();
    // User** u2 = users.search("HaHa");
    // Student* stu =dynamic_cast<Student*>(*(u2));
    // borrowBook(stu);
    Teacher *t;
    Student *s;
    Librarian *l;
    string anyKey;
    char c;
    try{
    while (true)
    {
        cout << "type q to quit, any other character to login:" << endl;
        cin >> c;
        if (c == 'q' || c == 'Q')
        {
            break;
        }
        while (login(l, t, s) == -1)
        {
            cout << "enter any character  to reenter" << endl;
            cin >> anyKey;
            system("clear");
        }

        if (s != nullptr)
        {
            studentSystem(s);
        }
        else if (t != nullptr)
        {
            studentSystem(t);
        }
        else if (l != nullptr)
        {
            librarianSystem(l);
        }
    }
    }
    catch(std::invalid_argument e){
        cout<<e.what()<<endl;
    }

    Book **test = books.search("sss");
    cout << "Quitting... outputing files..." << endl;
    outputFile();
    // login
    // reader login
    // print reader menu
    //

    // librarian login
    // print lib menu
    // request new book copy
    // delete existing copy
    // search users
    // add new users
    // delete old users

    // when ending, update the txt files

    /*

    //---------------------testing code--------------------------
    User** u1 = users.search("James");
    //User** u2 = users.search("HaHa");
    cout<<endl;
    cout<<(**(u1)<**(u2));
    //User** u = users.search("Bob");
    //Librarian* t =dynamic_cast<Librarian*>(*(u));
    //t->setMax_Period(1);
    cout<<endl;
    //bst.printLevelOrder();
    BookCopy** c = copys.search("18");
    User* u = *(u1);
    users.remove(u);
    vector<BookCopy*>vec = copys.vectorize();
    cout<<(*(vec[0])==*(vec[1]))<<endl;
    cout<<(vec[0]->getBook())<<endl;
    cout<<((*(vec[0])<*(vec[1])))<<endl;
    vector<BookCopy> v = BookCopy::transformVec(vec);
    cout<<v[0].getBook()<<endl;
    //BookCopy::quickSort(vec,0,vec.size());
    for(auto i:vec){
        cout<<*i<<endl;
    }
    vector<string> searchargs = vector<string>();
    searchargs.push_back("First_Lessons_in_Bach");
    searchargs.push_back("");
    searchargs.push_back("");
    searchargs.push_back("");
    vector<BookCopy> testSearch = copys.searchBook(searchargs);
    for(auto i: testSearch){cout<<i<<endl;}
    outputFile();


    */
}
