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
    /*!
     * \brief Конструктор класса MainWindow. Создает объект класса Client.
     * \param parent Указатель на родительский объект (по умолчанию nullptr).
     *
     * Создаёт главное окно приложения, инициализирует графический интерфейс, включая:
     * - Список комнат (\a roomList).
     * - Кнопки "Создать комнату" - \a createRoomButton и "Присоединиться" - \a joinRoomButton.
     *
     * Устанавливает центральный виджет и связывает сигналы с соответствующими слотами:
     * - Нажатие кнопок вызывает методы \a createRoom() и \a joinRoom().
     * - Сигналы от клиента (\a Client) связываются с методами для обновления интерфейса и обработки событий.
     *
     * После инициализации выполняется подключение к серверу QWebSocket по адресу "ws://localhost:24563".
     */
    explicit MainWindow(QWidget *parent = nullptr);
    /*!
     * \brief Деструктор класса MainWindow.
     */
    ~MainWindow(){};

private slots:
    /*!
     * \brief Открывает диалог для создания новой комнаты.
     *
     * Отображает всплывающее окно ввода, предлагая пользователю ввести название новой комнаты.
     * Если пользователь подтвердил ввод и строка не пустая, отправляет запрос на создание комнаты
     * через метод \a Client::createRoom().
     */
    void createRoom();
    /*!
     * \brief Метод служит для входа в комнату.
     *
     * В методе MainWindow::joinRoom() происходит получение выбранной комнаты, в списке существующих комнат,
     * далее происходит проверка на то, что элемент выбран, после чего название комнаты передается в метод
     * client::joinRoom, для последующей передачи серверу.
     */
    void joinRoom() const;
    /*!
     * \brief Метод служит для входа в комнату.
     * \param roomName Название комнаты
     *
     * В методе MainWindow::openGameWindow() происходит создание игрового окна, для определенного
     * клиента, который подключился к комнате с названием roomName. После чего происходит открытие окна.
     */
    void openGameWindow(const QString &roomName) const;
    /*!
     * \brief Метод служит для добавления комнаты в список комнат
     * \param roomName Название комнаты
     *
     * Метод MainWindow::addRoom() используется для добавления комнаты, с именем roomName в список всех
     * комнат \a roomList.
     */
    void addRoom(const QString &roomName) const;
    /*!
     * \brief Метод служит для удаления комнаты.
     * \param roomName Название комнаты
     *
     * В методе MainWindow::removeRoom() происходит прохождения по всем комнатам в списке, если же название комнаты
     * совпадает с тем, которое было передано в метод, она удаляется из списка и производится выход из цикла.
     */
    void removeRoom(const QString &roomName) const;
    /*!
     * \brief Метод служит для уведомления пользователя об ошибке.
     * \param message сообщение с ошибкой
     *
     * Метод MainWindow::showError() служит для создания диалогового окна с ошибкой, для уведомления пользователя.
     */
    void showError(const QString &message);

private:
    Client *client;
    QListWidget *roomList;
    QPushButton *createRoomButton;
    QPushButton *joinRoomButton;
};

#endif // MAINWINDOW_H
