#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <cstdio>
#include <vector>
#include <windows.h>

using namespace std;

// Class declarations:

class Book{
    private:
        int bookId;
    public:
        int getId();
        void setId(int id);
        string bookStatus;
        string title;
        string author;
        string publisher;
        string year;
        void fetchData(int id);
        void loadData(int id);
        bool bookExists(int id);
        int getTotal();
        void updateTotal(int tot);
};

class Account
{
private:
    int fine;
    int UserId;

public:
    static int SecPerDay;
    string role;
    int getUserId();
    void setUserId(int id);
    int getFine();
    void updateFine();
    void setFine(int money);
    int bookLimit;
    int timeLimit;
    int OverdueDays;
    int bookCount;
    void fetchData(int id);
    void loadData(int id);
    void loadBorrowedBook(int bookId);
    void loadBookHistory(int bookId);
    void viewBorrowedBooks();
};

class Library
{
public:
    Book book;
    int Id;
    int getPrevId();
    void updateId();
    void updateStatustoAvailable(int bookId);
    void updateStatustoBorrowed(int bookId);
    void addBook();
    void removeBook();
    void viewBooks();
};

class User
{
private:
    int UserId;
    string password;

public:
    string role;
    string name;
    int getUserId();
    void setUserId(int id);
    string getPassword();
    bool correctPassword(string pass);
    string encryptedPassword(string pass);
    void setPassword(string pass);
    void fetchPassword(string pass);
    void updateStatustoAvailable(int bookId);
    void updateStatustoBorrowed(int bookId);
    virtual bool accountExists(int id) = 0;
    virtual void fetchData(int id) = 0;
    virtual void newUser(string name, string pass) = 0;
    virtual void deleteAccount(int id) = 0;
    virtual ~User() {}
};

class Student : public User
{
public:
    int Fine();
    void payFine();
    int getOverdues();
    int Id;
    int getPrevId();
    void updateId();
    bool accountExists(int id) override;
    void fetchData(int id) override;
    void borrowBook(int bookId);
    void returnBook(int bookId);
    void viewBorrowedBooks();
    void viewHistory();
    void newUser(string name, string pass) override;
    void deleteAccount(int id) override;
    Account acc;
};

class Faculty : public User
{
public:
    int getOverdues();
    int Id;
    int getPrevId();
    void updateId();
    void borrowBook(int bookId);
    void returnBook(int bookId);
    void viewBorrowedBooks();
    void viewHistory();
    bool accountExists(int id) override;
    void fetchData(int id) override;
    void newUser(string name, string pass) override;
    void deleteAccount(int id) override;
    Account acc;
};

class Librarian : public User
{
public:
    Library lib;
    int Id;
    int getPrevId();
    void updateId();
    bool accountExists(int id) override;
    void fetchData(int id) override;
    void addBook();
    void removeBook();
    void addUser();
    void removeUser();
    void newUser(string name, string pass) override;
    void deleteAccount(int id) override;
};

// Function declaration:

string chooseRole();
void Login();
void LibrarianRoles(Librarian l1);
void StudentRoles(Student s1);
void FacultyRoles(Faculty f1);

// Main:

int main()
{
    cout << "\nIf you are new or wish to create account, consult Librarian.\n\n";
    Login();
    cout << "Thank you for using our Library Management System.\n\n";
    return 0;
}

// Function definitions:

string chooseRole()
{
    cout << "1. Student\n";
    cout << "2. Faculty\n";
    cout << "3. Librarian\n";
    cout << "Choose your role : ";
    string role;
    cin >> role;
    cin.ignore();
    cout << "\n";
    return role;
}

