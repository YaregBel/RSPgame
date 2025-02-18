#include "gamewindow.h"

GameWindow::GameWindow(QWebSocket *socket, const QString &room, QWidget *parent)
    : QWidget(parent), socket(socket), roomName(room) {

    setWindowTitle("Игра: " + room);
    QVBoxLayout *layout = new QVBoxLayout(this);

    statusLabel = new QLabel("Ожидание хода...", this);
    rockButton = new QPushButton("Камень", this);
    paperButton = new QPushButton("Бумага", this);
    scissorsButton = new QPushButton("Ножницы", this);

    layout->addWidget(statusLabel);
    layout->addWidget(rockButton);
    layout->addWidget(paperButton);
    layout->addWidget(scissorsButton);

    connect(rockButton, &QPushButton::clicked, this, &GameWindow::sendChoice);
    connect(paperButton, &QPushButton::clicked, this, &GameWindow::sendChoice);
    connect(scissorsButton, &QPushButton::clicked, this, &GameWindow::sendChoice);
    connect(socket, &QWebSocket::textMessageReceived, this, &GameWindow::onMessageReceived);
}

void GameWindow::sendChoice() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    QString choice;
    if (button == rockButton) choice = "rock";
    else if (button == paperButton) choice = "paper";
    else if (button == scissorsButton) choice = "scissors";

    sendJson({{"type", "play"}, {"choice", choice}});
    statusLabel->setText("Вы выбрали: " + choice + ". Ожидание соперника...");
}

void GameWindow::onMessageReceived(QString message) {
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isObject()) return;

    QJsonObject obj = doc.object();
    QString type = obj["type"].toString();

    if (type == "game_result") {
        QString winner = obj["winner"].toString();
        if (winner == "draw") {
            statusLabel->setText("Ничья!");
        } else if (winner == "player1") {
            statusLabel->setText("Вы победили!");
        } else {
            statusLabel->setText("Вы проиграли!");
        }
    } else if (type == "opponent_left") {
        statusLabel->setText("Противник покинул игру.");
    }
}

void GameWindow::sendJson(const QJsonObject &json) {
    socket->sendTextMessage(QJsonDocument(json).toJson(QJsonDocument::Compact));
}
