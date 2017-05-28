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
    void initBookTab();
    void initRequestTab();

    // Function for Book Tab
    void addBookViewTo(QTreeWidget *view, Book &book);
    bool searchBookByKey(Book &book, QString key);


    // Function for Request Tab
    void addRequestViewTo(QTreeWidget *view, Account &acc, Book &book);
    bool searchRequestByAccount(Account &acc, QString key);

    // Close event
    void closeEvent(QCloseEvent *event);

private slots:
    void addNewBookFromForm(Book *book);

    void editInfoBook(Book *book, int id);

    void on_butAddBook_clicked();

    void on_butSearch_clicked();

    void on_butRemove_clicked();

    void on_butEdit_clicked();

    void on_bAccept_clicked();

    void on_bRemove2_clicked();

    void on_bSearchRequest_clicked();

private:
    Ui::GuiLibrarian *ui;
};

#endif // GUILIBRARIAN_H
