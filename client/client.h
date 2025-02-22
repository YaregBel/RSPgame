#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    void connectToServer(const QUrl &url);
    void createRoom(const QString &roomName);
    void joinRoom(const QString &roomName);

signals:
    void roomJoined(const QString &roomName);
    void newRoomAvailable(const QString &roomName);
    void roomRemoved(const QString &roomName);
    void errorReceived(const QString &message);
    void connectionLost();

private:
    QWebSocket *socket;

    void sendJson(const QJsonObject &json);

private slots:
    void onConnected();
    void onMessageReceived(QString message);
    void onDisconnected();
};

#endif // CLIENT_H
