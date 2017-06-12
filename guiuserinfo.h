#ifndef GUIUSERINFO_H
#define GUIUSERINFO_H

#include <QMainWindow>

namespace Ui {
class GuiUserInfo;
}

class GuiUserInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuiUserInfo(QWidget *parent = 0);
    ~GuiUserInfo();

private:
    Ui::GuiUserInfo *ui;
};

#endif // GUIUSERINFO_H
