#include "gameServer.h"

GameServer::GameServer(const quint16 port, QObject *parent) : QObject(parent),
    server(new QWebSocketServer("RockPaperServer", QWebSocketServer::NonSecureMode, this))
{

    if (server->listen(QHostAddress::Any, port))
    {
        qInfo() << "Сервер запущен на порту" << port;
        connect(server, &QWebSocketServer::newConnection, this, &GameServer::onNewConnection);
    }
    else
    {
        qInfo() << "Ошибка запуска сервера";
    }
}

void GameServer::broadcastMessage(const QJsonObject &message)
{
    QString data = QJsonDocument(message).toJson(QJsonDocument::Compact);
    for (QWebSocket *client : clients)
    {
        client->sendTextMessage(data);
    }
}

void GameServer::processMessage(const QString& message)
{
    auto socket = qobject_cast<QWebSocket *>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isObject())
    {
        return;
    }

    QJsonObject obj = doc.object();
    QString type = obj["type"].toString();

    if (type == "create_room")
    {
        QString roomName = obj["room"].toString();
        if (!rooms.contains(roomName))
        {
            rooms[roomName] = {socket, nullptr};
            sendToClient(socket, {{"type", "room_created"}, {"room", roomName}});
            broadcastMessage({{"type", "new_room"}, {"room", roomName}});
        }
        else
        {
            sendToClient(socket, {{"type", "error"}, {"message", "Комната уже существует"}});
        }
    }
    else if (type == "join_room")
    {
        QString roomName = obj["room"].toString();
        if (rooms.contains(roomName) && rooms[roomName].second == nullptr)
        {
            rooms[roomName].second = socket;
            sendToClient(socket, {{"type", "game_start"}});
        }
        else
        {
            sendToClient(socket, {{"type", "error"}, {"message", "Комната недоступна"}});
        }
    }
    else if (type == "play")
    {
        handleGameMove(socket, obj);
    }
    else if (type == "exit")
    {
        QString roomName = getSocketsRoomName(socket);
        qDebug() << "GameServer получил указания по удалению данных о комнате" << roomName;
        broadcastMessage({{{"type", "exit"}, {"room", roomName}}});
        exitGame(roomName);
    }
    else if (type == "restart")
    {
        QString roomName = obj["room"].toString();
        qInfo("GameServer получил задание по обновлению комнаты для еще одного раунда.");
        sendToClient(socket, {{"type", "restart_room"}});
        restartGame(roomName);
    }
}

void GameServer::handleGameMove(const QWebSocket *socket, const QJsonObject& obj)
{
    QString choice = obj["choice"].toString();
    QString roomName = getSocketsRoomName(socket);

    if(roomName  == "")
    {
        return;
    }

    auto &room = rooms[roomName];
    if (room.first == socket)
    {
        moves[roomName].first = choice;
    }
    else if (room.second == socket)
    {
        moves[roomName].second = choice;
    }

    if (!moves[roomName].first.isEmpty() && !moves[roomName].second.isEmpty())
    {
        QString winner = determineWinner(moves[roomName].first, moves[roomName].second);
        sendToRoom(roomName, {{"type", "game_result"}, {"winner", winner}});
    }
}

QString GameServer::determineWinner(const QString &p1, const QString &p2)
{
    if (p1 == p2)
    {
        return "draw";
    }
    if ((p1 == "rock" && p2 == "scissors") || (p1 == "scissors" && p2 == "paper") || (p1 == "paper" && p2 == "rock"))
    {
        qInfo("Player1 победил!");
        return "player1";
    }

    qInfo("Player2 победил!");
    return "player2";
}

void GameServer::sendToClient(QWebSocket *socket, const QJsonObject& message)
{
    socket->sendTextMessage(QJsonDocument(message).toJson(QJsonDocument::Compact));
}

void GameServer::sendToRoom(const QString &roomName, const QJsonObject& message)
{
    auto room = rooms[roomName];
    if (room.first)
    {
        sendToClient(room.first, message);
    }
    if (room.second)
    {
        sendToClient(room.second, message);
    }
}

void GameServer::onNewConnection()
{
    auto socket = server->nextPendingConnection();
    connect(socket, &QWebSocket::textMessageReceived, this, &GameServer::processMessage);
    connect(socket, &QWebSocket::disconnected, this, &GameServer::onClientDisconnected);
    clients.insert(socket);
    qInfo() << "Новый клиент подключился";
}

void GameServer::onClientDisconnected()
{
    qInfo("OnClientDisconnected отработал");
    auto socket = qobject_cast<QWebSocket *>(sender());
    for (auto it = rooms.begin(); it != rooms.end();)
    {
        if (it.value().first == socket || it.value().second == socket)
        {
            sendToRoom(it.key(), {{"type", "opponent_left"}});
            moves.remove(it.key());
            it = rooms.erase(it);
        }
        else
        {
            ++it;
        }
    }
    clients.remove(socket);
    socket->deleteLater();
}

QString GameServer::getSocketsRoomName(const QWebSocket *socket)
{
    for (auto it = rooms.begin(); it != rooms.end(); ++it)
    {
        if (it.value().first == socket || it.value().second == socket)
        {
            it.key();
            return it.key();
        }
    }
    return "";
}

void GameServer::restartGame(const QString &roomName)
{
    qInfo("GameServer перезапустил комнату");
    moves.remove(roomName);
}

void GameServer::exitGame(const QString &roomName)
{
    qInfo("GameServer приступил к очистке данных о комнате.");

    rooms.remove(roomName);
    moves.remove(roomName);
}
