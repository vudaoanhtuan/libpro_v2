#include "guibookinfo.h"
#include "ui_guibookinfo.h"

GuiBookInfo::GuiBookInfo(Book &book, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiBookInfo)
{
    ui->setupUi(this);
    ui->lAuthor->setText("Author: " + book.getBAuthor());
    ui->lCategory->setText("Category: " + book.getBCategory());
    ui->lExit->setText("Exist: " + QString::number(book.getBCount()));
    ui->lPublisher->setText("Publisher: " + book.getBPublisher());
    ui->lTitle->setText("Title: " + book.getBTitle());
    ui->lYear->setText("Year: " + QString::number(book.getBYear()));
    ui->lId->setText("Id: " + QString::number(book.getBId()));
}

GuiBookInfo::~GuiBookInfo()
{
    delete ui;
}

void GuiBookInfo::on_butClose_clicked()
{
    this->close();
}
