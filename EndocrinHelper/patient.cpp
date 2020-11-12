#include "patient.h"
#include "ui_patient.h"

patient::patient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::patient)
{
    ui->setupUi(this);
}

patient::~patient()
{
    delete ui;
}
