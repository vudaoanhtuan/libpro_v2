#include "guimanager.h"
#include "ui_guimanager.h"

GuiManager::GuiManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiManager)
{
    ui->setupUi(this);
}

GuiManager::~GuiManager()
{
    delete ui;
}
