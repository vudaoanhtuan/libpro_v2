#include "datastore.h"

int DataStore::writeUser()
{
    QFile file(USER_FILE);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << " Could not open file " << USER_FILE;
        return 1;
    }
    QTextStream output(&file);
    for (int i=0; i<nUser; i++){
        output << users[i].getUId() << endl;
        output << users[i].getUCode() << endl;
        output << users[i].getUName() << endl;
        output << users[i].getUJob() << endl;
        output << users[i].getUEmail() << endl;
        output << users[i].getUDob().toString(DATE_FORMAT) << endl;
    }
    file.flush();
    file.close();
    return 0;
}

int DataStore::writeAccount()
{
    QFile file(ACCOUNT_FILE);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << " Could not open file " << ACCOUNT_FILE;
        return 1;
    }
    QTextStream output(&file);
    for (int i=0; i<nAccount; i++){
        output << accounts[i].getAId() << endl;
        output << accounts[i].getUserId() << endl;
        output << accounts[i].getAName() << endl;
        output << accounts[i].getAPass() << endl;
        output << accounts[i].getARole() << endl;
        output << accounts[i].getAStatus() << endl;

        output << accounts[i].getNBorrow() << " ";
        QVector<BookBorrow> bookBors = accounts[i].getListBorrows();
        for (int ib=0; ib<bookBors.size(); ib++){
            output << bookBors[ib].bookId << " " << bookBors[ib].dayBorrow.toString(DATE_FORMAT)<< " ";
        }
        output << endl;

        output << accounts[i].getNRequest() << " ";
        QVector<int> bookReqs = accounts[i].getListRequest();
        for (int ir=0; ir<bookReqs.size(); ir++){
            output << bookReqs[ir] << " ";
        }
        output << endl;
    }
    file.flush();
    file.close();
    return 0;
}

int DataStore::writeBook()
{
    QFile file(BOOK_FILE);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << " Could not open file " << BOOK_FILE;
        return 1;
    }
    QTextStream output(&file);
    for (int i=0; i<nBook; i++){
        output << books[i].getBId() << endl;
        output << books[i].getBTitle() << endl;
        output << books[i].getBAuthor() << endl;
        output << books[i].getBPublisher() << endl;
        output << books[i].getBCategory() << endl;
        output << books[i].getBYear() << endl;
        output << books[i].getBCount() << endl;
    }
    file.flush();
    file.close();
    return 0;
}

int DataStore::writeInitData()
{
    QFile file(INIT_DATA);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << " Could not open file " << INIT_DATA;
        return 1;
    }
    QTextStream output(&file);
    output << nUser << " ";
    output << nAccount << " ";
    output << nBook << " ";
    output << currentIdUser << " ";
    output << currentIdAccount << " ";
    output << currentIdBook << " ";
    output << nFine;

    file.flush();
    file.close();
    return 0;
}

void DataStore::writeData()
{
    writeInitData();
    writeUser();
    writeAccount();
    writeBook();
}

void DataStore::addNewBook(Book *book)
{
    currentIdBook++;
    nBook++;
    book->setBId(currentIdBook);
    book->setBCount(10);
    books.push_back(*book);
    qDebug() << book->getBTitle();
    qDebug() << "Book added";
}

Account &DataStore::getAccountByNameRef(QString aName)
{
    for (int i=0;i<nAccount; i++){
        if (accounts[i].getAName() == aName)
            return accounts[i];
    }
    Account nullAccount;
    return nullAccount;
}

Account &DataStore::getAccountByIdRef(int aId)
{
    for (int i=0;i<nAccount;i++)
        if (accounts[i].getAId() == aId)
            return accounts[i];
    Account nullAccount;
    return nullAccount;
}

User &DataStore::getUserByIdRef(int uId)
{
    for (int i=0;i<nUser;i++)
        if (users[i].getUId() == uId)
            return users[i];
    User nullUser;
    return nullUser;
}

Book &DataStore::getBookByIdRef(int bId)
{
    for (int i=0;i<nBook;i++)
        if (books[i].getBId() == bId)
            return books[i];
    Book nullBook;
    return nullBook;
}

int DataStore::getPosBookById(int bId)
{
    for (int i=0;i<nBook;i++)
        if (books[i].getBId() == bId)
            return i;
    return -1;
}

bool DataStore::exitAccountByName(QString aName)
{
    for (int i=0;i<nAccount;i++)
        if (accounts[i].getAName() == aName)
            return 1;
    return 0;
}

