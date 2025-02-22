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
    void joinRoom() const;
    void openGameWindow(const QString &roomName) const;
    void addRoom(const QString &roomName) const;
    void removeRoom(const QString &roomName) const;
    void showError(const QString &message);

private:
    Client *client;
    QListWidget *roomList;
    QPushButton *createRoomButton;
    QPushButton *joinRoomButton;
};

#endif // MAINWINDOW_H
