#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "../../client.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

/*!
 * \brief Класс GameWindow Игровое окно для взаимодействия в игре "Камень, ножницы, бумага".
 *
 * Класс реализует графический интерфейс для игры, включая:
 * - Отображение текущего статуса игры
 * - Кнопки для выбора хода
 * - Обработку сетевого взаимодействия через класс \a Client
 */
class GameWindow : public QWidget {
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса GameWindow. Инициализация интерфейса, связывание сигналов.
     * \param client Указатель на объект \a Client для взаимодействия с сервером.
     * \param room Название комнаты, в которой проходит игра.
     * \param parent Указатель на родительский объект (по умолчанию nullptr).
     *
     * Создаёт игровое окно для игры "Камень, ножницы, бумага".
     * Инициализирует интерфейс, добавляя:
     * - Метку состояния (\a statusLabel).
     * - Кнопки выбора: "Камень" (\a rockButton), "Бумага" (\a paperButton), "Ножницы" (\a scissorsButton).
     * - Кнопку выхода (\a exitButton).
     *
     * Устанавливает связи между кнопками и методом \a sendChoice(), а также кнопкой выхода и методом \a exitGame().
     * Связывает сигналы клиента с обработчиками:
     * - \a gameResultReceived - \a updateGameStatus() (обновление результата игры).
     * - \a opponentLeft - \a handleOpponentLeft() (обработка выхода соперника).
     */
    explicit GameWindow(Client *client, const QString &room, QWidget *parent = nullptr);
    ~GameWindow(){};

private slots:
    /*!
     * \brief Отправляет выбор игрока на сервер.
     *
     * Определяет, какая кнопка была нажата (Камень, Бумага или Ножницы),
     * и отправляет соответствующий выбор через метод \a Client::sendChoice().
     * Затем обновляет статус игры, отображая выбранный ход и сообщение об ожидании соперника.
     */
    void sendChoice();
    /*!
     * \brief Обновляет статус игры в зависимости от результата.
     * \param result Строка с результатом игры ("draw", "player1" или "player2").
     *
     * В зависимости от полученного результата:
     * - "draw" - Отображается сообщение "Ничья!".
     * - "player1" - Отображается сообщение "Победил player1!".
     * - "player2" - Отображается сообщение "Победил player2!".
     *
     * После отображения результата скрываются кнопки выбора (Камень, Бумага, Ножницы).
     */
    void updateGameStatus(const QString &result);
    /*!
     * \brief Обрабатывает выход соперника из игры.
     *
     * Обновляет статус, отображая сообщение "Противник покинул игру.".
     */
    void handleOpponentLeft();
    /*!
     * \brief Выходит из комнаты и закрывает игровое окно.
     *
     * Отправляет серверу запрос на выход из комнаты через \a Client::exitRoom()
     * и закрывает окно игры.
     */
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
