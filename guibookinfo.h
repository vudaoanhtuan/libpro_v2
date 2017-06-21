#ifndef GUIBOOKINFO_H
#define GUIBOOKINFO_H

#include <QMainWindow>
#include "book.h"

namespace Ui {
class GuiBookInfo;
}

class GuiBookInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuiBookInfo(Book &book, QWidget *parent = 0);
    ~GuiBookInfo();

private slots:
    void on_butClose_clicked();

private:
    Ui::GuiBookInfo *ui;
};

#endif // GUIBOOKINFO_H
