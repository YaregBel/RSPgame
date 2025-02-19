#include "client.h"

Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
}

void Client::connectToServer(const QString &host, quint16 port)
{
    // Проверяем текущее состояние подключения
    if (socket->state() == QAbstractSocket::ConnectedState)
    {
        qDebug() << "Уже подключен к серверу";
        return;
    }

    socket->connectToHost(host, port);

    if (!socket->waitForConnected(24563))
    {
        qDebug() << "Не удалось подключиться:" << socket->errorString();
    }
    else
    {
        qDebug() << "Успешное подключение к серверу";
        m_isInRoom = true; // Устанавливаем флаг в комнате
    }
}

void Client::onDisconnected()
{
    qDebug() << "Отключен от сервера";
    m_isInRoom = false; // Сбрасываем флаг при отключении
    emit connectionLost();
}

void Client::sendChoice(const QString &choice)
{
    // Отправляем только если подключены и находимся в комнате
    if (socket->state() == QAbstractSocket::ConnectedState && m_isInRoom)
    {
        socket->write(choice.toUtf8());
    }
}

// Остальные методы без изменений
void Client::onReadyRead()
{
    QByteArray data = socket->readAll();
    QString result = QString::fromUtf8(data).trimmed();
    qDebug() << "Результат игры:" << result;
    emit gameResultReceived(result);
}

