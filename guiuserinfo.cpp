#include "guiuserinfo.h"
#include "ui_guiuserinfo.h"

GuiUserInfo::GuiUserInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiUserInfo)
{
    ui->setupUi(this);
}

GuiUserInfo::~GuiUserInfo()
{
    delete ui;
}
