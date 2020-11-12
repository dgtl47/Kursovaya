#include "patients_printout.h"
#include "ui_patients_printout.h"

patients_printout::patients_printout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::patients_printout)
{
    ui->setupUi(this);

    ui->textEdit->setFont(QFont("Times", 12));
}

patients_printout::~patients_printout()
{
    delete ui;
}

void patients_printout::on_pushButton_clicked()
{
    QPrinter printer;
    printer.setPrinterName("HP");
    QPrintDialog dialog(&printer,this);
    if (dialog.exec() == QDialog::Rejected) return;
    ui->textEdit->print(&printer);
}

void patients_printout::setText(QString text) {
    ui->textEdit->setText(text);
}
