#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "../../client.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(Client *client, const QString &room, QWidget *parent = nullptr);
    ~GameWindow(){};

private slots:
    void sendChoice();
    void updateGameStatus(const QString &result);
    void handleOpponentLeft();
    void exitGame();

private:
    Client *client;
    QString roomName;
    QLabel *statusLabel;
    QPushButton *rockButton;
    QPushButton *paperButton;
    QPushButton *scissorsButton;
    QPushButton *exitButton;
    QVBoxLayout *layout;
};

#endif // GAMEWINDOW_H
