#include "guireader.h"
#include "ui_guireader.h"

GuiReader::GuiReader(int accountId, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiReader)
{
    data = new DataStore;

    data->ItsMe.myAccount = data->getAccountByIdRef(accountId);
    data->ItsMe.myUser = data->getUserByIdRef(data->ItsMe.myAccount.getUserId());
    ui->setupUi(this);
    setWindowTitle("Libpro - " + data->ItsMe.myAccount.getAName()+ " (Reader)");
    setMinimumSize(810,500);
    this->move(QApplication::desktop()->screen()->rect().center()-this->rect().center());
    initInfoTab();
    initBookTab();
    initStatusTab();
    initHistoryTab();

    ui->tabWidget->setCurrentIndex(0);
}

GuiReader::~GuiReader()
{
    delete ui;
}

void GuiReader::initInfoTab()
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

void GuiReader::initBookTab()
{
    ui->listBookView->hideColumn(6);
    ui->listBookView->clear();
    ui->listBookView->setColumnWidth(0,70);
    ui->listBookView->setColumnWidth(1,200);
    ui->listBookView->setColumnWidth(2,130);
    ui->listBookView->setColumnWidth(5,70);
    for (int i=0;i<data->nBook;i++)
        addBookViewTo(ui->listBookView, data->books[i]);
//    ui->listBookView->hideColumn(0);

}

void GuiReader::initStatusTab()
{
    ui->listRequesting->hideColumn(6);
    ui->listBorrowing->setColumnWidth(1,200);
    ui->listRequesting->setColumnWidth(1,200);



    Account &a = data->ItsMe.myAccount;
    ui->lBorrowing->setText("Borrowing: " + QString::number(a.getNBorrow()));
    ui->lRequesting->setText("Requesting: " + QString::number(a.getNRequest()));

    showListBookBorrowing();

    QVector<int> listRequest = a.getListRequest();
    for (int i=0;i<a.getNRequest();i++){
        Book book = data->getBookByIdRef(listRequest[i]);
        addBookViewTo(ui->listRequesting, book);
    }
}

void GuiReader::initHistoryTab()
{
    Account &me = data->getAccountByIdRef(data->ItsMe.myAccount.getAId());
    QVector<int> bookHis =  me.getListHistories();
    for (int i=0; i<bookHis.size(); i++){
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->listHistory);
        item->setText(0, QString::number(bookHis[i]));
        Book book = data->getBookByIdRef(bookHis[i]);
        item->setText(1, book.getBTitle());
    }
}

void GuiReader::addBookViewTo(QTreeWidget *view, Book &book)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(view);
    item->setText(0,QString::number(book.getBId()));
    item->setText(1,book.getBTitle());
    item->setText(2,book.getBAuthor());
    item->setText(3,book.getBCategory());
    item->setText(4,book.getBPublisher());
    item->setText(5,QString::number(book.getBYear()));
    item->setText(6,QString::number(book.getBCount()));
}

bool GuiReader::searchBookByKey(Book &book, QString key){
    QStringList word = key.split(",");
    for (int i=0;i<word.size();i++){
        if (book.getBTitle().contains(word[i], Qt::CaseInsensitive))
            return 1;
    }
    return 0;
}

void GuiReader::showListBookBorrowing()
{
    Account &a = data->ItsMe.myAccount;
    int fine =0;
    QVector<BookBorrow> lists = a.getListBorrows();
    for (int i=0;i<lists.size();i++){
        Book book = data->getBookByIdRef(lists[i].bookId);
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->listBorrowing);
        item->setText(0, QString::number(book.getBId()));
        item->setText(1, book.getBTitle());
        QDate dateFrom = lists[i].dayBorrow;
        QDate dateTo = dateFrom.addDays(MAX_DAY);
        item->setText(2, dateFrom.toString(DATE_FORMAT));
        item->setText(3, dateTo.toString(DATE_FORMAT));

        item->setText(4,"0");
        int nDate = QDate::currentDate().daysTo(dateTo);
        if (nDate < 0){
            fine += -nDate;
            int curFine = -nDate*data->nFine;
            item->setText(4,QString::number(curFine));
            for (int j=0;j<ui->listBorrowing->columnCount();j++)
                item->setBackgroundColor(j, QColor::fromRgb(244, 102, 102));
        }
        else if (nDate < 2){
            for (int j=0;j<ui->listBorrowing->columnCount();j++)
                item->setBackgroundColor(j, QColor::fromRgb(255, 177, 89));
        }
        else if (nDate < 4){
            for (int j=0;j<ui->listBorrowing->columnCount();j++)
                item->setBackgroundColor(j, QColor::fromRgb(252, 228, 123));
        }
    }

    fine = fine * data->nFine;
    ui->lFine->setText("Total Fine: " + QString::number(fine) + " VND");




}