void Login()
{
    string role = chooseRole();
    int i;
    if (role == "1")
    {
        string id;
        string pass;
        Student s1;
        i = 0;
        while (i < 3)
        {
            try{
                cout << "Enter your UserId : ";
                cin >> id;
                cout << "\n";
                stoi(id);
            }
            catch(...){
                i++;
                if (i == 3)
                {
                    cout << "\nInvalid input.";
                }
                else
                {
                    cout << "\nInvalid input. Try again.\n\n";
                }
                continue;
            }
            if (s1.accountExists(stoi(id)))
            {
                s1.fetchData(stoi(id));
                break;
            }
            else
            {
                i++;
                if (i == 3)
                {
                    cout << "\nUserId doesn't exist.";
                }
                else
                {
                    cout << "\nUserId doesn't exist. Try again.\n\n";
                }
            }
        }
        if (i == 3)
        {
            cout << "\nToo many failed attempts.";
            cout << "\nSession ended.\n\n";
            return;
        }
        i = 0;
        while (i < 3)
        {
            cout << "Enter your password : ";
            cin >> pass;
            cout << "\n";
            if (s1.correctPassword(pass))
            {
                break;
            }
            else
            {
                i++;
                if (i == 3)
                {
                    cout << "\nIncorrect Password.";
                }
                else
                {
                    cout << "\nIncorrect Password. Try again.\n\n";
                }
            }
        }
        if (i == 3)
        {
            cout << "\nToo many failed attempts.";
            cout << "\nSession ended.\n\n";
            return;
        }
        StudentRoles(s1);
    }
    else if (role == "2")
    {
        string id;
        string pass;
        Faculty f1;
        i = 0;
        while (i < 3)
        {
            try{
                cout << "Enter your UserId : ";
                cin >> id;
                cout << "\n";
                stoi(id);
            }
            catch(...){
                cout << "\nInvalid input. Try again.\n\n";
                i++;
                continue;
            }
            if (f1.accountExists(stoi(id)))
            {
                f1.fetchData(stoi(id));
                break;
            }
            else
            {
                i++;
                if (i == 3)
                {
                    cout << "\nUserId doesn't exist.";
                }
                else
                {
                    cout << "\nUserId doesn't exist. Try again.\n\n";
                }
            }
        }
        if (i == 3)
        {
            cout << "\nToo many failed attempts.";
            cout << "\nSession ended.\n\n";
            return;
        }
        i = 0;
        while (i < 3)
        {
            cout << "Enter your password : ";
            cin >> pass;
            cout << "\n";
            if (f1.correctPassword(pass))
            {
                break;
            }
            else
            {
                i++;
                if (i == 3)
                {
                    cout << "\nIncorrect Password.";
                }
                else
                {
                    cout << "\nIncorrect Password. Try again.\n\n";
                }
            }
        }
        if (i == 3)
        {
            cout << "\nToo many failed attempts.";
            cout << "\nSession ended.\n\n";
            return;
        }
        FacultyRoles(f1);
    }
    else if (role == "3")
    {
        string id;
        string pass;
        Librarian l1;
        i = 0;
        while (i < 3)
        {
            try{
                cout << "Enter your UserId : ";
                cin >> id;
                cout << "\n";
                stoi(id);
            }
            catch(...){
                cout << "\nInvalid input. Try again.\n\n";
                i++;
                continue;
            }
            if (l1.accountExists(stoi(id)))
            {
                l1.fetchData(stoi(id));
                break;
            }
            else
            {
                i++;
                if (i == 3)
                {
                    cout << "\nUserId doesn't exist.";
                }
                else
                {
                    cout << "\nUserId doesn't exist. Try again.\n\n";
                }
            }
        }
        if (i == 3)
        {
            cout << "\nToo many failed attempts.";
            cout << "\nSession ended.\n\n";
            return;
        }
        i = 0;
        while (i < 3)
        {
            cout << "Enter your password : ";
            cin >> pass;
            cout << "\n";
            if (l1.correctPassword(pass))
            {
                break;
            }
            else
            {
                i++;
                if (i == 3)
                {
                    cout << "\nIncorrect Password.";
                }
                else
                {
                    cout << "\nIncorrect Password. Try again.\n\n";
                }
            }
        }
        if (i == 3)
        {
            cout << "\nToo many failed attempts.";
            cout << "\nSession ended.\n\n";
            return;
        }
        LibrarianRoles(l1);
    }
    else
    {
        cout << "\nRole not available. Session ended.\n\n";
    }
    return;
}

void StudentRoles(Student s1)
{
    cout << "\nYou have successfully into you Student account with UserId : " << s1.getUserId() << "\n\n";
    int id = s1.getUserId();
    while (1)
    {
        s1.fetchData(id);
        cout << "Here are your permissions as Student : \n";
        cout << "1. View all Books along with its BookId\n";
        cout << "2. Borrow Book\n";
        cout << "3. Return Book\n";
        cout << "4. BookId's of the Borrowed Books\n";
        cout << "5. View Borrowed History\n";
        cout << "6. View Fine\n";
        cout << "7. Pay Fine\n";
        cout << "8. View no. of Overdue Days\n";
        cout << "9. Logout\n";
        cout << "Choose an option : ";
        string action;
        cin >> action;
        cout << "\n";
        if (action == "1")
        {
            Library lib;
            lib.viewBooks();
        }
        else if (action == "2")
        {
            int bookId;
            cout << "Enter BookId : ";
            cin >> bookId;
            cout << "\n";
            s1.borrowBook(bookId);
        }
        else if (action == "3")
        {
            int bookId;
            cout << "Enter BookId : ";
            cin >> bookId;
            cout << "\n";
            s1.returnBook(bookId);
        }
        else if (action == "4")
        {
            s1.viewBorrowedBooks();
        }
        else if (action == "5")
        {
            s1.viewHistory();
        }
        else if (action == "6")
        {
            if (s1.Fine())
            {
                cout << "\nYour fine : " << s1.Fine() << "/-\n\n";
            }
            else
            {
                cout << "\nYou have no fines at the moment.\n\n";
            }
        }
        else if (action == "7")
        {
            s1.payFine();
        }
        else if (action == "8")
        {
            cout << "\nNo. of Overdue Days : " << s1.getOverdues() << "\n\n";
        }
        else if (action == "9")
        {
            cout << "\nYou have succesfully logged out of the Student account.\n\n";
            Login();
            break;
        }
        else
        {
            cout << "\nSession ended.\n\n";
            break;
        }
    }
    return;
}

