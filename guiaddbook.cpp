#include "guiaddbook.h"
#include "ui_guiaddbook.h"

GuiAddBook::GuiAddBook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiAddBook)
{
    forEdit = 0;
    ui->setupUi(this);
}

GuiAddBook::~GuiAddBook()
{
    delete ui;
}

void GuiAddBook::setEditBookForm(Book *book)
{
    this->setWindowTitle("Edit Book");
    ui->bAdd->setText("OK");


    ui->inputAuthor->setText(book->getBAuthor());
    ui->inputCategory->setText(book->getBCategory());
    ui->inputPublisher->setText(book->getBPublisher());
    ui->inputTitle->setText(book->getBTitle());
    ui->inputYear->setText(QString::number(book->getBYear()));

    currentBookId = book->getBId();
    forEdit = 1;
}

void GuiAddBook::on_bAdd_clicked()
{
    Book *book = new Book;
    book->setBAuthor(ui->inputAuthor->text());
    book->setBCategory(ui->inputCategory->text());
    book->setBPublisher(ui->inputPublisher->text());
    book->setBTitle(ui->inputTitle->text());
    book->setBYear(ui->inputYear->text().toInt());
    if (forEdit)
        emit closeAndReturnEditBook(book, currentBookId);
    else
        emit closeAndReturnBook(book);
    this->close();
}

void GuiAddBook::on_bCancel_clicked()
{
    this->close();
}
