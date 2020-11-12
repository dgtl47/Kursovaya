#include "authdialog.h"
#include "ui_authdialog.h"

authdialog::authdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authdialog)
{
    ui->setupUi(this);
}

authdialog::~authdialog()
{
    delete ui;
}

void authdialog::on_loginButton_clicked()
{
    login = ui->loginLineEdit->text();
    password = ui->passwordLineEdit->text();
    authdialog::close();
}
