#include "guiaccountinfo.h"
#include "ui_guiaccountinfo.h"

guiAccountInfo::guiAccountInfo(int work, Account *acc, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::guiAccountInfo)
{
    ui->setupUi(this);
    if (work == 1)
        this->work = ADD;
    else
        this->work = EDIT;
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


}

guiAccountInfo::~guiAccountInfo()
{
    delete ui;
}

void guiAccountInfo::on_bOk_clicked()
{
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

void guiAccountInfo::on_bCancel_clicked()
{
    this->close();
}

void guiAccountInfo::on_bReset_clicked()
{
    ui->iPass->setText("123456");
    QMessageBox::information(this, "Reset Password", "Password reset to \"123456\"!");
}
