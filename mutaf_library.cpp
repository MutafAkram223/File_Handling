#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

int mainHeader();
char adminMenu();
int clearScreen();
int addStudent();
int viewAllStudents();
int addStudentIntoArray(string username, float balance);
int addUser(string name, string pass, string role);
int viewStudentBalances();
int addBook();
int editBook();
int deleteBook();
int viewBooksStatus();
int viewBalance(string username);
int depositBalance(string username);
int issueBook(string username);
char studentMenu();
int findStudentIndex(string username);
int findBookIndex(string id);
int findUserIndex(string name);
bool containsDigit(string str);

const int MAX_RECORDS = 100;
const int MAX_BOOKS = 100;

string usernameA[MAX_RECORDS];
string passwordsA[MAX_RECORDS];
string rolesA[MAX_RECORDS];
int userCount = 0;

string student_name[MAX_RECORDS];
float student_balance[MAX_RECORDS];
string student_issuedBook[MAX_RECORDS];
int studentCount = 0;

string bookID[MAX_BOOKS];
string bookName[MAX_BOOKS];
string bookAuthor[MAX_BOOKS];
string bookStatus[MAX_BOOKS];
int bookCount = 0;

int main() {
    addUser("admin", "123", "ADMIN");

    while (true) {
        system("cls");
        mainHeader();
        cout << "1- Admin" << endl;
        cout << "2- Student" << endl;
        cout << "3- Exit" << endl;
        cout << "Choose Your Option: ";
        char mainOption;
        cin >> mainOption;

        if (mainOption == '1') {
            system("cls");
            mainHeader();
            string loginUsername, loginPassword;
            cout << "Enter admin username: ";
            cin >> loginUsername;
            cout << "Enter password: ";
            cin >> loginPassword;

            int userIndex = findUserIndex(loginUsername);
            if (userIndex != -1 && passwordsA[userIndex] == loginPassword && rolesA[userIndex] == "ADMIN") {
                char option = ' ';
                while (true) {
                    system("cls");
                    option = adminMenu();
                    if (option == '1') {
                        system("cls");
                        string newUsername;
                        bool validName = false;
                        while (!validName) {
                            cout << "Enter admin username: ";
                            cin >> newUsername;
                            if (containsDigit(newUsername)) {
                                cout << "Admin name should not contain numbers. Try again." << endl;
                            } else {
                                validName = true;
                            }
                        }

                        int userIndex = findUserIndex(newUsername);
                        if (userIndex != -1) {
                            cout << "Admin of same name already exists." << endl;
                        } else {
                            cout << "Enter password: ";
                            string pass;
                            cin >> pass;

                            addUser(newUsername, pass, "ADMIN");
                            cout << "Admin added successfully!" << endl;
                        }
                        clearScreen();

                    } else if (option == '2') {
                        system("cls");
                        addStudent();

                    } else if (option == '3') {
                        system("cls");
                        addBook();

                    } else if (option == '4') {
                        system("cls");
                        editBook();

                    } else if (option == '5') {
                        system("cls");
                        deleteBook();

                    } else if (option == '6') {
                        system("cls");
                        viewBooksStatus();
                        clearScreen();

                    } else if (option == '7') {
                        system("cls");
                        viewStudentBalances();
                        clearScreen();

                    } else if (option == '8') {
                        break;

                    } else {
                        cout << "You chose an invalid option." << endl;
                        clearScreen();
                    }
                }
            } else {
                cout << "Invalid admin credentials." << endl;
                clearScreen();
            }
        } else if (mainOption == '2') {
            system("cls");
            string loginUsername, loginPassword;
            cout << "Enter student username: ";
            cin >> loginUsername;
            cout << "Enter password: ";
            cin >> loginPassword;

            int userIndex = findUserIndex(loginUsername);
            if (userIndex != -1 && passwordsA[userIndex] == loginPassword && rolesA[userIndex] == "STUDENT") {
                string username = loginUsername;

                char studentOption = ' ';
                while (true) {
                    system("cls");
                    studentOption = studentMenu();
                    if (studentOption == '1') {
                        system("cls");
                        viewBalance(username);
                        clearScreen();

                    } else if (studentOption == '2') {
                        system("cls");
                        depositBalance(username);
                        clearScreen();

                    } else if (studentOption == '3') {
                        system("cls");
                        issueBook(username);
                        clearScreen();

                    } else if (studentOption == '4') {
                        break;

                    } else {
                        cout << "Wrong selection! Try again." << endl;
                        clearScreen();
                    }
                }
            } else {
                cout << "Invalid student credentials." << endl;
                clearScreen();
            }
        } else if (mainOption == '3') {
            cout << "Exiting the program." << endl;
            break;
        } else {
            cout << "Invalid option. Please choose again." << endl;
            clearScreen();
        }
    }

    return 0;
}