void FacultyRoles(Faculty f1)
{
    cout << "\nYou have successfully into you Faculty account with UserId : " << f1.getUserId() << "\n\n";
    int id = f1.getUserId();
    while (1)
    {
        f1.fetchData(id);
        cout << "Here are your permissions as Faculty : \n";
        cout << "1. View all Books along with its BookId\n";
        cout << "2. Borrow Book\n";
        cout << "3. Return Book\n";
        cout << "4. BookId's of the Borrowed Books\n";
        cout << "5. View Borrowed History\n";
        cout << "6. View no. of Overdue Days\n";
        cout << "7. Logout\n";
        cout << "Choose an option : ";
        string action;
        cin >> action;
        cout << "\n";
        if (action == "1")
        {
            Library lib;
            lib.viewBooks();
        }
        else if (action == "2")
        {
            int bookId;
            cout << "Enter BookId : ";
            cin >> bookId;
            cout << "\n";
            f1.borrowBook(bookId);
        }
        else if (action == "3")
        {
            int bookId;
            cout << "Enter BookId : ";
            cin >> bookId;
            cout << "\n";
            f1.returnBook(bookId);
        }
        else if (action == "4")
        {
            f1.viewBorrowedBooks();
        }
        else if (action == "5")
        {
            f1.viewHistory();
        }
        else if (action == "6")
        {
            cout << "\nNo. of Overdue Days : " << f1.getOverdues() << "\n\n";
        }
        else if (action == "7")
        {
            cout << "\nYou have succesfully logged out of the Faculty account.\n\n";
            Login();
            break;
        }
        else
        {
            cout << "\nSession ended.\n\n";
            break;
        }
    }
    return;
}

void LibrarianRoles(Librarian l1)
{
    cout << "\nYou have successfully into you Librarian account with UserId : " << l1.getUserId() << "\n\n";
    while (1)
    {
        cout << "Here are your permissions as Librarian : \n";
        cout << "1. View all Books along with its BookId\n";
        cout << "2. Add Book\n";
        cout << "3. Remove Book\n";
        cout << "4. Add User\n";
        cout << "5. Remove User\n";
        cout << "6. Logout\n";
        cout << "Choose an option : ";
        string action;
        cin >> action;
        cout << "\n";
        if (action == "1")
        {
            l1.lib.viewBooks();
        }
        else if (action == "2")
        {
            l1.addBook();
        }
        else if (action == "3")
        {
            l1.removeBook();
        }
        else if (action == "4")
        {
            cout << "\nCreating a new account.\n\n";
            l1.addUser();
        }
        else if (action == "5")
        {
            cout << "\nRemoving an account.\n\n";
            l1.removeUser();
        }
        else if (action == "6")
        {
            cout << "\nYou have succesfully logged out of the Librarian account.\n\n";
            Login();
            break;
        }
        else
        {
            cout << "\nSession ended.\n\n";
            break;
        }
    }
    return;
}

// Class definitions:

// User class definitions:

int User ::getUserId()
{
    return UserId;
}

void User ::setUserId(int id)
{
    UserId = id;
    return;
}

string User ::getPassword()
{
    return password;
}

bool User ::correctPassword(string pass)
{
    return encryptedPassword(pass) == getPassword();
}

string User ::encryptedPassword(string pass)
{
    string salt1 = "abc";
    string salt2 = "123";
    return (salt1 + pass + salt2);
}

void User ::setPassword(string pass)
{
    password = encryptedPassword(pass);
    return;
}

void User ::fetchPassword(string pass)
{
    password = pass;
    return;
}


void User ::updateStatustoAvailable(int bookId)
{
    Library lib;
    lib.updateStatustoAvailable(bookId);
    return;
}

void User ::updateStatustoBorrowed(int bookId)
{
    Library lib;
    lib.updateStatustoBorrowed(bookId);
}

// Student class definitions:

int Student ::Fine()
{
    acc.updateFine();
    return acc.getFine();
}

void Student ::payFine()
{
    if (Fine())
    {
        acc.setFine(0);
        acc.loadData(getUserId());
        cout << "\nYour fines have been cleared.\n\n";
    }
    else
    {
        cout << "\nYou have no fines to pay.\n\n";
    }
    return;
}

int Student ::getOverdues()
{
    acc.updateFine();
    return acc.OverdueDays;
}

int Student ::getPrevId()
{
    string filename = "Users/Student/id_counter.txt";
    ifstream file(filename);
    int prevId;
    if (file.is_open())
    {
        file >> prevId;
        file.close();
    }
    else
    {
        prevId = 100;
    }
    return prevId;
}

void Student ::updateId()
{
    string filename = "Users/Student/id_counter.txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << Id;
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while updating Id. Student.updateId.\n\n";
    }
    return;
}

bool Student ::accountExists(int id)
{
    string filename = "Users/Student/user_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        file.close();
        return true;
    }
    return false;
}

void Student ::fetchData(int id)
{
    string filename = "Users/Student/user_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        string temp;
        setUserId(id);
        getline(file, role);
        getline(file, name);
        getline(file, temp);
        fetchPassword(temp);
        file.close();

        acc.role = "Student";
        acc.bookLimit = 3;
        acc.timeLimit = 15;
        acc.setUserId(getUserId());
        acc.fetchData(id);
    }
    else
    {
        cout << "\nSomething went wrong while fetching data. Student.fetchData.\n\n";
    }
    return;
}

