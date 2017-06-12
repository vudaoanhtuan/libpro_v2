#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QMainWindow>

namespace Ui {
class GuiManager;
}

class GuiManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuiManager(QWidget *parent = 0);
    ~GuiManager();

private:
    Ui::GuiManager *ui;
};

#endif // GUIMANAGER_H
