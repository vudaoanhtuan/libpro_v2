#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QDate>
#include <QVector>
#include <QDebug>

class Book
{
private:
    int bId;
    QString bTitle;
    QString bAuthor;
    QString bPublisher;
    QString bCategory;
    int bYear;
    int bCount;
public:
    Book();

    // Default GETTER & SETTER
    int getBId() const;
    void setBId(int value);
    QString getBTitle() const;
    void setBTitle(const QString &value);
    QString getBAuthor() const;
    void setBAuthor(const QString &value);
    QString getBPublisher() const;
    void setBPublisher(const QString &value);
    QString getBCategory() const;
    void setBCategory(const QString &value);
    int getBYear() const;
    void setBYear(int value);
    int getBCount() const;
    void setBCount(int value);
};

#endif // BOOK_H