void Student ::borrowBook(int bookId)
{
    Book book;
    if (!book.bookExists(bookId))
    {
        cout << "\nBook is not registered in the library at the moment.\n\n";
        return;
    }
    book.fetchData(bookId);
    acc.updateFine();
    if (acc.getFine())
    {
        cout << "\nClear fines to borrow books.\n\n";
        return;
    }
    else if (acc.bookCount >= acc.bookLimit)
    {
        cout << "\nYou have reached borrowing limit. Please submit atleast one book to borrow other books.\n\n";
        return;
    }
    else if (book.bookStatus != "Available")
    {
        cout << "\nCannot borrow book at the moment, it has been borrowed.\n\n";
        return;
    }
    else
    {
        acc.loadBorrowedBook(bookId);
        acc.bookCount += 1;
        acc.loadData(getUserId());
        updateStatustoBorrowed(bookId);
        cout << "\nYou have successfully borrowed the book.\n\n";
    }
}

void Student ::returnBook(int bookId)
{
    if (acc.bookCount)
    {
        int id[acc.bookCount];
        int Time[acc.bookCount];
        int index = -1;
        string filename = "Users/" + role + "/borrowed_" + to_string(getUserId()) + ".txt";
        ifstream file(filename);
        if (file.is_open())
        {
            string temp;
            for (int i = 0; i < acc.bookCount; i++)
            {
                getline(file, temp);
                id[i] = stoi(temp);
                getline(file, temp);
                Time[i] = stoi(temp);
                if (id[i] == bookId)
                {
                    index = i;
                }
            }
            file.close();
        }
        else
        {
            cout << "\nSomething is wrong while finding borrowed books. Student.returnBook.\n\n";
            return;
        }
        if (index == -1)
        {
            cout << "\nYou didn't borrow this book.\n\n";
            return;
        }
        acc.updateFine();
        ofstream fout(filename);
        if (fout.is_open())
        {
            for (int i = 0; i < acc.bookCount; i++)
            {
                if (index != i)
                {
                    fout << id[i] << "\n"
                         << Time[i] << "\n";
                }
            }
            fout.close();
        }
        else
        {
            cout << "\nIdentified the book in the borrowed. Something is wrong while returning. Student.returnBook.\n\n";
            return;
        }
        acc.bookCount -= 1;
        acc.loadBookHistory(bookId);
        acc.loadData(getUserId());
        updateStatustoAvailable(bookId);
        cout << "\nYou have successfully returned the book.\n\n";
    }
    else
    {
        cout << "\nYou don't have any borrowed books at the moment to return.\n\n";
    }
    return;
}

void Student ::viewBorrowedBooks()
{
    acc.viewBorrowedBooks();
    return;
}

void Student ::viewHistory()
{
    string filename = "Users/" + role + "/history_" + to_string(getUserId()) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        string temp;
        int i = 0;
        while (getline(file, temp))
        {
            cout << temp << "\n";
            i++;
        }
        file.close();
        cout << "\n";
        if (i == 0)
        {
            cout << "\nYou didn't return any book to view history.\n\n";
        }
    }
    else
    {
        cout << "\nSomething went wrong while checking history. Student.viewHistory.\n\n";
    }
    return;
}

void Student ::newUser(string name, string pass)
{
    CreateDirectory("Users/Student", NULL);
    Id = getPrevId();

    this->name = name;
    setPassword(pass);
    setUserId(Id);
    role = "Student";

    acc.role = "Student";
    acc.setUserId(Id);
    acc.setFine(0);
    acc.bookCount = 0;
    acc.OverdueDays = 0;
    acc.bookLimit = 3;
    acc.timeLimit = 15;
    acc.loadData(Id);

    string filename = "Users/Student/user_" + to_string(Id) + ".txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << role << "\n"
             << this->name << "\n"
             << getPassword();
        file.close();
        cout << "\nStudent account created!\n";
        cout << "Your UserId : " << getUserId() << "\n";
        cout << "Remember this UserId, you will have to login using this.\n\n";
    }
    else
    {
        cout << "\nSomething went wrong while creating a new user. Student.newUser.\n\n";
        return;
    }
    filename = "Users/Student/borrowed_" + to_string(Id) + ".txt";
    file.open(filename);
    if (file.is_open())
    {
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while creating a new user in borrowed. Student.newUser.\n\n";
        return;
    }
    filename = "Users/Student/history_" + to_string(Id) + ".txt";
    file.open(filename);
    if (file.is_open())
    {
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while creating a new user in history. Student.newUser.\n\n";
        return;
    }

    Id = getPrevId() + 1;
    updateId();

    return;
}

