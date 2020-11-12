#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>

class server: public QTcpServer
{
    Q_OBJECT // делаем класс объектным
public:
    server();
    ~server();

    QTcpSocket* socket; // интерфейс для передачи данных между клиентом и сервером (содержит параметры адреса и порта)
    QByteArray data; // через эту переменную передаем данные по сокету

    QJsonDocument document;
    QJsonParseError documentError;

public slots:
    void serverON();
    void incomingConnection(qintptr socketDescriptor);
    void socketReady();
    void socketDisconnect();

};

#endif // SERVER_H
