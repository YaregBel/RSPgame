#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../client.h"
#include "../gamewindow/gamewindow.h"

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow(){};

private slots:
    void createRoom();
    void joinRoom();
    void openGameWindow(const QString &roomName);
    void addRoom(const QString &roomName);
    void removeRoom(const QString &roomName);
    void showError(const QString &message);

private:
    Client *client;
    QListWidget *roomList;
    QPushButton *createRoomButton;
    QPushButton *joinRoomButton;
};

#endif // MAINWINDOW_H