void Student ::deleteAccount(int id)
{
    if (accountExists(id))
    {
        string filename1 = "Users/Student/user_" + to_string(id) + ".txt";
        string filename2 = "Users/Student/account_" + to_string(id) + ".txt";
        string filename3 = "Users/Student/borrowed_" + to_string(id) + ".txt";
        string filename4 = "Users/Student/history_" + to_string(id) + ".txt";
        if (remove((filename1).c_str()))
        {
            cout << "\nSomething went wrong while deleting filename1. Student.deleteAccount.\n\n";
            return;
        }
        if (remove((filename2).c_str()))
        {
            cout << "\nSomething went wrong while deleting filename2. Student.deleteAccount.\n\n";
            return;
        }
        if (remove((filename3).c_str()))
        {
            cout << "\nSomething went wrong while deleting filename3. Student.deleteAccount.\n\n";
            return;
        }
        if (remove((filename4).c_str()))
        {
            cout << "\nSomething went wrong while deleting filename4. Student.deleteAccount.\n\n";
            return;
        }
        cout << "\nYou have successfully removed the Student with UserId : " << to_string(id) << "\n\n";
    }
    else
    {
        cout << "\nUser doesn't exist to remove.\n\n";
    }
}

// Faculty class definitions:

int Faculty ::getOverdues()
{
    acc.updateFine();
    return acc.OverdueDays;
}

int Faculty ::getPrevId()
{
    string filename = "Users/Faculty/id_counter.txt";
    ifstream file(filename);
    int prevId;
    if (file.is_open())
    {
        file >> prevId;
        file.close();
    }
    else
    {
        prevId = 100;
    }
    return prevId;
}

void Faculty ::updateId()
{
    string filename = "Users/Faculty/id_counter.txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << Id;
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while updating Id. Faculty.updateId.\n\n";
    }
    return;
}

bool Faculty ::accountExists(int id)
{
    string filename = "Users/Faculty/user_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        file.close();
        return true;
    }
    return false;
}

void Faculty ::fetchData(int id)
{
    string filename = "Users/Faculty/user_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        string temp;
        setUserId(id);
        getline(file, role);
        getline(file, name);
        getline(file, temp);
        fetchPassword(temp);
        file.close();

        acc.role = "Faculty";
        acc.bookLimit = 5;
        acc.timeLimit = 30;
        acc.setUserId(id);
        acc.fetchData(id);
    }
    else
    {
        cout << "\nSomething went wrong while fetching data. Faculty.fetchData.\n\n";
    }
    return;
}

void Faculty ::borrowBook(int bookId)
{
    Book book;
    if (!book.bookExists(bookId))
    {
        cout << "\nBook is not registered in the library at the moment.\n\n";
        return;
    }
    book.fetchData(bookId);
    acc.updateFine();
    if (acc.OverdueDays >= 60)
    {
        cout << "\nYour Overdue Days have exceeded 60. You can no longer borrow books.\n\n";
        return;
    }
    else if (acc.bookCount >= acc.bookLimit)
    {
        cout << "\nYou have reached borrowing limit. Please submit atleast one book to borrow other books.\n\n";
        return;
    }
    else if (book.bookStatus != "Available")
    {
        cout << "\nCannot borrow book at the moment, it has been borrowed.\n\n";
        return;
    }
    else
    {
        acc.loadBorrowedBook(bookId);
        acc.bookCount += 1;
        acc.loadData(getUserId());
        updateStatustoBorrowed(bookId);
        cout << "\nYou have successfully borrowed the book.\n\n";
    }
    return;
}

void Faculty ::returnBook(int bookId)
{
    if (acc.bookCount)
    {
        int id[acc.bookCount];
        int Time[acc.bookCount];
        int index = -1;
        string filename = "Users/" + role + "/borrowed_" + to_string(getUserId()) + ".txt";
        ifstream file(filename);
        if (file.is_open())
        {
            string temp;
            for (int i = 0; i < acc.bookCount; i++)
            {
                getline(file, temp);
                id[i] = stoi(temp);
                getline(file, temp);
                Time[i] = stoi(temp);
                if (id[i] == bookId)
                {
                    index = i;
                }
            }
            file.close();
        }
        else
        {
            cout << "\nSomething is wrong while finding borrowed books. Faculty.returnBook.\n\n";
            return;
        }
        if (index == -1)
        {
            cout << "\nYou didn't borrow this book.\n\n";
            return;
        }
        acc.updateFine();
        ofstream fout(filename);
        if (fout.is_open())
        {
            for (int i = 0; i < acc.bookCount; i++)
            {
                if (index != i)
                {
                    fout << id[i] << "\n"
                         << Time[i] << "\n";
                }
            }
            fout.close();
        }
        else
        {
            cout << "\nIdentified the book in the borrowed. Something is wrong while returning. Faculty.returnBook.\n\n";
            return;
        }
        acc.bookCount -= 1;
        acc.loadBookHistory(bookId);
        acc.loadData(getUserId());
        updateStatustoAvailable(bookId);
        cout << "\nYou have successfully returned the book.\n\n";
    }
    else
    {
        cout << "\nYou don't have any borrowed books at the moment to return.\n\n";
    }
    return;
}

void Faculty ::viewBorrowedBooks()
{
    acc.viewBorrowedBooks();
    return;
}

void Faculty ::viewHistory()
{
    string filename = "Users/" + role + "/history_" + to_string(getUserId()) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        string temp;
        int i = 0;
        while (getline(file, temp))
        {
            cout << temp << "\n";
            i++;
        }
        file.close();
        cout << "\n";
        if (i == 0)
        {
            cout << "\nYou didn't return any book to view history.\n\n";
        }
    }
    else
    {
        cout << "\nSomething went wrong while checking history. Faculty.viewHistory.\n\n";
    }
    return;
}

