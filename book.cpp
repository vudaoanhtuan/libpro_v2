#include "book.h"

int Book::getBId() const
{
    return bId;
}

void Book::setBId(int value)
{
    bId = value;
}

QString Book::getBTitle() const
{
    return bTitle;
}

void Book::setBTitle(const QString &value)
{
    bTitle = value;
}

QString Book::getBAuthor() const
{
    return bAuthor;
}

void Book::setBAuthor(const QString &value)
{
    bAuthor = value;
}

QString Book::getBPublisher() const
{
    return bPublisher;
}

void Book::setBPublisher(const QString &value)
{
    bPublisher = value;
}

QString Book::getBCategory() const
{
    return bCategory;
}

void Book::setBCategory(const QString &value)
{
    bCategory = value;
}

int Book::getBYear() const
{
    return bYear;
}

void Book::setBYear(int value)
{
    bYear = value;
}

int Book::getBCount() const
{
    return bCount;
}

void Book::setBCount(int value)
{
    bCount = value;
}

Book::Book()
{

}

