#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QDate>
#include <QVector>
#include <QDebug>

#define MAX_BOOK 3
#define MAX_DAY 14

struct BookBorrow{
    int bookId;
    QDate dayBorrow;
};

enum Role{rREADER, rLIBRARIAN, rMANAGER};

class Account
{
private:
    int aId;
    int userId;
    QString aName;
    QString aPass;
    Role aRole;
    bool aStatus;
    int nBorrow;
    int nRequest;
public:
    QVector<BookBorrow> borrows;
    QVector<int> requests;
    Account();

    // Default GETTER & SETTER
    int getAId() const;
    void setAId(int value);
    int getUserId() const;
    void setUserId(int value);
    QString getAName() const;
    void setAName(const QString &value);
    QString getAPass() const;
    void setAPass(const QString &value);
    bool getAStatus() const;
    void setAStatus(bool value);
    int getNBorrow() const;
    void setNBorrow(int value);
    int getNRequest() const;
    void setNRequest(int value);
    Role getARole() const;
    void setARole(const Role &value);

    // New GETTER
    QVector<BookBorrow> getListBorrows();
    QVector<int> getListRequest();
    int requestBook(int bookId);
    int removeRequest(int bookId);
    int borrowBook(int bookId);
    int removeBorrow(int bookId);

};

#endif // ACCOUNT_H
