#include <QCoreApplication>
#include "gameServer.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    GameServer server(24563);
    return a.exec();
}
