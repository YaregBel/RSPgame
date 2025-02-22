#include "client.h"
#include <QJsonDocument>
#include <QJsonObject>

Client::Client(QObject *parent) : QObject(parent), socket(new QWebSocket)
{
    connect(socket, &QWebSocket::connected, this, &Client::onConnected);
    connect(socket, &QWebSocket::textMessageReceived, this, &Client::onMessageReceived);
    connect(socket, &QWebSocket::disconnected, this, &Client::onDisconnected);
}

void Client::connectToServer(const QUrl &url) const
{
    if (socket->state() == QAbstractSocket::ConnectedState)
    {
        qInfo() << "Уже подключен к серверу";
        return;
    }
    socket->open(url);
}

void Client::onConnected()
{
    qInfo() << "Подключено к серверу";
    sendJson({{"type", "get_rooms"}});
}

void Client::onDisconnected()
{
    qInfo() << "Отключено от сервера";
    emit connectionLost();
}

void Client::onMessageReceived(QString message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isObject())
    {
        return;
    }

    QJsonObject obj = doc.object();
    QString type = obj["type"].toString();

    if (type == "room_created" || type == "game_start")
    {
        emit roomJoined(obj["room"].toString());
    }
    else if (type == "new_room")
    {
        emit newRoomAvailable(obj["room"].toString());
    }
    else if (type == "error")
    {
        emit errorReceived(obj["message"].toString());
    }
    else if (type == "exit")
    {
        emit roomRemoved(obj["room"].toString());
    }
    else if (type == "game_result")
    {
        emit gameResultReceived(obj["winner"].toString());
    }
    else if (type == "opponent_left")
    {
        emit opponentLeft();
    }
}

void Client::createRoom(const QString &roomName) const
{
    sendJson({{"type", "create_room"}, {"room", roomName}});
}

void Client::joinRoom(const QString &roomName) const
{
    sendJson({{"type", "join_room"}, {"room", roomName}});
}

void Client::sendChoice(const QString &choice) const
{
    sendJson({{"type", "play"}, {"choice", choice}});
}

void Client::exitRoom() const
{
    sendJson({{"type", "exit"}});
}

void Client::sendJson(const QJsonObject &json) const
{
    socket->sendTextMessage(QJsonDocument(json).toJson(QJsonDocument::Compact));
}