void Faculty ::newUser(string name, string pass)
{
    CreateDirectory("Users/Faculty", NULL);
    Id = getPrevId();

    this->name = name;
    setPassword(pass);
    setUserId(Id);
    role = "Faculty";

    acc.role = "Faculty";
    acc.setUserId(Id);
    acc.setFine(0);
    acc.bookCount = 0;
    acc.OverdueDays = 0;
    acc.bookLimit = 5;
    acc.timeLimit = 30;
    acc.loadData(Id);

    string filename = "Users/Faculty/user_" + to_string(Id) + ".txt";
    ofstream file;
    file.open(filename);
    if (file.is_open())
    {
        file << role << "\n"
             << this->name << "\n"
             << getPassword();
        file.close();
        cout << "\nFaculty account created!\n";
        cout << "Your UserId : " << getUserId() << "\n";
        cout << "Remember this UserId, you will have to login using this.\n\n";
    }
    else
    {
        cout << "\nSomething went wrong while creating a new user. Faculty.newUser.\n\n";
        return;
    }
    filename = "Users/Faculty/borrowed_" + to_string(Id) + ".txt";
    file.open(filename);
    if (file.is_open())
    {
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while creating a new user in borrowed. Faculty.newUser.\n\n";
        return;
    }
    filename = "Users/Faculty/history_" + to_string(Id) + ".txt";
    file.open(filename);
    if (file.is_open())
    {
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while creating a new user in history. Faculty.newUser.\n\n";
        return;
    }

    Id = getPrevId() + 1;
    updateId();

    return;
}

void Faculty ::deleteAccount(int id)
{
    if (accountExists(id))
    {
        string filename1 = "Users/Faculty/user_" + to_string(id) + ".txt";
        string filename2 = "Users/Faculty/account_" + to_string(id) + ".txt";
        string filename3 = "Users/Faculty/borrowed_" + to_string(id) + ".txt";
        string filename4 = "Users/Faculty/history_" + to_string(id) + ".txt";
        if (remove((filename1).c_str()))
        {
            cout << "\nSomething went wrong while deleting filename1. Faculty.deleteAccount.\n\n";
            return;
        }
        if (remove((filename2).c_str()))
        {
            cout << "\nSomething went wrong while deleting filename2. Faculty.deleteAccount.\n\n";
            return;
        }
        if (remove((filename3).c_str()))
        {
            cout << "\nSomething went wrong while deleting filename3. Faculty.deleteAccount.\n\n";
            return;
        }
        if (remove((filename4).c_str()))
        {
            cout << "\nSomething went wrong while deleting filename4. Faculty.deleteAccount.\n\n";
            return;
        }
        cout << "\nYou have successfully removed the Faculty with UserId : " << to_string(id) << "\n\n";
    }
    else
    {
        cout << "\nUser doesn't exist to remove.\n\n";
    }
}

// Librarian class definitions:

int Librarian ::getPrevId()
{
    string filename = "Users/Librarian/id_counter.txt";
    ifstream file(filename);
    int prevId;
    if (file.is_open())
    {
        file >> prevId;
        file.close();
    }
    else
    {
        prevId = 100;
    }
    return prevId;
}

void Librarian ::updateId()
{
    string filename = "Users/Librarian/id_counter.txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << Id;
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while updating Id. Librarian.updateId.\n\n";
    }
    return;
}

void Librarian ::addBook()
{
    lib.addBook();
    return;
}

void Librarian ::removeBook()
{
    lib.removeBook();
    return;
}

void Librarian ::fetchData(int id)
{
    string filename = "Users/Librarian/user_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        string temp;
        setUserId(id);
        getline(file, role);
        getline(file, name);
        getline(file, temp);
        fetchPassword(temp);
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while fetching data. Librarian.fetchData.\n\n";
    }
    return;
}

void Librarian ::newUser(string name, string pass)
{
    Id = getPrevId();

    this->name = name;
    setPassword(pass);
    setUserId(Id);
    role = "Librarian";

    string filename = "Users/Librarian/user_" + to_string(Id) + ".txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << role << "\n"
             << this->name << "\n"
             << getPassword();
        file.close();
        cout << "\nLibrarian account created!\n";
        cout << "Your UserId : " << getUserId() << "\n";
        cout << "Remember this UserId, you will have to login using this.\n\n";
    }
    else
    {
        cout << "\nSomething went wrong while creating a new user. Librarian.newUser.\n\n";
    }

    Id = getPrevId() + 1;
    updateId();

    return;
}

bool Librarian ::accountExists(int id)
{
    string filename = "Users/Librarian/user_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        file.close();
        return true;
    }
    return false;
}