int mainHeader() {
    cout << "----------------------------------------------" << endl;
    cout << "---          Library Management System     ---" << endl;
    cout << "----------------------------------------------" << endl;
    return 0;
}

char adminMenu() {
    mainHeader();
    cout << "Admin Main Menu > " << endl;
    cout << "1- Add Admin " << endl;
    cout << "2- Add Student" << endl;
    cout << "3- Add Books" << endl;
    cout << "4- Edit Books" << endl;
    cout << "5- Delete Books" << endl;
    cout << "6- View Books Status" << endl;
    cout << "7- View Student Balance" << endl;
    cout << "8- Logout " << endl;
    cout << "Choose Your Option: ";
    char option;
    cin >> option;
    return option;
}

char studentMenu() {
    mainHeader();
    cout << "Student Main Menu > " << endl;
    cout << "1- View Balance " << endl;
    cout << "2- Deposit Balance " << endl;
    cout << "3- Issue Book " << endl;
    cout << "4- Logout " << endl;
    cout << "Choose Your Option: ";
    char option;
    cin >> option;
    return option;
}

int clearScreen() {
    cout << "Press any key to continue..." << endl;
    getch();
    system("cls");
    return 1;
}

int addUser(string name, string pass, string role) {
    if (userCount >= MAX_RECORDS) {
        cout << "Cannot add more users. Maximum capacity reached." << endl;
        return 0;
    }
    if (findUserIndex(name) != -1) {
        cout << "User already exists." << endl;
        return 0;
    }

    usernameA[userCount] = name;
    passwordsA[userCount] = pass;
    rolesA[userCount] = role;
    userCount++;
    return 1;
}

int findUserIndex(string name) {
    for (int i = 0; i < userCount; i++) {
        if (usernameA[i] == name) {
            return i;
        }
    }
    return -1;
}

int addStudent() {
    string username;
    bool validName = false;
    while (!validName) {
        cout << "Enter student username: ";
        cin >> username;
        if (containsDigit(username)) {
            cout << "Student name should not contain numbers. Please try again." << endl;
        } else {
            validName = true;
        }
    }

    int userIndex = findUserIndex(username);
    if (userIndex != -1) {
        cout << "Same name already exists." << endl;
        clearScreen();
        return 0;
    }

    string pass;
    cout << "Enter student password: ";
    cin >> pass;
    
    float balance;
    cout << "Enter initial balance: ";
    cin >> balance;

    if (!addStudentIntoArray(username, balance)) {
        cout << "Failed to add student into array." << endl;
        return 0;
    }
    if (!addUser(username, pass, "STUDENT")) {
        cout << "Failed to add user." << endl;
        return 0;
    }

    cout << "Student added successfully!" << endl;
    clearScreen();
    return 1;
}

int addStudentIntoArray(string username, float balance) {
    if (studentCount >= MAX_RECORDS) {
        cout << "Cannot add more students. Maximum capacity reached." << endl;
        return 0;
    }
    student_name[studentCount] = username;
    student_balance[studentCount] = balance;
    student_issuedBook[studentCount] = "";
    studentCount++;
    return 1;
}

int viewStudentBalances() {
    cout << "Username\tBalance" << endl;
    for (int i = 0; i < studentCount; i++) {
        cout << student_name[i] << "\t\t" << student_balance[i] << endl;
    }
    return 1;
}

int addBook() {
    if (bookCount >= MAX_BOOKS) {
        cout << "Cannot add more books. Maximum capacity reached." << endl;
        return 0;
    }
    cout << "Enter Book ID: ";
    string id;
    cin >> id;
    cin.get();

    if (findBookIndex(id) != -1) {
        cout << "Book with this ID already exists." << endl;
        clearScreen();
        return 0;
    }

    string name;
    bool validName = false;
    while (!validName) {
        cout << "Enter Book Name: ";
        getline(cin, name);
        if (containsDigit(name)) {
            cout << "Book name should not contain numbers. Please try again." << endl;
        } else {
            validName = true;
        }
    }

    string author;
    bool validAuthor = false;
    while (!validAuthor) {
        cout << "Enter Author Name: ";
        getline(cin, author);
        if (containsDigit(author)) {
            cout << "Author name should not contain numbers. Please try again." << endl;
        } else {
            validAuthor = true;
        }
    }

    bookID[bookCount] = id;
    bookName[bookCount] = name;
    bookAuthor[bookCount] = author;
    bookStatus[bookCount] = "Available";
    bookCount++;

    cout << "Book added successfully!" << endl;
    clearScreen();
    return 1;
}

