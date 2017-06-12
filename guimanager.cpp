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
    setWindowTitle("Libpro - " + data->ItsMe.myAccount.getAName()+ " (Reader)");
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
    ui->lRole->setText("Role: Reader");
    ui->lStatus->setText("Status: Active");
}

void GuiManager::initAccountTab()
{
    ui->listAccount->hideColumn(0);
    for (int i=0; i<data->nAccount; i++){
        Account &curAcc = data->accounts[i];
        addAccountViewTo(ui->listAccount, curAcc);
    }
}

void GuiManager::initUserTab()
{
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

        int pos = data->getPosAccountById(aId);
        if (resBtn == QMessageBox::Yes && pos > -1){
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

}
