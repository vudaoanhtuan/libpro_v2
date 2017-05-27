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
    initInfoTab();

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
}

void GuiLibrarian::on_butAddBook_clicked()
{
    GuiAddBook *addBookGui = new GuiAddBook;
    connect(addBookGui, SIGNAL(closeAndReturnBook(Book*)), this, SLOT(addNewBookFromForm(Book*)));
    addBookGui->show();
}
