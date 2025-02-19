#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "../../../gameServer/gameServer.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>


class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(QWebSocket *socket, const QString &room, QWidget *parent = nullptr);

private slots:
    void sendChoice();
    void onMessageReceived(QString message);

private:
    QWebSocket *socket;
    QString roomName;
    QLabel *statusLabel;
    QPushButton *rockButton;
    QPushButton *paperButton;
    QPushButton *scissorsButton;
    QPushButton *restartButton;
    QPushButton *exitButton;

    void sendJson(const QJsonObject &json);
};

#endif // GAMEWINDOW_H
