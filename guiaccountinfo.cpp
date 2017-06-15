#include "guiaccountinfo.h"
#include "ui_guiaccountinfo.h"

guiAccountInfo::guiAccountInfo(int work, Account *acc, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::guiAccountInfo)
{
    data = new DataStore;

    ui->setupUi(this);
    if (work == 1)
        this->work = ADD;
    if (work == 2)
        this->work = EDIT;
    if (work == 3)
        this->work = INFO;
    // 1. Add
    if (work == 1){
        ui->sActive->setChecked(true);
        ui->bReset->hide();

    }

    // 2. Edit
    if (work == 2){
        aId = acc->getAId();
        ui->iAccName->setDisabled(1);
        ui->iPass->hide();

        ui->iAccName->setText(acc->getAName());
        ui->iUserId->setText(QString::number(acc->getUserId()));

        if (acc->getAStatus() == 1)
            ui->sActive->setChecked(1);
        else
            ui->sInactive->setChecked(1);

        ui->iPass->setText(acc->getAPass());

        Role role = acc->getARole();
        bool iR = DataStore::isReader(role);
        bool iL = DataStore::isLibrarian(role);
        bool iM = DataStore::isManager(role);

        if (iR) ui->cReader->setChecked(1);
        if (iL) ui->cLibrarian->setChecked(1);
        if (iM) ui->cManager->setChecked(1);
    }

    if (work == INFO){

        ui->iAccName->hide();
        ui->iUserId->hide();
        ui->iPass->hide();
        ui->bReset->hide();
        ui->cLibrarian->hide();
        ui->cReader->hide();
        ui->cManager->hide();
        ui->sActive->hide();
        ui->sInactive->hide();
        ui->lAccountName->setText("Account: " + acc->getAName());
        ui->lUserId->setText("User Id: " + QString::number(acc->getUserId()));

        if (acc->getAStatus() == 1)
            ui->lStatus->setText("Status: Active");
        else
            ui->lStatus->setText("Status: Inactive");

        ui->iPass->setText(acc->getAPass());

        Role role = acc->getARole();
        bool iR = DataStore::isReader(role);
        bool iL = DataStore::isLibrarian(role);
        bool iM = DataStore::isManager(role);
        QString strRole = "";
        if (iR) strRole = strRole + "Reader ";
        if (iL) strRole = strRole + "Librarian ";
        if (iM) strRole = strRole + "Manager ";
        ui->lRole->setText("Role: " + strRole);
        QString bookInfo =  "Book Borrowing: " + QString::number(acc->getNBorrow()) + "\n" +
                            "Book Requesting: " + QString::number(acc->getNRequest());
        ui->lPassword->setText(bookInfo);

        ui->bOk->hide();
        ui->bCancel->setText("Close");
    }

}

guiAccountInfo::~guiAccountInfo()
{
    delete data;
    delete ui;
}

QString guiAccountInfo::checkInput()
{
    QString aName = ui->iAccName->text();
    bool isNum;
    int uId = ui->iUserId->text().toInt(&isNum);
    QString aPass = ui->iPass->text();
    bool iR = ui->cReader->isChecked();
    bool iL = ui->cLibrarian->isChecked();
    bool iM = ui->cManager->isChecked();

    bool isUserExist = 0;

    bool isAccountExist = 0;

    for (int i=0;i<data->nAccount;i++){
        Account acc=data->accounts[i];
        if (acc.getAName()==aName){
            isAccountExist = 1;
            break;
        }
    }

    if (aName==""){
        return "You must set account name!";
    }

    if (aName.contains(" "))
        return "Account name invalid!";

    if (isAccountExist){
        return "Someone used this name!";
    }

    if (!isNum){
        return "User Id must be number!";
    }
    else{
        for (int i=0;i<data->nUser;i++){
            User &user = data->users[i];
            if (user.getUId() == uId){
                isUserExist = 1;
                break;
            }
        }
        if (!isUserExist){
            return "User doesn't exit!";
        }
    }

    if (!(iR || iL || iM)){
        return "You must set role for account!";
    }

    if (work == ADD && aPass==""){
        return "You must set password";
    }

    return "Done";
}

void guiAccountInfo::on_bOk_clicked()
{
    QString status = checkInput();
    if (status=="Done"){
        Account *acc = new Account;
        acc->setAName(ui->iAccName->text());
        acc->setUserId(ui->iUserId->text().toInt());
        if (ui->sActive->isChecked())
            acc->setAStatus(1);
        else
            acc->setAStatus(0);
        bool isReader = ui->cReader->isChecked();
        bool isLibrarian = ui->cLibrarian->isChecked();
        bool isManager = ui->cManager->isChecked();
        Role role = DataStore::getRole(isReader, isLibrarian, isManager);
        acc->setARole(role);
        acc->setAPass(ui->iPass->text());


        if (work == ADD){
            acc->setNBorrow(0);
            acc->setNRequest(0);
            emit addAccount(acc);
        }

        if (work == EDIT){
            qDebug()<<aId;
            qDebug()<<(int)acc->getARole();
            emit editAccount(acc, aId);
        }
        this->close();
    }
    else{
        QMessageBox::information(this, "Error!", status);
    }

}

void guiAccountInfo::on_bCancel_clicked()
{
    this->close();
}

void guiAccountInfo::on_bReset_clicked()
{
    ui->iPass->setText("123456");
    QMessageBox::information(this, "Reset Password", "Password reset to \"123456\"!");
}
