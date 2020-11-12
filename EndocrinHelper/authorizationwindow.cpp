#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"

authorizationwindow::authorizationwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authorizationwindow)
{
    ui->setupUi(this);
}

authorizationwindow::~authorizationwindow()
{
    delete ui;
}
