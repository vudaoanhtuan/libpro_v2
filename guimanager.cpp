#include "guimanager.h"
#include "ui_guimanager.h"

GuiManager::GuiManager(int accountId, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiManager)
{
    data = new DataStore;

    data->ItsMe.myAccount = data->getAccountByIdRef(accountId);
    data->ItsMe.myUser = data->getUserByIdRef(data->ItsMe.myAccount.getUserId());
    ui->setupUi(this);

    // Set location and default for tab
    setWindowTitle("Libpro - " + data->ItsMe.myAccount.getAName()+ " (Manager)");
    setMinimumSize(810,500);
    this->move(QApplication::desktop()->screen()->rect().center()-this->rect().center());

    // Init tab;
    initInfoTab();
    initAccountTab();
    initUserTab();
//    initStatusTab();
    // Set defaul tab;
    ui->tabWidget->setCurrentIndex(0);
}

GuiManager::~GuiManager()
{
    delete ui;
}

void GuiManager::initInfoTab()
{
    Account &a = data->ItsMe.myAccount;
    User &u = data->ItsMe.myUser;
    ui->lAccount->setText("Account: " + a.getAName());
    ui->lDoB->setText("Birth Day: " + u.getUDob().toString(DATE_FORMAT));
    ui->lEmail->setText("Email: " + u.getUEmail());
    ui->lFullName->setText("Full Name: " + u.getUName());
    ui->lJob->setText("Job: " + u.getUJob());
    ui->lRole->setText("Role: Manager");
    ui->lStatus->setText("Status: Active");
}

void GuiManager::initAccountTab()
{
    ui->listAccount->clear();
    ui->listAccount->setColumnWidth(2,150);
    ui->listAccount->setColumnWidth(3, 200);

    ui->listAccount->hideColumn(0);
    for (int i=0; i<data->nAccount; i++){
        Account &curAcc = data->accounts[i];
        addAccountViewTo(ui->listAccount, curAcc);
    }
}

void GuiManager::initUserTab()
{
    ui->listUser->clear();
    ui->listUser->setColumnWidth(2, 200);

    ui->listUser->hideColumn(0);
    for (int iu=0;iu<data->nUser;iu++){
        User &user = data->users[iu];
        addUserViewTo(ui->listUser, user);
    }
}

void GuiManager::addAccountViewTo(QTreeWidget *view, Account &acc)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(view);
    item->setText(1, QString::number(acc.getAId()));
    item->setText(2, acc.getAName());
    User &user = data->getUserByIdRef(acc.getUserId());
    item->setText(3, user.getUName());
    QString strRole = "";
    Role role = acc.getARole();
    if (data->isReader(role))
        strRole = strRole + "R ";
    if (data->isLibrarian(role))
        strRole = strRole + "L ";
    if (data->isManager(role))
        strRole = strRole + "M ";
    item->setText(4, strRole);
    if (acc.getAStatus() == 0){
        for (int i=1;i<5;i++)
            item->setBackgroundColor(i, QColor::fromRgb(155, 158, 163));
    }
}

void GuiManager::addUserViewTo(QTreeWidget *view, User &user)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(view);
    item->setText(1, QString::number(user.getUId()));
    item->setText(2, user.getUName());
    item->setText(3, QString::number(user.getUCode()));
    item->setText(4, user.getUEmail());
}

void GuiManager::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "LibPro",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Yes | QMessageBox::No,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        delete data;
        delete this;
    }
}

void GuiManager::on_bSearchAcc_clicked()
{
    int searchBy = ui->searchAccBy->currentIndex();
    QString key = ui->searchAccInput->text();

    ui->listAccount->clear();

    // Search by account id -> 0
    if (searchBy == 0){
        for (int ia=0; ia<data->nAccount; ia++){
            Account &curAcc = data->accounts[ia];
            QString strId = QString::number(curAcc.getAId());
            if (strId.contains(key))
                addAccountViewTo(ui->listAccount, curAcc);
        }
    }

    // Search by account name -> 1
    if (searchBy == 1){
        for (int ia=0; ia<data->nAccount; ia++){
            Account &curAcc = data->accounts[ia];
            QString str = curAcc.getAName();
            if (str.contains(key, Qt::CaseInsensitive))
                addAccountViewTo(ui->listAccount, curAcc);
        }
    }

    // Search by user name
    if (searchBy == 2){
        for (int ia=0; ia<data->nAccount; ia++){
            Account &curAcc = data->accounts[ia];
            User &user = data->getUserByIdRef(curAcc.getUserId());
            QString str = user.getUName();
            if (str.contains(key, Qt::CaseInsensitive))
                addAccountViewTo(ui->listAccount, curAcc);
        }
    }
}

