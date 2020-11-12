#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class authdialog;
}

class authdialog : public QDialog
{
    Q_OBJECT

public:

    QString login;
    QString password;
    explicit authdialog(QWidget *parent = nullptr);
    ~authdialog();

private slots:
    void on_loginButton_clicked();

    void on_loginLineEdit_textChanged(const QString &arg1);

    void on_passwordLineEdit_textChanged(const QString &arg1);

    void on_loginButtonBox_accepted();

    void on_buttonBox_accepted();

private:
    Ui::authdialog *ui;
};

#endif // AUTHDIALOG_H
