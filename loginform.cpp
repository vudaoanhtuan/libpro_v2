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
    ui->bReader->hide();
    ui->bLibrarian->hide();
    ui->bManager->hide();
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
        data->ItsMe.myAccount = curAcc;
        if (curAcc.getAPass() == password){
            if (curAcc.getAStatus() == 0){
                ui->labelStatus->setText("Your account is disabled!");
                return;
            }
            ui->labelStatus->setText("Log in as:");

            Role role = curAcc.getARole();
            bool isReader = data->isReader(role);
            bool isLibrarian = data->isLibrarian(role);
            bool isManager = data->isManager(role);
            if (isReader)
                ui->bReader->show();

            if (isLibrarian)
                ui->bLibrarian->show();

            if (isManager)
                ui->bManager->show();
        }
        else{
            ui->labelStatus->setText("Wrong Password!");
        }
    }
    else{
        ui->labelStatus->setText("Wrong Account!");
    }



}

void LoginForm::on_bReader_clicked()
{
    Account &curAcc = data->ItsMe.myAccount;
    GuiReader *readerGui  = new GuiReader(curAcc.getAId());
    this->close();
    readerGui->show();
}

void LoginForm::on_bLibrarian_clicked()
{
    Account &curAcc = data->ItsMe.myAccount;
    GuiLibrarian *librarianGui = new GuiLibrarian(curAcc.getAId());
    this->close();
    librarianGui->show();
}

void LoginForm::on_bManager_clicked()
{
    Account &curAcc = data->ItsMe.myAccount;
    GuiManager *managerGui = new GuiManager(curAcc.getAId());
    this->close();
    managerGui->show();
}
