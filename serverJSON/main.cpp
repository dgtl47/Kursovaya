#include <QCoreApplication>
#include <server.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    server Server;
    Server.serverON();

    return a.exec();
}
