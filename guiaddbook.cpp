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
    ui->inputExist->setText(QString::number(book->getBCount()));

    currentBookId = book->getBId();
    forEdit = 1;
}

QString GuiAddBook::checkInput()
{
    QString strY = ui->inputYear->text();
    QString strE = ui->inputExist->text();
    bool isY = 0;
    bool isE = 0;
    int year = strY.toInt(&isY);
    int Exist = strE.toInt(&isE);
    if (!isY)
        return "Year must be a number!";
    if (year<100 || year > 2017)
        return "Invalid year!";
    if (!isE)
        return "Number of book must be a number!";
    return "Done";
}

void GuiAddBook::on_bAdd_clicked()
{
    QString status = checkInput();
    if (status == "Done"){
        Book book;
        book.setBAuthor(ui->inputAuthor->text());
        book.setBCategory(ui->inputCategory->text());
        book.setBPublisher(ui->inputPublisher->text());
        book.setBTitle(ui->inputTitle->text());
        book.setBYear(ui->inputYear->text().toInt());
        book.setBCount(ui->inputExist->text().toInt());
        if (forEdit)
            emit closeAndReturnEditBook(&book, currentBookId);
        else
            emit closeAndReturnBook(&book);
        this->close();
    }
    else{
        QMessageBox::information(this, "Error!", status);
    }

}

void GuiAddBook::on_bCancel_clicked()
{
    this->close();
}
