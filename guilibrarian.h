#ifndef GUILIBRARIAN_H
#define GUILIBRARIAN_H

#include <QMainWindow>

namespace Ui {
class GuiLibrarian;
}

class GuiLibrarian : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuiLibrarian(QWidget *parent = 0);
    ~GuiLibrarian();

private:
    Ui::GuiLibrarian *ui;
};

#endif // GUILIBRARIAN_H
