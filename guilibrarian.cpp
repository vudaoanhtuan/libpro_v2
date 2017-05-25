#include "guilibrarian.h"
#include "ui_guilibrarian.h"

GuiLibrarian::GuiLibrarian(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiLibrarian)
{
    ui->setupUi(this);
}

GuiLibrarian::~GuiLibrarian()
{
    delete ui;
}
