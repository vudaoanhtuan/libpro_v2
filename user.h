#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>
#include <QDebug>


#define USER_FIELDS 6

class User
{
private:
    int uId;
    int uCode;
    QString uName;
    QString uJob;
    QString uEmail;
    QDate uDob;
public:
    User();

    // Default GETTER & SETTER
    int getUId() const;
    void setUId(int value);
    int getUCode() const;
    void setUCode(int value);
    QString getUName() const;
    void setUName(const QString &value);
    QString getUJob() const;
    void setUJob(const QString &value);
    QString getUEmail() const;
    void setUEmail(const QString &value);
    QDate getUDob() const;
    void setUDob(const QDate &value);
};

#endif // USER_H