void GuiReader::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "LibPro",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Yes | QMessageBox::No,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
//        qDebug()<<&(data->ItsMe.myAccount);
//        qDebug()<<&(data->accounts[0]);
        Account &a = data->getAccountByIdRef(data->ItsMe.myAccount.getAId());
//        qDebug()<<&a;
//        qDebug()<<a.getNRequest();
        a = data->ItsMe.myAccount;
//        qDebug()<<a.getNRequest();
        event->accept();
        delete data;
        delete this;
    }
}


void GuiReader::on_butSearch_clicked()
{
    ui->listBookView->clear();
    QString key = ui->textSearch->text();
    for (int i=0;i<data->nBook;i++){
        if (searchBookByKey(data->books[i], key))
            addBookViewTo(ui->listBookView, data->books[i]);
    }
}

void GuiReader::on_butRequest_clicked()
{
    if (ui->listBookView->currentItem() == 0)
        return;

    int bookId = ui->listBookView->currentItem()->text(0).toInt();
    Account &a = data->ItsMe.myAccount;
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Confirm!",
                                                                tr("Request this book?\n"),
                                                                QMessageBox::Yes | QMessageBox::No,
                                                                QMessageBox::Yes);

    bool isRequested = 0;

    if (resBtn == QMessageBox::Yes){
        isRequested = !a.requestBook(bookId);
        if (isRequested){
            addBookViewTo(ui->listRequesting, data->getBookByIdRef(bookId));
            ui->lRequesting->setText("Requesting: " + QString::number(a.getNRequest()));
        }
        else{
            QMessageBox::information(this, "Error!", "You have got maximun book request and borrow.\nRemove some request!");
        }
    }


}

void GuiReader::on_bRemove_clicked()
{
    if (ui->listRequesting->currentItem() == 0)
        return;

    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Confirm!",
                                                                tr("Remove this request?\n"),
                                                                QMessageBox::Yes | QMessageBox::No,
                                                                QMessageBox::Yes);

    if (resBtn == QMessageBox::Yes){
        int bookId = ui->listRequesting->currentItem()->text(0).toInt();
        Account &a = data->ItsMe.myAccount;
        if (!a.removeRequest(bookId)){
            ui->lRequesting->setText("Requesting: " + QString::number(a.getNRequest()));
            delete ui->listRequesting->currentItem();
        }
    }
}

void GuiReader::on_butChangePassword_clicked()
{
    QString curPass = QInputDialog::getText(0,"Change Password","Current Password",QLineEdit::Normal,"",0);
    if (curPass == "")
        return;
    Account &a = data->ItsMe.myAccount;
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

void GuiReader::on_butQuit_clicked()
{
    this->close();
}

void GuiReader::on_bQuit2_clicked()
{
    this->close();
}

void GuiReader::on_butQuit3_clicked()
{
    this->close();
}


void GuiReader::on_butLogout_clicked()
{
    if (this->close()){
         LoginForm *loginForm = new LoginForm();
         loginForm->show();
    }
}

void GuiReader::on_bLogout2_clicked()
{
    if (this->close()){
         LoginForm *loginForm = new LoginForm();
         loginForm->show();
    }
}

void GuiReader::on_butLogout3_clicked()
{
    if (this->close()){
         LoginForm *loginForm = new LoginForm();
         loginForm->show();
    }
}

void GuiReader::on_listBookView_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    int bookId = item->text(0).toInt();
    Book book = data->getBookByIdRef(bookId);

    GuiBookInfo *bookInfoGui = new GuiBookInfo(book);
    bookInfoGui->move(QApplication::desktop()->screen()->rect().center()-this->rect().center());
    bookInfoGui->show();
}

void GuiReader::on_listRequesting_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Confirm!",
                                                                tr("Remove this request?\n"),
                                                                QMessageBox::Yes | QMessageBox::No,
                                                                QMessageBox::Yes);

    if (resBtn == QMessageBox::Yes){
        int bookId = item->text(0).toInt();
        Account &a = data->ItsMe.myAccount;
        if (!a.removeRequest(bookId)){
            ui->lRequesting->setText("Requesting: " + QString::number(a.getNRequest()));
            delete ui->listRequesting->currentItem();
        }
    }
}

void GuiReader::on_bInfo_clicked()
{
    QMessageBox::information(this, "Info", ui->lFine->text());
}

void GuiReader::on_butLogout4_clicked()
{
    if (this->close()){
         LoginForm *loginForm = new LoginForm();
         loginForm->show();
    }
}

void GuiReader::on_butQuit4_clicked()
{
    this->close();
}