void GuiManager::on_bRemoveAcc_clicked()
{
    if (ui->listAccount->currentItem() ==0)
        return;
    int aId = ui->listAccount->currentItem()->text(1).toInt();
    Account &curAcc = data->getAccountByIdRef(aId);
    if (curAcc.getNBorrow() > 0){
        QMessageBox::information(this, "Error!", "This account is borrowing some book!");
        qDebug() << "Can't delete Account";
        return;
    }
    else{
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, "LibPro",
                                                                    tr("Are you sure?\n"),
                                                                    QMessageBox::Yes | QMessageBox::No,
                                                                    QMessageBox::Yes);

        if (resBtn == QMessageBox::Yes){
            data->removeAccount(aId);
            delete ui->listAccount->currentItem();
        }
    }
}

void GuiManager::on_bAddAcc_clicked()
{
    guiAccountInfo *guiAccInfo =  new guiAccountInfo(1);
    guiAccInfo->setWindowTitle("Add New Account");
    guiAccInfo->move(QApplication::desktop()->screen()->rect().center()-this->rect().center());
    connect(guiAccInfo, SIGNAL(addAccount(Account*)), this, SLOT(addNewAccount(Account*)));
    guiAccInfo->show();
}

void GuiManager::addNewAccount(Account *acc)
{
    data->addNewAccount(acc);
    initAccountTab();
}

void GuiManager::editAccount(Account *acc, int aId)
{
    qDebug()<<aId;
    qDebug()<<(int)acc->getARole();
    Account &curAcc = data->getAccountByIdRef(aId);
    curAcc.setARole(acc->getARole());
    curAcc.setAStatus(acc->getAStatus());
    curAcc.setUserId(acc->getUserId());
    curAcc.setAPass(acc->getAPass());

    initAccountTab();
}

void GuiManager::on_bEditAcc_clicked()
{
    if (ui->listAccount->currentItem() == 0)
        return;

    int aId = ui->listAccount->currentItem()->text(1).toInt();
    Account &curAcc = data->getAccountByIdRef(aId);

    guiAccountInfo *editAccGui = new guiAccountInfo(2, &curAcc);

    editAccGui->setWindowTitle("Edit Account");
    editAccGui->move(QApplication::desktop()->screen()->rect().center()-this->rect().center());
    connect(editAccGui, SIGNAL(editAccount(Account*,int)), this, SLOT(editAccount(Account*,int)));
    editAccGui->show();
}

void GuiManager::on_bSearchUser_clicked()
{
    ui->listUser->clear();
    QString key = ui->searchUserInput->text();
    int searchBy = ui->searchUserBy->currentIndex();

    // 0. User Id
    if (searchBy == 0){
        for (int iu=0;iu<data->nUser;iu++){
            User user = data->users[iu];
            QString str = QString::number(user.getUId());
            if (str.contains(key, Qt::CaseInsensitive))
                addUserViewTo(ui->listUser,user);
        }
    }

    // 1. User Name
    if (searchBy == 1){
        for (int iu=0;iu<data->nUser;iu++){
            User user = data->users[iu];
            QString str = user.getUName();
            if (str.contains(key, Qt::CaseInsensitive))
                addUserViewTo(ui->listUser,user);
        }
    }

    // 2. User Code
    if (searchBy == 2){
        for (int iu=0;iu<data->nUser;iu++){
            User user = data->users[iu];
            QString str = QString::number(user.getUCode());
            if (str.contains(key, Qt::CaseInsensitive))
                addUserViewTo(ui->listUser,user);
        }
    }

    // 3. User Email
    if (searchBy == 3){
        for (int iu=0;iu<data->nUser;iu++){
            User user = data->users[iu];
            QString str = user.getUEmail();
            if (str.contains(key, Qt::CaseInsensitive))
                addUserViewTo(ui->listUser,user);
        }
    }
}

void GuiManager::on_bRemoveUser_clicked()
{
    if (ui->listUser->currentItem() == 0)
        return;

    int uId = ui->listUser->currentItem()->text(1).toInt();

    // Check user link to account
    bool linked = 0;
    for (int i=0;i<data->nAccount;i++){
        Account &acc = data->accounts[i];
        if (acc.getUserId() == uId){
            linked = 1;
            break;
        }
    }
    if (linked){
        QMessageBox::information(this, "Error!", "This user is linked to some account!");
    }
    else{
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, "LibPro",
                                                                    tr("Are you sure?\n"),
                                                                    QMessageBox::Yes | QMessageBox::No,
                                                                    QMessageBox::Yes);

        if (resBtn == QMessageBox::Yes){
            data->removeUser(uId);
            delete ui->listUser->currentItem();
        }
    }
}

void GuiManager::on_bAddUser_clicked()
{
    GuiUserInfo *guiUserInfo =  new GuiUserInfo(1);
    guiUserInfo->setWindowTitle("Add New User");
    guiUserInfo->move(QApplication::desktop()->screen()->rect().center()-this->rect().center());
    connect(guiUserInfo, SIGNAL(addNewUser(User*)), this, SLOT(addNewUser(User*)));
    guiUserInfo->show();
}

