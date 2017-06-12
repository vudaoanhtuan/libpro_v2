#ifndef DATASTORE_H
#define DATASTORE_H

#include "user.h"
#include "account.h"
#include "book.h"
#include <QVector>
#include <QDebug>
#include <QFile>
#include <QTextStream>

// Define File
#define USER_FILE "data/user.dat"
#define ACCOUNT_FILE "data/account.dat"
#define BOOK_FILE "data/book.dat"
#define INIT_DATA "data/data.ini"
// Define date format
#define DATE_FORMAT "dd/MM/yyyy"
// Define

struct WhoLoging{
    User myUser;
    Account myAccount;
};

enum Work{ADD = 1, EDIT = 2, INFO = 3};

class DataStore
{
public:
    // Data
    QVector<User> users;
    QVector<Account> accounts;
    QVector<Book> books;
    WhoLoging ItsMe;
    int nUser;
    int nAccount;
    int nBook;
    int currentIdUser;
    int currentIdAccount;
    int currentIdBook;

    int nFine;
    // Function

    // Read Data
    int readUser();
    int readAccount();
    int readBook();
    int readInitData();
    void readData();

    // Write Data
    int writeUser();
    int writeAccount();
    int writeBook();
    int writeInitData();
    void writeData();




    // Add new
    void addNewUser(User *user);
    void addNewAccount(Account *acc);
    void addNewBook(Book *book);

    // GETTER
    Account &getAccountByNameRef(QString aName);
    Account &getAccountByIdRef(int aId);
    User &getUserByIdRef(int uId);
    Book &getBookByIdRef(int bId);

    // GET POS
    int getPosBookById(int bId);
    int getPosAccountById(int aId);
    int getPosUserById(int uId);

    bool exitAccountByName(QString aName);
    bool exitAccountById(int aId);
    bool exitUserById(int uId);
    bool exitBookById(int bId);

    // Function for Role
    static bool isReader(Role role);
    static bool isLibrarian(Role role);
    static bool isManager(Role role);
    static Role getRole(bool iR, bool iL, bool iM);

    // Remove
    bool removeAccount(int aId);
    bool removeUser(int uId);




    DataStore();
    ~DataStore();
};

#endif // DATASTORE_H
