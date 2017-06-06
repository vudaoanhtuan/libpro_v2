#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QMainWindow>
#include <QDebug>
#include "datastore.h"
#include "guireader.h"
#include "guilibrarian.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QMainWindow
{
    Q_OBJECT

public:
    DataStore *data;

    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

private slots:
    void on_buttonQuit_clicked();

    void on_buttonLogin_clicked();

    void on_bReader_clicked();

    void on_bLibrarian_clicked();

    void on_bManager_clicked();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