void GuiManager::addNewUser(User *user)
{
    data->addNewUser(user);
    initUserTab();
}

void GuiManager::editUser(User *user, int uId)
{
    User &userOrigin = data->getUserByIdRef(uId);
    userOrigin.setUCode(user->getUCode());
    userOrigin.setUDob(user->getUDob());
    userOrigin.setUEmail(user->getUEmail());
    userOrigin.setUJob(user->getUJob());
    userOrigin.setUName(user->getUName());
    initUserTab();
}

void GuiManager::on_bEditUser_clicked()
{
    if (ui->listUser->currentItem() == 0)
        return;

    int uId = ui->listUser->currentItem()->text(1).toInt();
    User &user = data->getUserByIdRef(uId);

    GuiUserInfo *guiUserInfo =  new GuiUserInfo(2, &user);
    guiUserInfo->setWindowTitle("Edit User");
    guiUserInfo->move(QApplication::desktop()->screen()->rect().center()-this->rect().center());
    connect(guiUserInfo, SIGNAL(editUser(User*,int)), this, SLOT(editUser(User*,int)));
    guiUserInfo->show();

}

void GuiManager::on_butChangePassword_clicked()
{
    QString curPass = QInputDialog::getText(0,"Change Password","Current Password",QLineEdit::Normal,"",0);
    if (curPass == "")
        return;
    Account &a = data->getAccountByIdRef(data->ItsMe.myAccount.getAId());
    if (a.getAPass() == curPass){
        QString newPass = QInputDialog::getText(0,"Change Password","New Password",QLineEdit::Normal,"",0);
        if (newPass=="")
            return;
        QString configNewPass = QInputDialog::getText(0,"Change Password","Confirm new Password",QLineEdit::Normal,"",0);
        if (newPass == configNewPass){
            a.setAPass(newPass);
            QMessageBox::information(this, "Done!", "Password changed!");
        }
        else{
            QMessageBox::information(
                this,
                tr("Error!"),
                tr("Wrong confirm password!") );
        }
    }
    else{
        QMessageBox::information(this, tr("Error!"), tr("Wrong password!"));
    }
}

void GuiManager::on_bLogout1_clicked()
{
    if (this->close()){
         LoginForm *loginForm = new LoginForm();
         loginForm->show();
    }
}

void GuiManager::on_bLogout2_clicked()
{
    if (this->close()){
         LoginForm *loginForm = new LoginForm();
         loginForm->show();
    }
}

void GuiManager::on_butLogout3_clicked()
{
    if (this->close()){
         LoginForm *loginForm = new LoginForm();
         loginForm->show();
    }
}

void GuiManager::on_bQuit1_clicked()
{
    this->close();
}

void GuiManager::on_bQuit2_clicked()
{
    this->close();
}

void GuiManager::on_butQuit3_clicked()
{
    this->close();
}


void GuiManager::on_listUser_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    int uId = item->text(1).toInt();
    User &user = data->getUserByIdRef(uId);
    GuiUserInfo *guiUserInfo = new GuiUserInfo(3, &user);
    guiUserInfo->setWindowTitle("User Info");
    guiUserInfo->move(QApplication::desktop()->screen()->rect().center()-this->rect().center());
    guiUserInfo->show();
}

void GuiManager::on_listAccount_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    int aId = item->text(1).toInt();
    Account &acc = data->getAccountByIdRef(aId);
    guiAccountInfo *guiAccInfo = new guiAccountInfo(3, &acc);
    guiAccInfo->setWindowTitle("Account Info");
    guiAccInfo->move(QApplication::desktop()->screen()->rect().center()-this->rect().center());
    guiAccInfo->show();
}

void GuiManager::on_butImportUser_clicked()
{
    QString fName = QFileDialog::getOpenFileName(this,
                                                 "Open File",
                                                 "",
                                                 "CSV(*.csv)"
                                                 );
    QFile file(fName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "Error!", "Can't open file");
    }
    else{
        file.readLine();
        while (!file.atEnd()) {
            QString line = file.readLine();
            line.remove("\r\n");
            QStringList list = line.split(',');
            User user;
            user.setUName(list[0]);
            user.setUCode(list[1].toInt());
            user.setUDob(QDate::fromString(list[2], DATE_FORMAT));
            user.setUEmail(list[3]);
            user.setUJob(list[4]);

            bool isUserExist = 0;
            for (int i=0; i<data->nUser; i++)
                if (data->users[i].getUCode() == user.getUCode()){
                    isUserExist = 1;
                    break;
                }
            if (!isUserExist){
                data->addNewUser(&user);
                addUserViewTo(ui->listUser, user);
            }
        }
    }
}
