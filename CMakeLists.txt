cmake_minimum_required(VERSION 3.16)

project(gameApplication VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS WebSockets)
find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(client_app
    client/main.cpp
    client/client.cpp
    client/client.h
    client/ui/mainwindow/mainwindow.cpp
    client/ui/mainwindow/mainwindow.h
    client/ui/mainwindow/mainwindow.ui
    client/ui/gamewindow/gamewindow.h
    client/ui/gamewindow/gamewindow.cpp
    client/ui/gamewindow/gamewindow.ui
)

target_link_libraries(client_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(client_app PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(client_app PRIVATE Qt6::Core)
target_link_libraries(client_app PRIVATE Qt6::WebSockets)

add_executable(server_app
    gameServer/main.cpp
    gameServer/gameServer.cpp
    gameServer/gameServer.h
)

target_link_libraries(server_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(server_app PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(server_app PRIVATE Qt6::Core)
target_link_libraries(server_app PRIVATE Qt6::WebSockets)

