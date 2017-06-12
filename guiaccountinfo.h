#ifndef GUIACCOUNTINFO_H
#define GUIACCOUNTINFO_H

#include <QMainWindow>
#include "account.h"

namespace Ui {
class guiAccountInfo;
}

class guiAccountInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit guiAccountInfo(int work, Account *acc =0, QWidget *parent = 0);
    ~guiAccountInfo();

signals:
    void addAccount(Account *acc);
    void editAccount(Account *acc, int aId);


private:
    Ui::guiAccountInfo *ui;
};

#endif // GUIACCOUNTINFO_H
