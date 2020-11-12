#include "server.h"

server::server(){}

server::~server(){}

void server::serverON()
{
    if (this->listen(QHostAddress::Any,5555))
    {
        qDebug() << "The server is running...";
    }
    else
    {
        qDebug() << "The server is down...";
    }
}

void server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket,SIGNAL(readyRead()),this,SLOT(socketReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(socketDisconnect()));

    qDebug() << "Client is connected, uniq number: " << socketDescriptor;

    socket->write("{\"type\":\"connect\",\"value\":\"correct\"}");
}

void server::socketReady()
{
    data = socket->readAll(); // прием запроса от клиента в .json формате

    QString loginsubstring = data.mid(9,5);
    QString passwordsubstring = data.mid(30,8);
    QString usersubstring = data.mid(12,4);
    QString user = data.mid(12,5);
    QString username = data.mid (33,5); // для запроса данных конкретного пациента
    QString patientInfo = data.mid(49, 40);
    patientInfo.remove(QRegExp("[,});\"]+"));

    qDebug() << "Data" << data; // отправка данных запроса на консоль отладки в формате .json

    document = QJsonDocument::fromJson(data,&documentError); // сохранение в переменной document всех данных запроса, ошибок

        if ((loginsubstring == "login") && (passwordsubstring == "password"))
        {
            QFile file("C:\\Users\\79788\\Documents\\serverJSON\\user\\user.json");
            if (!file.open(QIODevice::ReadOnly))
                {
                   qDebug()<< "Error! File is not open";
                }
            QByteArray JSONdata = file.readAll();
            file.close();

            QJsonDocument document1(QJsonDocument::fromJson(JSONdata));
            QJsonObject object = document1.object();

            QJsonValue JSONArrayValue = object.value("usersArray");
            QJsonArray JSONArray = JSONArrayValue.toArray();

            loginsubstring = data.mid(15,5);
            passwordsubstring = data.mid(39,8);

            int count = 0;

            foreach (const QJsonValue & v, JSONArray)
            {
                if ((v.toObject().value("login").toString() == loginsubstring) && (v.toObject().value("password").toString() == passwordsubstring))
                {
                    socket->write("{\"type\":\"user\",\"value\":\"success\"}");
                    continue;
                }
                count++;
            }
            if (count == 9)
            {
                socket->write("{\"type\":\"user\",\"value\":\"failed\"}");
            }
        }

        if ((documentError.errorString()=="no error occurred"))
        {
            if ((document.object().value("login").toString() == user) && (document.object().value("type").toString() == "save"))
            {
                qDebug() << "WORK";
                QFile file("C:\\Users\\79788\\Documents\\serverJSON\\user\\"+user+".json");

                if (!file.open(QIODevice::ReadOnly))
                    {
                    qDebug()<< "Error! File is not open";
                    }

                QByteArray JSONdata = file.readAll();
                file.close();

                QJsonObject objectfile = QJsonDocument::fromJson(JSONdata).object();
                QJsonObject objectdata = QJsonDocument::fromJson(data).object();

                QJsonArray a = objectfile["patientArray"].toArray(); //вычленяем массив json'ов
                a.append(objectdata);
                objectfile.insert("patientArray", a);

                QJsonDocument document1(objectfile);
                QJsonObject object = document1.object();

                file.open(QIODevice::WriteOnly);
                file.write(QJsonDocument(document1.object()).toJson());
                file.close();
            }
            else if ((document.object().value("login").toString() == user) && (document.object().value("patient").toString() == "list"))
            {
                qDebug() << "Its work";
                QFile file("C:\\Users\\79788\\Documents\\serverJSON\\user\\"+user+".json");

                if (!file.open(QIODevice::ReadOnly))
                    {
                       qDebug()<< "Error! File is not open";
                    }

                QByteArray JSONdata = file.readAll();
                file.close();

                socket->write(JSONdata);
            }
            else if ((document.object().value("patientname").toString() == "YES"))
            {
                QFile file("C:\\Users\\79788\\Documents\\serverJSON\\user\\"+username+".json");

                if (!file.open(QIODevice::ReadOnly))
                    {
                       qDebug()<< "Error! File is not open";
                    }

                QByteArray JSONdata = file.readAll();
                file.close();

                QJsonDocument document1(QJsonDocument::fromJson(JSONdata));
                QJsonObject object = document1.object();

                QJsonValue JSONArrayValue = object.value("patientArray");
                QJsonArray JSONArray = JSONArrayValue.toArray();
                QByteArray patientinfo_ = patientInfo.toUtf8();;

                int counter = 0;

                foreach (const QJsonValue & v, JSONArray)
                {
                    if ((v.toObject().value("surname").toString() + " " + v.toObject().value("name").toString() + " " + v.toObject().value("patronymic").toString() == patientInfo))
                    {
                        QJsonObject object_JSONArray = JSONArray[counter].toObject();
                        QJsonDocument doc_JSONArray(object_JSONArray);
                        QString strJSONArray(doc_JSONArray.toJson(QJsonDocument::Compact));
                        QByteArray summary = strJSONArray.toUtf8();

                        socket->write(summary);
                    }
                    counter++;

                }
            }
        }
}

void server::socketDisconnect()
{
    socket->deleteLater();
    qDebug() << "Disconnect";
}
