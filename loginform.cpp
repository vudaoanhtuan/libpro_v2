#include "loginform.h"
#include "ui_loginform.h"


LoginForm::LoginForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    data = new DataStore;
//    qDebug()<<data.users[0].getUName();
//    qDebug()<<data.books[0].getBTitle();
//    qDebug()<<data.accounts[0].getAName();


}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_buttonQuit_clicked()
{
    delete data;
    this->close();
}

void LoginForm::on_buttonLogin_clicked()
{
    QString account = ui->inputAccount->text();
    QString password = ui->inputPassword->text();

    if (data->exitAccountByName(account)){
        Account curAcc = data->getAccountByNameRef(account);
        if (curAcc.getAPass() == password){
            ui->labelStatus->setText("Loged in!");
            if (curAcc.getARole() == rREADER){
                GuiReader *readerGui  = new GuiReader(curAcc.getAId());
                this->close();
                readerGui->show();
            }
        }
        else{
            ui->labelStatus->setText("Wrong Password!");
        }
    }
    else{
        ui->labelStatus->setText("Wrong Account!");
    }



}
