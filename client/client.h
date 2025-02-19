#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>


class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    void connectToServer(const QString &host, quint16 port);
    void sendChoice(const QString &choice);

private:
    QTcpSocket *socket;
    bool m_isInRoom = false;


signals:
    void gameResultReceived(const QString &result);
    void sendRoomList(QWebSocket *socket);
    void connectionLost();


private slots:
    void onReadyRead();
    void onDisconnected();


};

#endif // CLIENT_H
