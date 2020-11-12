#ifndef PATIENT_H
#define PATIENT_H

#include <QWidget>
#include <QDialog>
#include <QDebug>

namespace Ui {
class patient;
}

class patient : public QWidget
{
    Q_OBJECT

public:
    explicit patient(QWidget *parent = nullptr);
    ~patient();

private:
    Ui::patient *ui;
};

#endif // PATIENT_H
