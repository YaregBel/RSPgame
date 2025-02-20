#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

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

    void restartGame();
    void exitGame();


private:
    QWebSocket *socket;
    QString roomName;
    QLabel *statusLabel;
    QPushButton *rockButton;
    QPushButton *paperButton;
    QPushButton *scissorsButton;
    QPushButton *restartButton;
    QPushButton *exitButton;
    QVBoxLayout *layout;

    void sendJson(const QJsonObject &json);
};

#endif // GAMEWINDOW_H