int editBook() {
    cout << "Enter Book ID to edit: ";
    string id;
    cin >> id;
    cin.get();

    int index = findBookIndex(id);
    if (index == -1) {
        cout << "Book not found." << endl;
        clearScreen();
        return 0;
    }

    string name;
    bool validName = false;
    while (!validName) {
        cout << "Enter new Book Name: ";
        getline(cin, name);
        if (containsDigit(name)) {
            cout << "Book name should not contain numbers. Please try again." << endl;
        } else {
            validName = true;
        }
    }

    string author;
    bool validAuthor = false;
    while (!validAuthor) {
        cout << "Enter new Author Name: ";
        getline(cin, author);
        if (containsDigit(author)) {
            cout << "Author name should not contain numbers. Please try again." << endl;
        } else {
            validAuthor = true;
        }
    }

    bookName[index] = name;
    bookAuthor[index] = author;
    cout << "Book updated successfully." << endl;
    clearScreen();
    return 1;
}

int deleteBook() {
    cout << "Enter Book ID to delete: ";
    string id;
    cin >> id;

    int index = findBookIndex(id);
    if (index == -1) {
        cout << "Book not found." << endl;
        clearScreen();
        return 0;
    }

    if (bookStatus[index] == "Issued") {
        cout << "Cannot delete an issued book." << endl;
        clearScreen();
        return 0;
    }

    for (int i = index; i < bookCount - 1; i++) {
        bookID[i] = bookID[i + 1];
        bookName[i] = bookName[i + 1];
        bookAuthor[i] = bookAuthor[i + 1];
        bookStatus[i] = bookStatus[i + 1];
    }
    bookCount--;

    cout << "Book deleted successfully." << endl;
    clearScreen();
    return 1;
}

int viewBooksStatus() {
    cout << "Book ID\tBook Name\tAuthor Name\tStatus" << endl;
    for (int i = 0; i < bookCount; i++) {
        cout << bookID[i] << "\t" << bookName[i] << "\t" << bookAuthor[i] << "\t" << bookStatus[i] << endl;
    }
    return 1;
}

int viewBalance(string username) {
    int index = findStudentIndex(username);
    if (index == -1) {
        cout << "Student not found." << endl;
        return 0;
    }
    cout << "Your balance is: " << student_balance[index] << endl;
    return 1;
}

int depositBalance(string username) {
    int index = findStudentIndex(username);
    if (index == -1) {
        cout << "Student not found." << endl;
        return 0;
    }
    cout << "Enter amount to deposit: ";
    float amount;
    cin >> amount;
    if (amount <= 0) {
        cout << "Invalid amount." << endl;
        return 0;
    }
    student_balance[index] += amount;
    cout << "Amount deposited successfully. New balance: " << student_balance[index] << endl;
    return 1;
}

int issueBook(string username) {
    int studentIndex = findStudentIndex(username);
    if (studentIndex == -1) {
        cout << "Student not found." << endl;
        return 0;
    }
    if (student_issuedBook[studentIndex] != "") {
        cout << "You have already issued a book: " << student_issuedBook[studentIndex] << endl;
        return 0;
    }
    cout << "Available books: " << endl;
    for (int i = 0; i < bookCount; i++) {
        if (bookStatus[i] == "Available") {
            cout << bookID[i] << "\t" << bookName[i] << "\t" << bookAuthor[i] << endl;
        }
    }
    cout << "Enter Book ID to issue: ";
    string id;
    cin >> id;
    int bookIndex = findBookIndex(id);
    if (bookIndex == -1 || bookStatus[bookIndex] != "Available") {
        cout << "Book not found or not available." << endl;
        return 0;
    }
    float issueCost = 10.0;
    if (student_balance[studentIndex] < issueCost) {
        cout << "Insufficient balance to issue book. Please deposit funds." << endl;
        return 0;
    }
    student_balance[studentIndex] -= issueCost;
    student_issuedBook[studentIndex] = bookID[bookIndex];
    bookStatus[bookIndex] = "Issued";
    cout << "Book issued successfully. Remaining balance: " << student_balance[studentIndex] << endl;
    return 1;
}

int findStudentIndex(string username) {
    for (int i = 0; i < studentCount; i++) {
        if (student_name[i] == username) {
            return i;
        }
    }
    return -1;
}

int findBookIndex(string id) {
    for (int i = 0; i < bookCount; i++) {
        if (bookID[i] == id) {
            return i;
        }
    }
    return -1;
}

bool containsDigit(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            return true;
        }
    }
    return false;
}