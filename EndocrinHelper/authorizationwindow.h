#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QDialog>

namespace Ui {
class authorizationwindow;
}

class authorizationwindow : public QDialog
{
    Q_OBJECT

public:
    explicit authorizationwindow(QWidget *parent = nullptr);
    ~authorizationwindow();

private:
    Ui::authorizationwindow *ui;
};

#endif // AUTHORIZATIONWINDOW_H
