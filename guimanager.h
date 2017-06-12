#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QMainWindow>
#include "datastore.h"
#include "loginform.h"
#include "guiaccountinfo.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QCloseEvent>
#include <QMessageBox>
#include <QInputDialog>

namespace Ui {
class GuiManager;
}

class GuiManager : public QMainWindow
{
    Q_OBJECT

public:
    DataStore *data;
    explicit GuiManager(int accountId, QWidget *parent = 0);
    ~GuiManager();


    // Init tab
    void initInfoTab();
    void initAccountTab();
    void initUserTab();

    // Function for AccountTab
    void addAccountViewTo(QTreeWidget *view, Account &acc);

    // Function for UserTab
    void addUserViewTo(QTreeWidget *view, User &user);

    // Close event
    void closeEvent(QCloseEvent *event);


private slots:
    void on_bSearchAcc_clicked();

    void on_bRemoveAcc_clicked();

    void on_bAddAcc_clicked();

    void addNewAccount(Account *acc);

    void editAccount(Account *acc, int aId);

    void on_bEditAcc_clicked();

private:
    Ui::GuiManager *ui;
};

#endif // GUIMANAGER_H
