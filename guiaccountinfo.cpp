#include "guiaccountinfo.h"
#include "ui_guiaccountinfo.h"

guiAccountInfo::guiAccountInfo(int work, Account *acc, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::guiAccountInfo)
{
    ui->setupUi(this);

    // 1. Add
    if (work == 1){
        ui->sActive->setChecked(true);
        ui->bReset->hide();
    }

    // 2. Edit
    if (work == 2){

    }


}

guiAccountInfo::~guiAccountInfo()
{
    delete ui;
}
