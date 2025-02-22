#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>

class Client : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Client::Client конструктор класса Client, инициализация QWebSocket.
     * \param parent - Указатель на родительский объект
     *
     * Данном конструкторе происходит инициализация объекта типа QWebSocket и связывание его
     * сигналов со слотами:
     * - connected - вызывается слот \a onConnected() при успешном подключении
     * - textMessageReceived - вызывается слот \a onMessageReceived() при получении сообщения
     * - disconnected - вызывается слот \a onDisconnected() при разрыве соединения клиента с сервером
     */
    explicit Client(QObject *parent = nullptr);
    /*!
     * \brief Client::connectToServer метод используется для подключения к серверу.
     * \param url URL сервера, к которому нужно подключиться
     *
     * Проверяет подключен ли сокет к серверу, если да, то выводится сообщение об успешном подключении,
     * иначе вызывается метод open() для инициации подключения.
     */
    void connectToServer(const QUrl &url) const;
    /*!
     * \brief Client::createRoom отправляет запрос на создание комнаты.
     * \param roomName Название комнаты, которую нужно создать.
     *
     * Формирует JSON-объект с типом "create_room" и именем комнаты, затем отправляет его серверу.
     */
    void createRoom(const QString &roomName) const;
    /*!
     * \brief Client::joinRoom отправляет запрос на вход в уже созданную комнату.
     * \param roomName Название комнаты, в которую нужно найти.
     *
     * Формирует JSON-объект с типом "join_room" и именем комнаты, затем отправляет его серверу.
     */
    void joinRoom(const QString &roomName) const;
    /*!
     * \brief Client::sendChoice отправляет выбор игрока в игре.
     * \param choice Выбранное действие ("камень", "ножницы" или "бумага").
     *
     * Формирует JSON-объект с типом "play" и переданным выбором, затем отправляет его серверу.
     */
    void sendChoice(const QString &choice) const;
    /*!
     * \brief Client::exitRoom отправляет запрос на выход из комнаты.
     *
     * Формирует JSON-объект с типом "exit" и отправляет его серверу
     */
    void exitRoom() const;

signals:
    void roomJoined(const QString &roomName);
    void newRoomAvailable(const QString &roomName);
    void roomRemoved(const QString &roomName);
    void errorReceived(const QString &message);
    void connectionLost();
    void gameResultReceived(const QString &result);
    void opponentLeft();

private:
    /*!
     * \brief Client::sendJson отправляет JSON-объект серверу через QWebSocket.
     * \param json JSON-объект, который нужно отправить.
     *
     * Преобразует переданный JSON в строку и отправляет его с помощью QWebSocket.
     */
    void sendJson(const QJsonObject &json) const;

private slots:
    /*!
     * \brief Client::onConnected слот срабатывает при подключении к серверу
     *
     * Выводит сообщение о подключении в лог и отправляет запрос на получение списка доступных комнат,
     * отправляя серверу JSON-сообщение с типом "get_rooms".
     */
    void onConnected();
    /*!
     * \brief Обрабатывает отключение от сервера.
     *
     * Выводит сообщение в лог о разрыве соединения и испускает сигнал \a connectionLost(),
     * уведомляя другие компоненты о потере соединения.
     */
    void onDisconnected();
    /*!
     * \brief Обрабатывает полученное сообщение от сервера WebSocket.
     * \param message Строка с JSON-сообщением от сервера
     *
     * Проверка на существование JSON-объекта, далее его парсинг в JSON объект и получение значения поля "type"
     * преобразованного в строку, и уже исходя из значения, происходит следующее:
     * - \a "room_created" или \a "game_start" - испускается сигнал \a roomJoined() с именем комнаты.
     * - \a "new_room" - испускается сигнал \a newRoomAvailable() с именем новой комнаты.
     * - \a "error" - испускается сигнал \a errorReceived() с текстом ошибки
     * - \a "exit" - испускается сигнал \a roomRemoved() с именем комнаты
     * - \a "game_result" - испускается сигнал \a gameResultReceived() с именем победителя.
     * - \a "opponent_left" - испускается сигнал \a opponentLeft(), уведомляющий об уходе соперника
     *
     * Если варианта не предусмотрено, сообщение игнорируется.
     */
    void onMessageReceived(QString message);

private:
    QWebSocket *socket;

};

#endif // CLIENT_H
