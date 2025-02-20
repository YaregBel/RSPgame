#include "gamewindow.h"

GameWindow::GameWindow(QWebSocket *socket, const QString &room, QWidget *parent)
    : QWidget(parent), socket(socket), roomName(room) {

    setWindowTitle("Игра: " + room);
    layout = new QVBoxLayout(this);

    statusLabel = new QLabel("Ожидание хода...", this);
    rockButton = new QPushButton("Камень", this);
    paperButton = new QPushButton("Бумага", this);
    scissorsButton = new QPushButton("Ножницы", this);

    //restartButton = new QPushButton("Переиграть", this);
    exitButton = new QPushButton("Выйти", this);

    layout->addWidget(statusLabel);
    layout->addWidget(rockButton);
    layout->addWidget(paperButton);
    layout->addWidget(scissorsButton);
    layout->addWidget(exitButton);

    connect(rockButton, &QPushButton::clicked, this, &GameWindow::sendChoice);
    connect(paperButton, &QPushButton::clicked, this, &GameWindow::sendChoice);
    connect(scissorsButton, &QPushButton::clicked, this, &GameWindow::sendChoice);
    connect(socket, &QWebSocket::textMessageReceived, this, &GameWindow::onMessageReceived);

    connect(exitButton, &QPushButton::clicked, this, &GameWindow::exitGame);
    connect(exitButton, &QPushButton::clicked, this, &GameWindow::close);

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
            statusLabel->setText("Победил player1!");
        } else {
            statusLabel->setText("Победил player2!");
        }

        scissorsButton->hide();
        rockButton->hide();
        paperButton->hide();


        layout->addWidget(restartButton);
        layout->addWidget(exitButton);

        //connect(restartButton, &QPushButton::clicked, this, &GameWindow::restartGame);

    } else if (type == "opponent_left") {
        statusLabel->setText("Противник покинул игру.");
    }
}

void GameWindow::sendJson(const QJsonObject &json) {
    socket->sendTextMessage(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

void GameWindow::restartGame()
{
    // Здесь нужно реализовать логику очистки ходов для комнаты,
    // или же переработать структуру, например, добавить поле раундов,
    // Чтобы ходы в комнате сделанные в разные раунды отличались в хранимой структуре

    // layout->removeWidget(restartButton);
    // layout->removeWidget(exitButton);

    // Ну и сброс текстового поле, видимо лучше реализовать в GameWindow
}

void GameWindow::exitGame()
{
    qDebug("Уведомление GameServer'a о необходимости удаления комнаты.");
    sendJson({{"type", "exit"}});

    // rooms.remove(roomName);
    // moves.remove(roomName);

    // Затем надо удалить игровое окно для конкретного клиента.
    // И уведомить оппонента о том, что вы покинули комнату.
    // Как будто это следует делать в GameWindow
}
