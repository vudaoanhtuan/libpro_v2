#ifndef GUIADDBOOK_H
#define GUIADDBOOK_H

#include <QMainWindow>
#include "book.h"

namespace Ui {
class GuiAddBook;
}

class GuiAddBook : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuiAddBook(QWidget *parent = 0);
    ~GuiAddBook();

private slots:
    void on_bAdd_clicked();


    void on_bCancel_clicked();

signals:
    void closeAndReturnBook(Book *book);

private:
    Ui::GuiAddBook *ui;
};

#endif // GUIADDBOOK_H