void Librarian ::addUser()
{
    string role = chooseRole();
    string name;
    string pass;
    if (role == "1")
    {
        cout << "Enter your name : ";
        cin >> name;
        cout << "\n";
        cout << "Enter password : ";
        cin >> pass;
        cout << "\n";
        Student s1;
        s1.newUser(name, pass);
    }
    else if (role == "2")
    {
        cout << "Enter your name : ";
        cin >> name;
        cout << "\n";
        cout << "Enter password : ";
        cin >> pass;
        cout << "\n";
        Faculty f1;
        f1.newUser(name, pass);
    }
    else if (role == "3")
    {
        cout << "Enter your name : ";
        cin >> name;
        cout << "\n";
        cout << "Enter password : ";
        cin >> pass;
        cout << "\n";
        Librarian l1;
        l1.newUser(name, pass);
    }
    else
    {
        cout << "\nChoose valid Role.\n\n";
    }
    return;
}

void Librarian ::removeUser()
{
    string role = chooseRole();
    if (role == "1")
    {
        cout << "Enter UserId : ";
        int id;
        cin >> id;
        cout << "\n";
        Student s1;
        s1.deleteAccount(id);
    }
    else if (role == "2")
    {
        cout << "Enter UserId : ";
        int id;
        cin >> id;
        cout << "\n";
        Faculty f1;
        f1.deleteAccount(id);
    }
    else if (role == "3")
    {
        cout << "Enter UserId : ";
        int id;
        cin >> id;
        cout << "\n";
        deleteAccount(id);
    }
    else
    {
        cout << "\nChoose valid Role.\n\n";
    }
    return;
}

void Librarian ::deleteAccount(int id)
{
    string filename = "Users/Librarian/user_" + to_string(id) + ".txt";
    if (getUserId() == id)
    {
        cout << "\nYou cannot remove yourself. If you want to delete your account, ask other Librarians.\n\n";
    }
    else
    {
        if (accountExists(id))
        {
            if (remove((filename).c_str()))
            {
                cout << "\nSomething went wrong while deleting filenam4. Librarian.deleteAccount.\n\n";
                return;
            }
            cout << "\nYou have successfully removed the Librarian with UserId : " << to_string(id) << "\n\n";
        }
        else
        {
            cout << "\nUser doesn't exist to remove.\n\n";
        }
    }
}

// Account class definitions:

int Account ::SecPerDay = 86400;

int Account ::getUserId()
{
    return UserId;
}

void Account ::setUserId(int id)
{
    UserId = id;
    return;
}

int Account ::getFine()
{
    return fine;
}

void Account ::updateFine()
{
    if (bookCount)
    {
        int id[bookCount];
        int Time[bookCount];
        string filename = "Users/" + role + "/borrowed_" + to_string(getUserId()) + ".txt";
        ifstream file(filename);
        if (file.is_open())
        {
            for (int i = 0; i < bookCount; i++)
            {
                string temp;
                getline(file, temp);
                id[i] = stoi(temp);
                getline(file, temp);
                Time[i] = stoi(temp);
            }
            file.close();
        }
        else
        {
            cout << "\nSomething went wrong while fetching data. Account.updateFine.\n\n";
            return;
        }
        for (int i = 0; i < bookCount; i++)
        {
            int now = (int)time(0);
            int days = (now - Time[i]) / SecPerDay;
            if (days > timeLimit)
            {
                fine += 10 * (days - timeLimit);
                OverdueDays += (days - timeLimit);
                Time[i] += (days - timeLimit) * SecPerDay;
            }
        }
        ofstream fout(filename);
        if (fout.is_open())
        {
            for (int i = 0; i < bookCount; i++)
            {
                fout << id[i] << "\n"
                     << Time[i] << "\n";
            }
            fout.close();
        }
        else
        {
            cout << "\nSomething went wrong while updating fine. Account.updateFine.\n\n";
            return;
        }
        loadData(getUserId());
    }
    return;
}

void Account ::setFine(int money)
{
    fine = money;
    return;
}

void Account ::fetchData(int id)
{
    string filename = "Users/" + role + "/account_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        string temp;
        getline(file, temp);
        setFine(stoi(temp));
        getline(file, temp);
        OverdueDays = stoi(temp);
        getline(file, temp);
        bookCount = stoi(temp);

        file.close();
    }
    else
    {
        cout << "Something went wrong while fetching account data. Account.fetchData.\n\n";
    }
    return;
}

void Account ::loadData(int id)
{
    string filename = "Users/" + role + "/account_" + to_string(id) + ".txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << getFine() << "\n"
             << OverdueDays << "\n"
             << bookCount;
        file.close();
    }
    else
    {
        cout << "Something went wrong while loading data. Account.loadData.\n\n";
    }
    return;
}

void Account ::loadBorrowedBook(int bookId)
{
    string filename = "Users/" + role + "/borrowed_" + to_string(getUserId()) + ".txt";
    ofstream file(filename, ios::app);
    if (file.is_open())
    {
        int now = (int)time(0);
        file << bookId << "\n"
             << now << "\n";
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while storing borrowed books. Account.loadBorrowedBooks.\n\n";
    }
    return;
}

void Account ::loadBookHistory(int bookId)
{
    string filename = "Users/" + role + "/history_" + to_string(getUserId()) + ".txt";
    ofstream file(filename, ios::app);
    if (file.is_open())
    {
        file << bookId << "\n";
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while storing history. Account.loadBookHistory.\n\n";
    }
}

