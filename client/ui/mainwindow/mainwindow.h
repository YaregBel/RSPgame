#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../gamewindow/gamewindow.h"

#include <QMainWindow>
#include <QWebSocket>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QInputDialog>
#include <QDebug>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void connectToServer();
    void onConnected();
    void onMessageReceived(QString message);
    void createRoom();
    void joinRoom();

private:
    QWebSocket *socket;
    QListWidget *roomList;
    QPushButton *createRoomButton;
    QPushButton *joinRoomButton;
    QString selectedRoom;

    void sendJson(const QJsonObject &json);
};

#endif // MAINWINDOW_H
