#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QMainWindow>
#include "datastore.h"
#include "loginform.h"
#include "guiaccountinfo.h"
#include "guiuserinfo.h"
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

    void on_bSearchUser_clicked();

    void on_bRemoveUser_clicked();

    void on_bAddUser_clicked();

    void addNewUser(User *user);

    void editUser(User *user, int uId);

    void on_bEditUser_clicked();

    void on_butChangePassword_clicked();

    void on_bLogout1_clicked();

    void on_bLogout2_clicked();

    void on_butLogout3_clicked();

    void on_bQuit1_clicked();

    void on_bQuit2_clicked();

    void on_butQuit3_clicked();

    void on_listUser_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_listAccount_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::GuiManager *ui;
};

#endif // GUIMANAGER_H
