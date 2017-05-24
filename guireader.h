#ifndef GUIREADER_H
#define GUIREADER_H

#include <QMainWindow>
#include "datastore.h"
#include "loginform.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QCloseEvent>
#include <QMessageBox>
#include <QInputDialog>

namespace Ui {
class GuiReader;
}

class GuiReader : public QMainWindow
{
    Q_OBJECT

public:
    DataStore *data;
    explicit GuiReader(int accountId, QWidget *parent = 0);
    ~GuiReader();

    // Init tab;
    void initInfoTab();
    void initBookTab();
    void initStatusTab();


    // Function for Book Tab
    void addBookViewTo(QTreeWidget *view, Book &book);
    bool searchBookByKey(Book &book, QString key);

    // Function for Status Tab
    void showListBookBorrowing();

    // Close gui
    void closeEvent (QCloseEvent *event);

private slots:
    void on_butSearch_clicked();

    void on_butRequest_clicked();

    void on_bRemove_clicked();

    void on_butChangePassword_clicked();

    void on_butQuit_clicked();

    void on_bQuit2_clicked();

    void on_butQuit3_clicked();

    void on_butLogout_clicked();

    void on_bLogout2_clicked();

    void on_butLogout3_clicked();

private:
    Ui::GuiReader *ui;
};

#endif // GUIREADER_H
