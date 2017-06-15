#include "guiuserinfo.h"
#include "ui_guiuserinfo.h"

GuiUserInfo::GuiUserInfo(int work, User *user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiUserInfo)
{
    data = new DataStore;
    ui->setupUi(this);
    if (work == 1)
        this->work = ADD;
    if (work == 2)
        this->work = EDIT;
    if (work == 3)
        this->work = INFO;


    if (work == ADD){
        ui->iUserId->hide();
        ui->lId->hide();
    }

    if (work == EDIT){
        uId = user->getUId();
        ui->iUserId->setDisabled(1);

        ui->iUserId->setText(QString::number(user->getUId()));
        ui->iUserName->setText(user->getUName());
        ui->iUserCode->setText(QString::number(user->getUCode()));
        ui->iUserJob->setText(user->getUJob());
        ui->iUserEmail->setText(user->getUEmail());
        ui->iUserDoB->setText(user->getUDob().toString(DATE_FORMAT));
    }

    if (work == INFO){
        ui->lCode->setText("Code: " + QString::number(user->getUCode()));
        ui->lDob->setText("Date of Birth: " + user->getUDob().toString(DATE_FORMAT));
        ui->lEmail->setText("Email: " + user->getUEmail());
        ui->lId->setText("Id: " + QString::number(user->getUId()));
        ui->lJob->setText("Job: " + user->getUJob());
        ui->lName->setText("Full Name: " + user->getUName());

        ui->iUserCode->hide();
        ui->iUserDoB->hide();
        ui->iUserEmail->hide();
        ui->iUserId->hide();
        ui->iUserJob->hide();
        ui->iUserName->hide();
        ui->bOK->hide();
        ui->bCancel->setText("Close");


    }
}

GuiUserInfo::~GuiUserInfo()
{
    delete data;
    delete ui;
}

QString GuiUserInfo::checkInput()
{
    QString uEmail = ui->iUserEmail->text();
    QString uDob = ui->iUserDoB->text();
    bool isNum=0;
    int uCode = ui->iUserCode->text().toInt(&isNum);

    QRegularExpression reDate("^(0[1-9]|[12][0-9]|3[01])[/](0[1-9]|1[012])[/](19|20)\\d\\d$");
    bool isDate=1;
    if (!reDate.match(uDob).hasMatch()){
        isDate=0;
    }


    QRegularExpression regex("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");
    bool isEmail = 1;
    if(!regex.match(uEmail).hasMatch()){
        isEmail = 0;
    }

    if (!isNum){
        return "User code must be number!";
    }
    else{
        if (work == ADD){
            bool isCodeExit=0;
            for (int i=0;i<data->nUser;i++){
                User &user=data->users[i];
                if (user.getUCode()==uCode){
                    isCodeExit=1;
                    break;
                }
            }
            if (isCodeExit)
                return "Some user is using this code!";
        }
        if (work == EDIT){
            bool isCodeExit=0;
            for (int i=0;i<data->nUser;i++){
                User &user=data->users[i];
                if (user.getUId() != uId && user.getUCode()==uCode){
                    isCodeExit=1;
                    break;
                }
            }
            if (isCodeExit)
                return "Some user is using this code!";
        }
    }

    if (!isEmail){
        return "Email invalid!";
    }

    if (!isDate){
        return "Date invalid!";
    }

    return "Done";

}

void GuiUserInfo::on_bOK_clicked()
{
    QString status = checkInput();

    if (status == "Done"){
        User user;
        user.setUCode(ui->iUserCode->text().toInt());
        user.setUDob(QDate::fromString(ui->iUserDoB->text(), DATE_FORMAT));
        user.setUEmail(ui->iUserEmail->text());
        user.setUJob(ui->iUserJob->text());
        user.setUName(ui->iUserName->text());

        if (work == ADD){
            emit addNewUser(&user);
        }

        if (work == EDIT){
            emit editUser(&user, uId);
        }

        this->close();
    }
    else{
        QMessageBox::information(this, "Error!", status);
    }

}

void GuiUserInfo::on_bCancel_clicked()
{
    this->close();
}
