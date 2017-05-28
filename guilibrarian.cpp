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
    ui->listBookView->clear();
    for (int i=0;i<data->nBook;i++)
        addBookViewTo(ui->listBookView, data->books[i]);
}

void GuiLibrarian::initRequestTab()
{
    for (int i=0;i<data->nAccount;i++){
        Account &curAcc = data->accounts[i];
        int nReq = curAcc.getNRequest();
        if (nReq > 0){
            QVector<int> listBook = curAcc.getListRequest();
            for (int j=0;j<nReq;j++){
                Book &book = data->getBookByIdRef(listBook[j]);
                addRequestViewTo(ui->listRequesting, curAcc, book);
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
        if (book.getBTitle().contains(word[i]))
            return 1;
    }
    return 0;
}

void GuiLibrarian::addRequestViewTo(QTreeWidget *view, Account &acc, Book &book)
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

void GuiLibrarian::on_butRemove_clicked()
{
    if (ui->listBookView->currentItem() == 0)
        return;
    int bookId = ui->listBookView->currentItem()->text(0).toInt();
    int pos = data->getPosBookById(bookId);
    if (pos > -1){
        data->books.remove(pos);
        data->nBook--;
        qDebug() << "Book deleted";
    }
    else
        qDebug() << "Can't delete book";
    initBookTab();
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

void GuiLibrarian::on_bRemove2_clicked()
{
    if (ui->listRequesting->currentItem() == 0)
        return;
    int accId = ui->listRequesting->currentItem()->text(0).toInt();
    int bookId = ui->listRequesting->currentItem()->text(2).toInt();
    Account &curAcc  = data->getAccountByIdRef(accId);
    curAcc.removeRequest(bookId);
    delete ui->listRequesting->currentItem();
}

void GuiLibrarian::on_bSearchRequest_clicked()
{
    ui->listRequesting->clear();
    QString text = ui->inputAccountRequest->text();
    if (text.compare("all") == 0){
        initRequestTab();
        return;
    }
    QStringList listKey = text.split(" ");
    QString textSearchAccount = listKey[0];
    if (textSearchAccount.startsWith("a:")){
        textSearchAccount = textSearchAccount.remove(0,2);
        for (int iAcc=0; iAcc<data->nAccount; iAcc++){
            Account &curAcc = data->accounts[iAcc];
            if (searchRequestByAccount(curAcc, textSearchAccount)){
                QVector<int> listBook = curAcc.getListRequest();
                for (int iR=0; iR<listBook.size(); iR++)
                    addRequestViewTo(ui->listRequesting, curAcc, data->getBookByIdRef(listBook[iR]));
            }
        }


    }
}
