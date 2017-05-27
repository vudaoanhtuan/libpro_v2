#include "guiaddbook.h"
#include "ui_guiaddbook.h"

GuiAddBook::GuiAddBook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiAddBook)
{
    ui->setupUi(this);
}

GuiAddBook::~GuiAddBook()
{
    delete ui;
}

void GuiAddBook::on_bAdd_clicked()
{
    Book *book = new Book;
    book->setBAuthor(ui->inputAuthor->text());
    book->setBCategory(ui->inputCategory->text());
    book->setBPublisher(ui->inputPublisher->text());
    book->setBTitle(ui->inputTitle->text());
    book->setBYear(ui->inputYear->text().toInt());
    emit closeAndReturnBook(book);
    this->close();
}

void GuiAddBook::on_bCancel_clicked()
{
    this->close();
}
