#ifndef GUILIBRARIAN_H
#define GUILIBRARIAN_H

#include <QMainWindow>
#include "datastore.h"
#include "guiaddbook.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QCloseEvent>
#include <QMessageBox>
#include <QInputDialog>

namespace Ui {
class GuiLibrarian;
}

class GuiLibrarian : public QMainWindow
{
    Q_OBJECT

public:
    DataStore *data;
    explicit GuiLibrarian(int accountId, QWidget *parent = 0);
    ~GuiLibrarian();


    // Init tab
    void initInfoTab();

    // Function for Book Tab
    void addBookViewTo(QTreeWidget *view, Book &book);
    bool searchBookByKey(Book &book, QString key);



    // Close event
    void closeEvent(QCloseEvent *event);

private slots:
    void addNewBookFromForm(Book *book);
    void on_butAddBook_clicked();

private:
    Ui::GuiLibrarian *ui;
};

#endif // GUILIBRARIAN_H
