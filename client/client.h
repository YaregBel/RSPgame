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

    void connectToServer(const QUrl &url) const;
    void createRoom(const QString &roomName) const;
    void joinRoom(const QString &roomName) const;
    void sendChoice(const QString &choice) const;
    void exitRoom() const;

signals:
    void roomJoined(const QString &roomName);
    void newRoomAvailable(const QString &roomName);
    void roomRemoved(const QString &roomName);
    void errorReceived(const QString &message);
    void connectionLost();
    void gameResultReceived(const QString &result);
    void opponentLeft();

private:
    void sendJson(const QJsonObject &json) const;

private slots:
    void onConnected();
    void onMessageReceived(QString message);
    void onDisconnected();

private:
    QWebSocket *socket;

};

#endif // CLIENT_H
