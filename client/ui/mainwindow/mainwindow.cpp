#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), client(new Client(this))
{
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

    connect(client, &Client::roomJoined, this, &MainWindow::openGameWindow);
    connect(client, &Client::newRoomAvailable, this, &MainWindow::addRoom);
    connect(client, &Client::roomRemoved, this, &MainWindow::removeRoom);
    connect(client, &Client::errorReceived, this, &MainWindow::showError);

    client->connectToServer(QUrl("ws://localhost:24563"));
}

void MainWindow::createRoom()
{
    bool ok;
    QString roomName = QInputDialog::getText(this, "Создание комнаты", "Введите название комнаты:", QLineEdit::Normal, "", &ok);
    if (ok && !roomName.isEmpty())
    {
        client->createRoom(roomName);
    }
}

void MainWindow::joinRoom() const
{
    QListWidgetItem *item = roomList->currentItem();
    if (item)
    {
        client->joinRoom(item->text());
    }
}

void MainWindow::openGameWindow(const QString &roomName) const
{
    GameWindow *gameWindow = new GameWindow(client, roomName);
    gameWindow->show();
}

void MainWindow::addRoom(const QString &roomName) const
{
    roomList->addItem(roomName);
}

void MainWindow::removeRoom(const QString &roomName) const
{
    for (int i = 0; i < roomList->count(); ++i)
    {
        if (roomList->item(i)->text() == roomName)
        {
            delete roomList->takeItem(i);
            break;
        }
    }
}

void MainWindow::showError(const QString &message)
{
    QMessageBox::warning(this, "Ошибка", message);
}
