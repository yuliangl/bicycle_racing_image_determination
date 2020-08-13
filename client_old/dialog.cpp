#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->resize(700, 500);
    this->setWindowTitle("result");

}

Dialog::~Dialog()
{
    delete ui;
}
