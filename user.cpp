#include "user.h"

int User::getUId() const
{
    return uId;
}

void User::setUId(int value)
{
    uId = value;
}

int User::getUCode() const
{
    return uCode;
}

void User::setUCode(int value)
{
    uCode = value;
}

QString User::getUName() const
{
    return uName;
}

void User::setUName(const QString &value)
{
    uName = value;
}

QString User::getUJob() const
{
    return uJob;
}

void User::setUJob(const QString &value)
{
    uJob = value;
}

QString User::getUEmail() const
{
    return uEmail;
}

void User::setUEmail(const QString &value)
{
    uEmail = value;
}

QDate User::getUDob() const
{
    return uDob;
}

void User::setUDob(const QDate &value)
{
    uDob = value;
}

User::User()
{
    
}

