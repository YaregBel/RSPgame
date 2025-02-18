#include "client.h"

Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

void Client::connectToServer(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
    if (!socket->waitForConnected(24563))
    {
        qDebug() << "Соединение разорвано!";
    }
    else
    {
        qDebug() << "Подключились к серверу";
    }
}

void Client::sendChoice(const QString &choice)
{
    if (socket->state() == QAbstractSocket::ConnectedState)
    {
        socket->write(choice.toUtf8());
    }
}

void Client::onReadyRead()
{
    QByteArray data = socket->readAll();
    QString result = QString::fromUtf8(data).trimmed();
    qDebug() << "Результат игры:" << result;
    emit gameResultReceived(result);
}

