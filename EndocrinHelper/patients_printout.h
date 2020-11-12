#ifndef PATIENTS_PRINTOUT_H
#define PATIENTS_PRINTOUT_H

#include <QDialog>
#include <QPrintDialog>
#include <QPrinter>
#include <QDebug>

namespace Ui {
class patients_printout;
}

class patients_printout : public QDialog
{
    Q_OBJECT

public:

    explicit patients_printout(QWidget *parent = nullptr);
    ~patients_printout();

    void setText(QString text);

private slots:
    void on_pushButton_clicked();

private:
    Ui::patients_printout *ui;
};

#endif // PATIENTS_PRINTOUT_H
