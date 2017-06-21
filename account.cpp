#include "account.h"

int Account::getAId() const
{
    return aId;
}

void Account::setAId(int value)
{
    aId = value;
}

int Account::getUserId() const
{
    return userId;
}

void Account::setUserId(int value)
{
    userId = value;
}

QString Account::getAName() const
{
    return aName;
}

void Account::setAName(const QString &value)
{
    aName = value;
}

QString Account::getAPass() const
{
    return aPass;
}

void Account::setAPass(const QString &value)
{
    aPass = value;
}

bool Account::getAStatus() const
{
    return aStatus;
}

void Account::setAStatus(bool value)
{
    aStatus = value;
}

int Account::getNBorrow() const
{
    return nBorrow;
}

void Account::setNBorrow(int value)
{
    nBorrow = value;
}

int Account::getNRequest() const
{
    return nRequest;
}

void Account::setNRequest(int value)
{
    nRequest = value;
}

Role Account::getARole() const
{
    return aRole;
}

void Account::setARole(const Role &value)
{
    aRole = value;
}

QVector<BookBorrow> Account::getListBorrows()
{
    return borrows;
}

QVector<int> Account::getListRequest()
{
    return requests;
}

QVector<int> Account::getListHistories()
{
    return histories;
}

int Account::requestBook(int bookId)
{
    if (nBorrow + nRequest >= MAX_BOOK)
        return 1;
    nRequest++;
    requests.push_back(bookId);
    return 0;
}

int Account::removeRequest(int bookId)
{
    int id = -1;
    for (int i=0;i<nRequest;i++)
        if (requests[i] == bookId){
            id = i;
            break;
        }
    if (id == -1){
        return 1;
    }
    nRequest--;
    requests.remove(id);
    return 0;
}

int Account::borrowBook(int bookId)
{
    if (nBorrow >= MAX_BOOK)
        return 1;
    BookBorrow newBook;
    newBook.dayBorrow = QDate::currentDate();
    newBook.bookId = bookId;
    nBorrow++;
    borrows.push_back(newBook);
    return 0;
}

int Account::removeBorrow(int bookId)
{
    int id = -1;
    for (int i=0;i<nBorrow;i++)
        if (borrows[i].bookId == bookId){
            id = i;
            break;
        }
    if (id == -1){
        return 1;
    }
    nBorrow--;
    borrows.remove(id);
    return 0;
}

int Account::getNHistory() const
{
    return nHistory;
}

void Account::setNHistory(int value)
{
    nHistory = value;
}

Account::Account()
{
    
}

