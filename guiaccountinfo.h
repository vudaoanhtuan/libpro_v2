#ifndef GUIACCOUNTINFO_H
#define GUIACCOUNTINFO_H

#include <QMainWindow>
#include "account.h"
#include "datastore.h"
#include <QMessageBox>

enum Work{ADD = 1, EDIT = 2};

namespace Ui {
class guiAccountInfo;
}

class guiAccountInfo : public QMainWindow
{
    Q_OBJECT

public:
    Work work;
    int aId;
    explicit guiAccountInfo(int work, Account *acc =0, QWidget *parent = 0);
    ~guiAccountInfo();

signals:
    void addAccount(Account *acc);
    void editAccount(Account *acc, int aId);


private slots:
    void on_bOk_clicked();

    void on_bCancel_clicked();

    void on_bReset_clicked();

private:
    Ui::guiAccountInfo *ui;
};

#endif // GUIACCOUNTINFO_H
