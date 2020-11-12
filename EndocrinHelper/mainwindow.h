#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <iostream>
#include <QPushButton>
#include <QIcon>
#include <QString>
#include <QDebug>
#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <QFile>
#include <QToolTip>
#include <QFont>
#include <QToolBar>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTime>
#include <QByteArray>
#include <QPrintDialog>
#include <QPrinter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();   
    QTcpSocket* socket;
    QByteArray data;

    QJsonDocument document;
    QJsonArray documentArray;
    QJsonParseError documentError;

    QString globalPath;
    QFile file;

    QToolBar toolbar;

    QByteArray complaint1_;
    QByteArray complaint2_;
    QByteArray complaint3_;
    QByteArray complaint4_;
    QByteArray complaint5_;
    QByteArray complaint6_;
    QByteArray complaint7_;
    QByteArray complaint8_;
    QByteArray complaint9_;
    QByteArray complaint10_;
    QByteArray complaint11_;
    QByteArray complaint12_;
    QByteArray complaint13_;
    QByteArray complaint14_;
    QByteArray complaint15_;
    QByteArray complaint16_;
    QByteArray complaint17_;
    QByteArray complaint18_;
    QByteArray complaint19_;
    QByteArray condition1_;
    QByteArray condition2_;
    QByteArray skin1_;
    QByteArray skin2_;
    QByteArray skin3_;
    QByteArray skin4_;
    QByteArray skin5_;
    QByteArray skin6_;
    QByteArray thyroid1_;
    QByteArray thyroid2_;
    QByteArray thyroid3_;
    QByteArray thyroid4_;
    QByteArray thyroid5_;
    QByteArray thyroid6_;
    QByteArray lungs1_;
    QByteArray lungs2_;
    QByteArray lungs3_;
    QByteArray heart1_;
    QByteArray heart2_;
    QByteArray heart3_;
    QByteArray stomach1_;
    QByteArray stomach2_;
    QByteArray stomach3_;
    QByteArray tremor1_;
    QByteArray tremor2_;
    QByteArray tremor3_;


public slots:
    void socketReady();
    void socketDisconnect();
    void delay();

private slots:
    void on_userloginButton_clicked();

    void on_connectButton_clicked();

    void on_actionLogin_changed();

    void on_actionLogin_triggered();

    void on_actionAdd_Patient_triggered();

    void on_pushButton_clicked();

    void grabcheckboxstate();

    void on_pushButton_2_clicked();

    void disableButtons();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_actionPrint_out_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
