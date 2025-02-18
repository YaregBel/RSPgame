#include "gameServer.h"

GameServer::GameServer(quint16 port, QObject *parent)
    : QObject(parent), server(new QWebSocketServer("RockPaperServer", QWebSocketServer::NonSecureMode, this)) {

    if (server->listen(QHostAddress::Any, port)) {
        qDebug() << "Сервер запущен на порту" << port;
        connect(server, &QWebSocketServer::newConnection, this, &GameServer::onNewConnection);
    } else {
        qDebug() << "Ошибка запуска сервера";
    }
}
void GameServer::onNewConnection() {
    auto socket = server->nextPendingConnection();
    connect(socket, &QWebSocket::textMessageReceived, this, &GameServer::processMessage);
    connect(socket, &QWebSocket::disconnected, this, &GameServer::onClientDisconnected);
    clients.insert(socket);
    qDebug() << "Новый клиент подключился";
}

void GameServer::broadcastMessage(const QJsonObject &message) {
    QString data = QJsonDocument(message).toJson(QJsonDocument::Compact);
    for (QWebSocket *client : clients) {
        client->sendTextMessage(data);
    }
}

void GameServer::processMessage(QString message) {
    auto socket = qobject_cast<QWebSocket *>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isObject()) return;

    QJsonObject obj = doc.object();
    QString type = obj["type"].toString();

    if (type == "create_room") {
        QString roomName = obj["room"].toString();
        if (!rooms.contains(roomName)) {
            rooms[roomName] = {socket, nullptr}; // Первый игрок создаёт комнату
            sendToClient(socket, {{"type", "room_created"}, {"room", roomName}});

            // Отправляем уведомление всем клиентам
            QJsonObject update;
            update["type"] = "new_room";
            update["room"] = roomName;
            broadcastMessage(update);
        } else {
            sendToClient(socket, {{"type", "error"}, {"message", "Комната уже существует"}});
        }
    }
    else if (type == "join_room") {
        QString roomName = obj["room"].toString();
        if (rooms.contains(roomName) && rooms[roomName].second == nullptr) {
            rooms[roomName].second = socket; // Второй игрок присоединяется
            sendToRoom(roomName, {{"type", "game_start"}});
        } else {
            sendToClient(socket, {{"type", "error"}, {"message", "Комната недоступна"}});
        }
    } else if (type == "play") {
        handleGameMove(socket, obj);
    }
}

void GameServer::handleGameMove(QWebSocket *socket, QJsonObject obj) {
    QString choice = obj["choice"].toString();
    QString roomName;
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        if (it->first == socket || it->second == socket) {
            roomName = it.key();
            break;
        }
    }
    if (roomName.isEmpty()) return;

    auto &room = rooms[roomName];
    if (room.first == socket) moves[roomName].first = choice;
    else if (room.second == socket) moves[roomName].second = choice;

    if (!moves[roomName].first.isEmpty() && !moves[roomName].second.isEmpty()) {
        QString winner = determineWinner(moves[roomName].first, moves[roomName].second);
        sendToRoom(roomName, {{"type", "game_result"}, {"winner", winner}});
        moves.remove(roomName);
    }
}

QString GameServer::determineWinner(const QString &p1, const QString &p2) {
    if (p1 == p2) return "draw";
    if ((p1 == "rock" && p2 == "scissors") || (p1 == "scissors" && p2 == "paper") || (p1 == "paper" && p2 == "rock"))
        return "player1";
    return "player2";
}

void GameServer::onClientDisconnected() {
    auto socket = qobject_cast<QWebSocket *>(sender());
    for (auto it = rooms.begin(); it != rooms.end();) {
        if (it->first == socket || it->second == socket) {
            sendToRoom(it.key(), {{"type", "opponent_left"}});
            it = rooms.erase(it);
        } else {
            ++it;
        }
    }
    clients.remove(socket);
    socket->deleteLater();
}

void GameServer::sendToClient(QWebSocket *socket, QJsonObject message) {
    socket->sendTextMessage(QJsonDocument(message).toJson(QJsonDocument::Compact));
}

void GameServer::sendToRoom(const QString &roomName, QJsonObject message) {
    auto room = rooms[roomName];
    if (room.first) sendToClient(room.first, message);
    if (room.second) sendToClient(room.second, message);
}
