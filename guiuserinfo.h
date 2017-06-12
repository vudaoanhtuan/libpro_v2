#ifndef GUIUSERINFO_H
#define GUIUSERINFO_H

#include <QMainWindow>
#include "user.h"
#include "datastore.h"
#include <QRegularExpression>
#include <QMessageBox>

namespace Ui {
class GuiUserInfo;
}

class GuiUserInfo : public QMainWindow
{
    Q_OBJECT

public:
    DataStore *data;
    Work work;
    int uId;
    explicit GuiUserInfo(int work, User *user = 0, QWidget *parent = 0);
    ~GuiUserInfo();
    QString checkInput();


signals:
    void addNewUser(User *user);
    void editUser(User *user, int uId);

private slots:
    void on_bOK_clicked();

    void on_bCancel_clicked();

private:
    Ui::GuiUserInfo *ui;
};

#endif // GUIUSERINFO_H
