#include "guilibrarian.h"
#include "ui_guilibrarian.h"

GuiLibrarian::GuiLibrarian(int accountId, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiLibrarian)
{
    data = new DataStore;
    data->ItsMe.myAccount = data->getAccountByIdRef(accountId);
    data->ItsMe.myUser = data->getUserByIdRef(data->ItsMe.myAccount.getUserId());

    ui->setupUi(this);

    // Init tab
    initBookTab();
    initInfoTab();
    initRequestTab();
    initBorrowTab();

}

GuiLibrarian::~GuiLibrarian()
{
    delete ui;
}

void GuiLibrarian::initInfoTab()
{
    Account &a = data->ItsMe.myAccount;
    User &u = data->ItsMe.myUser;
    ui->lAccount->setText("Account: " + a.getAName());
    ui->lDoB->setText("Birth Day: " + u.getUDob().toString(DATE_FORMAT));
    ui->lEmail->setText("Email: " + u.getUEmail());
    ui->lFullName->setText("Full Name: " + u.getUName());
    ui->lJob->setText("Job: " + u.getUJob());
    ui->lRole->setText("Role: Librarian");
    ui->lStatus->setText("Status: Active");
}

void GuiLibrarian::initBookTab()
{
    ui->listBookView->hideColumn(6);
    ui->listBookView->clear();
    for (int i=0;i<data->nBook;i++)
        addBookViewTo(ui->listBookView, data->books[i]);
}

void GuiLibrarian::initRequestTab()
{
    ui->listRequesting->hideColumn(0);
    ui->listRequesting->hideColumn(2);
    for (int i=0;i<data->nAccount;i++){
        Account &curAcc = data->accounts[i];
        int nReq = curAcc.getNRequest();
        if (nReq > 0){
            QVector<int> listBook = curAcc.getListRequest();
            for (int j=0;j<nReq;j++){
                Book &book = data->getBookByIdRef(listBook[j]);
                addAccAndBookTo(ui->listRequesting, curAcc, book);
            }
        }
    }
}

void GuiLibrarian::initBorrowTab()
{
    ui->listBorrowing->hideColumn(5);
    ui->listBorrowing->hideColumn(6);
    ui->listBorrowing->clear();
    for (int i=0;i<data->nAccount;i++){
        if (data->accounts[i].getNBorrow() > 0){
            QVector<BookBorrow> borrowing = data->accounts[i].getListBorrows();
            for (int iB=0;iB<borrowing.size();iB++){
                addBookBorrowViewTo(ui->listBorrowing, data->accounts[i], borrowing[iB]);
            }
        }
    }
}

void GuiLibrarian::addBookViewTo(QTreeWidget *view, Book &book)
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

bool GuiLibrarian::searchBookByKey(Book &book, QString key)
{
    QStringList word = key.split(" ");
    for (int i=0;i<word.size();i++){
        if (book.getBTitle().contains(word[i],Qt::CaseInsensitive))
            return 1;
    }
    return 0;
}

bool GuiLibrarian::isBookUsing(int bId)
{
    for (int i=0;i<data->nAccount;i++){
        Account &acc=data->accounts[i];
        // Book request
        QVector<int> listR = acc.getListRequest();
        for (int iR=0;iR<listR.size();iR++)
            if (listR[iR] == bId)
                return 1;

        // Book borrow
        QVector<BookBorrow> listB = acc.getListBorrows();
        for (int iB=0;iB<listB.size();iB++)
            if (listB[iB].bookId == bId)
                return 1;
    }
    return 0;
}

void GuiLibrarian::addAccAndBookTo(QTreeWidget *view, Account &acc, Book &book)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(view);
    item->setText(0, QString::number(acc.getAId()));
    item->setText(1, acc.getAName());
    item->setText(2, QString::number(book.getBId()));
    item->setText(3, book.getBTitle());
}

