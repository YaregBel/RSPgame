#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), socket(new QWebSocket) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    roomList = new QListWidget(this);
    createRoomButton = new QPushButton("Создать комнату", this);
    joinRoomButton = new QPushButton("Присоединиться", this);

    layout->addWidget(roomList);
    layout->addWidget(createRoomButton);
    layout->addWidget(joinRoomButton);
    setCentralWidget(centralWidget);

    connect(createRoomButton, &QPushButton::clicked, this, &MainWindow::createRoom);
    connect(joinRoomButton, &QPushButton::clicked, this, &MainWindow::joinRoom);
    connect(socket, &QWebSocket::connected, this, &MainWindow::onConnected);
    connect(socket, &QWebSocket::textMessageReceived, this, &MainWindow::onMessageReceived);

    connectToServer();
}

MainWindow::~MainWindow() {
    socket->close();
    delete socket;
}

void MainWindow::connectToServer() {
    socket->open(QUrl("ws://localhost:24563"));
}

void MainWindow::onConnected() {
    qDebug() << "Подключено к серверу";
    sendJson({{"type", "get_rooms"}});
}

void MainWindow::onMessageReceived(QString message) {
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isObject()) return;

    QJsonObject obj = doc.object();
    QString type = obj["type"].toString();

    if (type == "room_created") {
        qDebug() << "Комната создана:" << obj["room"].toString();
        selectedRoom = obj["room"].toString();  // Сохраняем название комнаты
        GameWindow* gameWindow = new GameWindow(socket, selectedRoom);
        gameWindow->show();
    }
    else if (type == "game_start") {
        qDebug() << "Перешел в созданную комнату:" << obj["room"].toString();
        qDebug() << "Игра началась!";
        GameWindow* gameWindow2 = new GameWindow(socket, selectedRoom);
        gameWindow2->show();
    }
    else if (type == "new_room") {
        QString roomName = obj["room"].toString();
        roomList->addItem(roomName);  // Добавляем комнату в список
    }
    else if (type == "error") {
        qDebug() << "Ошибка:" << obj["message"].toString();
    }
}

void MainWindow::createRoom() {
    bool ok;
    QString roomName = QInputDialog::getText(this, "Создание комнаты", "Введите название комнаты:", QLineEdit::Normal, "", &ok);
    if (ok && !roomName.isEmpty()) {
        sendJson({{"type", "create_room"}, {"room", roomName}});
    }
}

void MainWindow::joinRoom() {
    QListWidgetItem *item = roomList->currentItem();
    if (item) {
        selectedRoom = item->text();
        sendJson({{"type", "join_room"}, {"room", selectedRoom}});
    }
}

void MainWindow::sendJson(const QJsonObject &json) {
    socket->sendTextMessage(QJsonDocument(json).toJson(QJsonDocument::Compact));
}