void Account ::viewBorrowedBooks()
{
    if (bookCount)
    {
        string filename = "Users/" + role + "/borrowed_" + to_string(getUserId()) + ".txt";
        ifstream file(filename);
        if (file.is_open())
        {
            string temp;
            while (getline(file, temp))
            {
                cout << temp << "\n";
                getline(file, temp);
            }
            cout << "\n";
            file.close();
        }
    }
    else
    {
        cout << "\nYou didn't borrow any books at the moment.\n\n";
    }
    return;
}

// Library class definitions

int Library ::getPrevId()
{
    string filename = "Books/id_counter.txt";
    ifstream file(filename);
    int prevId = 100;
    if (file.is_open())
    {
        file >> prevId;
        file.close();
    }
    return prevId;
}

void Library ::updateId()
{
    string filename = "Books/id_counter.txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << Id;
        file.close();
    }
    return;
}

void Library::updateStatustoAvailable(int bookId)
{
    book.fetchData(bookId);
    book.bookStatus = "Available";
    book.loadData(bookId);
    return;
}

void Library ::updateStatustoBorrowed(int bookId)
{
    book.fetchData(bookId);
    book.bookStatus = "Borrowed";
    book.loadData(bookId);
    return;
}

void Library ::addBook()
{
    CreateDirectory("Books", NULL);
    Id = getPrevId();
    string filename = "Books/book_" + to_string(Id) + ".txt";
    book.setId(Id);
    book.bookStatus = "Available";

    cout << "Enter Title of the book : ";
    cin >> book.title;
    cout << "\n";

    cout << "Enter the name of the Author : ";
    cin >> book.author;
    cout << "\n";

    cout << "Enter Publisher : ";
    cin >> book.publisher;
    cout << "\n";

    while(1){
        cout << "Enter published Year : ";
        cin >> book.year;
        cout << "\n";
        try{
            stoi(book.year);
            break;
        }
        catch(...){
            cout << "\nInvalid year. Try again.\n\n";
        }
    }
    
    cout << "Successfully added a new book to the Library. BookId : " << Id << "\n\n";
    book.loadData(Id);
    Id = getPrevId() + 1;
    updateId();
    int tot = book.getTotal();
    book.updateTotal(tot + 1);
    return;
}

void Library ::removeBook()
{
    cout << "Enter bookId : ";
    int id;
    cin >> id;
    cout << "\n";
    string filename = "Books/book_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        book.fetchData(id);
        file.close();
        if (!(book.bookStatus == "Available"))
        {
            cout << "\nThe book is borrowed at the moment. Try again when it is Available in the Library.\n\n";
        }
        else
        {
            if (!remove((filename).c_str()))
            {
                int tot = book.getTotal();
                book.updateTotal(tot - 1);
                cout << "\nSuccessfully removed the book from library.\n\n";
            }
            else
            {
                cout << "\nSomething went wrong while removing book. Library.removeBook.\n\n";
            }
        }
    }
    else
    {
        cout << "\nThe book is not registered in the library.\n\n";
    }
    return;
}

void Library ::viewBooks()
{
    cout << "\n";
    int i = 0;
    int id = 100;
    if (book.getTotal())
    {
        while (i < book.getTotal())
        {
            string filename = "Books/book_" + to_string(id) + ".txt";
            ifstream file(filename);
            if (file.is_open())
            {
                file.close();
                book.fetchData(id);
                cout << "BookId : " + to_string(book.getId()) + " , Title : " + book.title + " , Status : " + book.bookStatus << "\n";
                i++;
            }
            id++;
        }
        cout << "\n";
    }
    else
    {
        cout << "There are no books registered in the Library.\n\n";
    }

    return;
}

// Book class definitions

int Book ::getId()
{
    return bookId;
}

void Book ::setId(int id)
{
    bookId = id;
    return;
}

void Book ::fetchData(int id)
{
    string filename = "Books/book_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        setId(id);
        getline(file, bookStatus);
        getline(file, title);
        getline(file, author);
        getline(file, publisher);
        getline(file, year);
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while fetching book data. Book.fetchData.\n\n";
    }
    return;
}

void Book ::loadData(int id)
{
    string filename = "Books/book_" + to_string(id) + ".txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << bookStatus << "\n"
             << title << "\n"
             << author << "\n"
             << publisher << "\n"
             << year;
        file.close();
    }
    else
    {
        cout << "\nSomething went wrong while storing book data. Book.loadData.\n\n";
    }
    return;
}

bool Book ::bookExists(int id)
{
    string filename = "Books/book_" + to_string(id) + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        file.close();
        return true;
    }
    return false;
}

int Book ::getTotal()
{
    string filename = "Books/book_counter.txt";
    int tot = 0;
    ifstream file(filename);
    if (file.is_open())
    {
        file >> tot;
        file.close();
    }
    return tot;
}

void Book ::updateTotal(int tot)
{
    string filename = "Books/book_counter.txt";
    ofstream file(filename);
    if (file.is_open())
    {
        file << tot;
    }
    else
    {
        cout << "\nSomething went wrong while updating total books. Book.updateTotal.\n\n";
    }
    return;
}
