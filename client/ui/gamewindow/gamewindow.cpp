#include "gamewindow.h"
#include <QJsonDocument>
#include <QJsonObject>

GameWindow::GameWindow(Client *client, const QString &room, QWidget *parent)
    : QWidget(parent), client(client), roomName(room)
{
    setWindowTitle("Игра: " + room);
    layout = new QVBoxLayout(this);

    statusLabel = new QLabel("Ожидание хода...", this);
    rockButton = new QPushButton("Камень", this);
    paperButton = new QPushButton("Бумага", this);
    scissorsButton = new QPushButton("Ножницы", this);
    exitButton = new QPushButton("Выйти", this);

    layout->addWidget(statusLabel);
    layout->addWidget(rockButton);
    layout->addWidget(paperButton);
    layout->addWidget(scissorsButton);
    layout->addWidget(exitButton);

    connect(rockButton, &QPushButton::clicked, this, &GameWindow::sendChoice);
    connect(paperButton, &QPushButton::clicked, this, &GameWindow::sendChoice);
    connect(scissorsButton, &QPushButton::clicked, this, &GameWindow::sendChoice);
    connect(exitButton, &QPushButton::clicked, this, &GameWindow::exitGame);

    connect(client, &Client::gameResultReceived, this, &GameWindow::updateGameStatus);
    connect(client, &Client::opponentLeft, this, &GameWindow::handleOpponentLeft);
}

void GameWindow::sendChoice()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if(!button)
    {
        return;
    }

    QString choice;
    if (button == rockButton)
    {
        choice = "rock";
    }
    else if (button == paperButton)
    {
        choice = "paper";
    }
    else if (button == scissorsButton)
    {
        choice = "scissors";
    }

    client->sendChoice(choice);
    statusLabel->setText("Вы выбрали: " + choice + ". Ожидание соперника...");
}

void GameWindow::updateGameStatus(const QString &result)
{
    if (result == "draw")
    {
        statusLabel->setText("Ничья!");
    }
    else if (result == "player1")
    {
        statusLabel->setText("Победил player1!");
    }
    else
    {
        statusLabel->setText("Победил player2!");
    }

    rockButton->hide();
    paperButton->hide();
    scissorsButton->hide();
}

void GameWindow::handleOpponentLeft()
{
    statusLabel->setText("Противник покинул игру.");
}

void GameWindow::exitGame()
{
    client->exitRoom();
    close();
}