bool GuiLibrarian::searchRequestByAccount(Account &acc, QString key)
{
    if (acc.getAName().contains(key) && acc.getNRequest() > 0)
        return 1;
    return 0;
}

void GuiLibrarian::addBookBorrowViewTo(QTreeWidget *view, Account &acc, BookBorrow &bBorrow)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(view);
    item->setText(0,acc.getAName());
    Book book = data->getBookByIdRef(bBorrow.bookId);
    item->setText(1,book.getBTitle());
    QDate date = bBorrow.dayBorrow;
    item->setText(2,date.toString(DATE_FORMAT));
    date = date.addDays(MAX_DAY);
    item->setText(3,date.toString(DATE_FORMAT));

    int nDate = date.daysTo(QDate::currentDate());
    int fine = 0;
    if (nDate > 0){
        fine = nDate * data->nFine;
    }
    item->setText(4,QString::number(fine));
    item->setText(5, QString::number(acc.getAId()));
    item->setText(6,QString::number(bBorrow.bookId));
}



void GuiLibrarian::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "LibPro",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Yes | QMessageBox::No,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        Account &a = data->getAccountByIdRef(data->ItsMe.myAccount.getAId());
        a = data->ItsMe.myAccount;
        event->accept();
        delete data;
        delete this;
    }
}

void GuiLibrarian::addNewBookFromForm(Book *book)
{
    data->addNewBook(book);
    initBookTab();
}

void GuiLibrarian::editInfoBook(Book *book, int id)
{
    Book &bookRef = data->getBookByIdRef(id);
    bookRef.setBAuthor(book->getBAuthor());
    bookRef.setBCategory(book->getBCategory());
    bookRef.setBPublisher(book->getBPublisher());
    bookRef.setBTitle(book->getBTitle());
    bookRef.setBYear(book->getBYear());
    initBookTab();
}

void GuiLibrarian::on_butAddBook_clicked()
{
    GuiAddBook *addBookGui = new GuiAddBook;
    connect(addBookGui, SIGNAL(closeAndReturnBook(Book*)), this, SLOT(addNewBookFromForm(Book*)));
    addBookGui->show();
}

void GuiLibrarian::on_butSearch_clicked()
{
    ui->listBookView->clear();
    QString key = ui->textSearch->text();
    for (int i=0;i<data->nBook;i++){
        if (searchBookByKey(data->books[i], key))
            addBookViewTo(ui->listBookView, data->books[i]);
    }
}

void GuiLibrarian::on_butRemoveBook_clicked()
{
    if (ui->listBookView->currentItem() == 0)
        return;
    int bookId = ui->listBookView->currentItem()->text(0).toInt();
    if (isBookUsing(bookId)){
        QMessageBox::information(this, "Error!", "Someone is borrowing or requesting this book!");
        qDebug() << "Can't delete book";
        return;
    }


    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "LibPro",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Yes | QMessageBox::No,
                                                                QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes){
        int pos = data->getPosBookById(bookId);
        if (pos > -1){
            data->books.remove(pos);
            data->nBook--;
            qDebug() << "Book deleted";
        }
        else
            qDebug() << "Can't delete book";
        delete ui->listBookView->currentItem();
    }



}

void GuiLibrarian::on_butEdit_clicked()
{
    if (ui->listBookView->currentItem() == 0)
        return;
    int bookId = ui->listBookView->currentItem()->text(0).toInt();

    Book &book = data->getBookByIdRef(bookId);


    GuiAddBook *editBookGui = new GuiAddBook;
    editBookGui->setEditBookForm(&book);
    connect(editBookGui, SIGNAL(closeAndReturnEditBook(Book*,int)), this, SLOT(editInfoBook(Book*, int)));
    editBookGui->show();
}

