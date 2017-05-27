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
    void addNewUser(User user);
    void addNewAccount(Account acc);
    void addNewBook(Book *book);

    // GETTER
    Account &getAccountByNameRef(QString aName);
    Account &getAccountByIdRef(int aId);
    User &getUserByIdRef(int uId);
    Book &getBookByIdRef(int bId);

    // GET POS
    int getPosBookById(int bId);

    bool exitAccountByName(QString aName);
    bool exitAccountById(int aId);
    bool exitUserById(int uId);
    bool exitBookById(int bId);





    DataStore();
    ~DataStore();
};

#endif // DATASTORE_H
