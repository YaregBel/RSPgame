#ifndef SERVER_H
#define SERVER_H

#include <QCoreApplication>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QObject>

class GameServer : public QObject {
    Q_OBJECT

public:
    GameServer(quint16 port, QObject *parent = nullptr);

private slots:
    void onNewConnection();
    void onClientDisconnected();

    void broadcastMessage(const QJsonObject &message);
    void processMessage(QString message);
    void handleGameMove(QWebSocket *socket, QJsonObject obj);
    void sendToClient(QWebSocket *socket, QJsonObject message);
    void sendToRoom(const QString &roomName, QJsonObject message);

    QString determineWinner(const QString &p1, const QString &p2);

private:
    QWebSocketServer *server;
    QSet<QWebSocket *> clients;
    QMap<QString, QPair<QWebSocket *, QWebSocket *>> rooms;
    QMap<QString, QPair<QString, QString>> moves;
};

#endif // SERVER_H
