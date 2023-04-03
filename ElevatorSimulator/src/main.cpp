#include "mainwindow.h"
#include "ElevatorControlSystem.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ElevatorControlSystem ecs(0, 0);
    MainWindow w(&ecs);
    w.show();
    return a.exec();
}