bool DataStore::exitAccountById(int aId)
{
    for (int i=0;i<nAccount;i++)
        if (accounts[i].getAId() == aId)
            return 1;
    return 0;
}

bool DataStore::exitUserById(int uId)
{
    for (int i=0;i<nUser;i++)
        if (users[i].getUId() == uId)
            return 1;
    return 0;
}

bool DataStore::exitBookById(int bId)
{
    for (int i=0;i<nBook;i++)
        if (books[i].getBId() == bId)
            return 1;
    return 0;
}

int DataStore::readUser()
{
    QFile file(USER_FILE);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << " Could not open the file " << USER_FILE;
        return 1;
    }
    QTextStream input(&file);

    for (int i=0 ; i<nUser; i++){
        User nUser;
        QString curLine;

        curLine = input.readLine();
        nUser.setUId(curLine.toInt());

        curLine = input.readLine();
        nUser.setUCode(curLine.toInt());

        curLine = input.readLine();
        nUser.setUName(curLine);

        curLine = input.readLine();
        nUser.setUJob(curLine);

        curLine = input.readLine();
        nUser.setUEmail(curLine);

        curLine = input.readLine();
        QDate date = QDate::fromString(curLine, DATE_FORMAT);
        nUser.setUDob(date);

        users.push_back(nUser);
    }
    file.close();
    return 0;
}

int DataStore::readAccount()
{
    QFile file(ACCOUNT_FILE);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << " Could not open the file " << ACCOUNT_FILE;
        return 1;
    }
    QTextStream input(&file);

    for (int i=0;i<nAccount; i++){
        Account nAcc;
        QString cLine;

        cLine = input.readLine();
        nAcc.setAId(cLine.toInt());

        cLine = input.readLine();
        nAcc.setUserId(cLine.toInt());

        cLine = input.readLine();
        nAcc.setAName(cLine);

        cLine = input.readLine();
        nAcc.setAPass(cLine);

        cLine = input.readLine();
        nAcc.setARole((Role)cLine.toInt());

        cLine = input.readLine();
        nAcc.setAStatus((bool)cLine.toInt());

        cLine = input.readLine();
        QTextStream strBor(&cLine);
        int nBor;
        strBor >> nBor;
        nAcc.setNBorrow(nBor);
        for (int ib=0; ib<nBor; ib++){
            BookBorrow nBook;
            QString day;
            strBor >> nBook.bookId >> day;
            nBook.dayBorrow = QDate::fromString(day, DATE_FORMAT);
            nAcc.borrows.push_back(nBook);
        }

        cLine = input.readLine();
        QTextStream strReq(&cLine);
        int nReq;
        strReq >> nReq;
        nAcc.setNRequest(nReq);
        for (int ir=0; ir<nReq; ir++){
            int bookId;
            strReq >> bookId;
            nAcc.requests.push_back(bookId);
        }

        accounts.push_back(nAcc);
    }
    file.close();
    return 0;
}

int DataStore::readBook()
{
    QFile file(BOOK_FILE);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << " Could not open the file " << BOOK_FILE;
        return 1;
    }
    QTextStream input(&file);

    for (int i=0; i<nBook; i++){
        Book nBook;
        QString cLine;

        cLine = input.readLine();
        nBook.setBId(cLine.toInt());

        cLine = input.readLine();
        nBook.setBTitle(cLine);

        cLine = input.readLine();
        nBook.setBAuthor(cLine);

        cLine = input.readLine();
        nBook.setBPublisher(cLine);

        cLine = input.readLine();
        nBook.setBCategory(cLine);

        cLine = input.readLine();
        nBook.setBYear(cLine.toInt());

        cLine = input.readLine();
        nBook.setBCount(cLine.toInt());

        books.push_back(nBook);
    }
    file.close();
    return 0;
}

int DataStore::readInitData()
{
    QFile file(INIT_DATA);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << " Could not open the file " << INIT_DATA;
        return 1;
    }
    QTextStream input(&file);

    input >> nUser >> nAccount >> nBook >> currentIdUser >> currentIdAccount >> currentIdBook;
    input >> nFine;
    file.close();
    return 0;
}

void DataStore::readData()
{
    readInitData();
    readUser();
    readAccount();
    readBook();
}


DataStore::DataStore()
{
    readData();
}

DataStore::~DataStore()
{
    writeData();
    qDebug() << "Data saved!";
}

