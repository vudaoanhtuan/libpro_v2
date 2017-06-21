#ifndef GUILIBRARIAN_H
#define GUILIBRARIAN_H

#include <QMainWindow>
#include "datastore.h"
#include "guiaddbook.h"
#include "loginform.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QCloseEvent>
#include <QMessageBox>
#include <QInputDialog>
#include <QHeaderView>
#include <QDesktopWidget>
#include <QFile>
#include <QFileDialog>

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
    void initBookTab();
    void initRequestTab();
    void initBorrowTab();
    void initInfoTab();

    // Function for Book Tab
    void addBookViewTo(QTreeWidget *view, Book &book);
    bool searchBookByKey(Book &book, QString key);
    bool isBookUsing(int bId);


    // Function for Request Tab
    void addAccAndBookTo(QTreeWidget *view, Account &acc, Book &book);
    bool searchRequestByAccount(Account &acc, QString key);

    // Function for Borrow tab
    void addBookBorrowViewTo(QTreeWidget *view, Account &acc, BookBorrow &bBorrow);

    // Close event
    void closeEvent(QCloseEvent *event);

private slots:
    void addNewBookFromForm(Book *book);

    void editInfoBook(Book *book, int id);

    void on_butAddBook_clicked();

    void on_butSearch_clicked();

    void on_butRemoveBook_clicked();

    void on_butEdit_clicked();

    void on_bAccept_clicked();

    void on_bRemoveRequest_clicked();

    void on_bSearchRequest_clicked();

    void on_bRemoveBorrow_clicked();

    void on_bSearchBorrow_clicked();

    void on_bQuit1_clicked();

    void on_bQuit2_clicked();

    void on_bQuit3_clicked();

    void on_bQuit4_clicked();

    void on_bLogout1_clicked();

    void on_bLogout2_clicked();

    void on_bLogout3_clicked();

    void on_bLogout4_clicked();

    void on_butChangePassword_clicked();

    void on_listBookView_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_butImport_clicked();

private:
    Ui::GuiLibrarian *ui;
};

#endif // GUILIBRARIAN_H