void GuiLibrarian::on_bAccept_clicked()
{
    if (ui->listRequesting->currentItem() == 0)
        return;
    int accId = ui->listRequesting->currentItem()->text(0).toInt();
    int bookId = ui->listRequesting->currentItem()->text(2).toInt();
    Account &curAcc  = data->getAccountByIdRef(accId);
    curAcc.removeRequest(bookId);
    curAcc.borrowBook(bookId);
    delete ui->listRequesting->currentItem();
}

void GuiLibrarian::on_bRemoveRequest_clicked()
{
    if (ui->listRequesting->currentItem() == 0)
        return;

    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Confirm!",
                                                                tr("Do you want delete this request?\n"),
                                                                QMessageBox::Yes | QMessageBox::No,
                                                                QMessageBox::Yes);

    if (resBtn==QMessageBox::Yes){
        int accId = ui->listRequesting->currentItem()->text(0).toInt();
        int bookId = ui->listRequesting->currentItem()->text(2).toInt();
        Account &curAcc  = data->getAccountByIdRef(accId);
        curAcc.removeRequest(bookId);
        delete ui->listRequesting->currentItem();
    }


}

void GuiLibrarian::on_bSearchRequest_clicked()
{
    ui->listRequesting->clear();
    QString text = ui->inputAccountRequest->text();
    for (int iAcc=0; iAcc<data->nAccount; iAcc++){
        Account &curAcc = data->accounts[iAcc];
        if (searchRequestByAccount(curAcc, text)){
            QVector<int> listBook = curAcc.getListRequest();
            for (int iR=0; iR<listBook.size(); iR++)
                addAccAndBookTo(ui->listRequesting, curAcc, data->getBookByIdRef(listBook[iR]));
        }
    }
}

void GuiLibrarian::on_bRemoveBorrow_clicked()
{
    if (ui->listBorrowing->currentItem() == 0)
        return;

    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Confirm!",
                                                                tr("Did this book return?\n"),
                                                                QMessageBox::Yes | QMessageBox::No,
                                                                QMessageBox::Yes);

    if (resBtn == QMessageBox::Yes){
        int aId = ui->listBorrowing->currentItem()->text(5).toInt();
        int bId = ui->listBorrowing->currentItem()->text(6).toInt();
        Account &acc = data->getAccountByIdRef(aId);
        acc.removeBorrow(bId);
        delete ui->listBorrowing->currentItem();
    }
}


void GuiLibrarian::on_bSearchBorrow_clicked()
{
    ui->listBorrowing->clear();
    QString text = ui->inputBorrow->text();
    for (int iA = 0; iA < data->nAccount; iA++){
        Account &acc = data->accounts[iA];
        if (acc.getAName().contains(text)){
            if (acc.getNBorrow() > 0){
                QVector<BookBorrow> borrowing = acc.getListBorrows();
                for (int iB=0;iB<borrowing.size();iB++){
                    addBookBorrowViewTo(ui->listBorrowing, acc, borrowing[iB]);
                }
            }
        }
    }
}

void GuiLibrarian::on_bQuit1_clicked()
{
    this->close();
}

void GuiLibrarian::on_bQuit2_clicked()
{
    this->close();
}

void GuiLibrarian::on_bQuit3_clicked()
{
    this->close();
}

void GuiLibrarian::on_bQuit4_clicked()
{
    this->close();
}

void GuiLibrarian::on_bLogout1_clicked()
{
    if (this->close()){
         LoginForm *loginForm = new LoginForm();
         loginForm->show();
    }
}

void GuiLibrarian::on_bLogout2_clicked()
{
    if (this->close()){
         LoginForm *loginForm = new LoginForm();
         loginForm->show();
    }
}

void GuiLibrarian::on_bLogout3_clicked()
{
    if (this->close()){
         LoginForm *loginForm = new LoginForm();
         loginForm->show();
    }
}

void GuiLibrarian::on_bLogout4_clicked()
{
    if (this->close()){
         LoginForm *loginForm = new LoginForm();
         loginForm->show();
    }
}

void GuiLibrarian::on_butChangePassword_clicked()
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
