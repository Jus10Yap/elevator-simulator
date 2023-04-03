#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Subject.h"
#include "Observer.h"
#include "ElevatorControlSystem.h"
QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    MainWindow(ElevatorControlSystem *ecs, QWidget *parent = nullptr);
    ~MainWindow();
    void update(Subject *subj);

private:
    Ui::MainWindow *ui;
    // void init();
    ElevatorControlSystem *ecs;

private slots:
    // PUSH BUTTONS
    void startSimulation();
    void next();
    void fire();
    void buildFire();
    void obstacles();
    void overload();
    void help();
    void pushed();
    void powerOutage();
    void up();
    void down();
    void close();
    void open();

    //populate
    void populateElevatorsDropdown();
    void populateFloorsDropdown();
    void populateFloorDropdown(int floors);
    void populateElevatorDropdown(int elevators);
    void populateTable(int floors, int elevators);

    //tables
    void displayPositions();
    void displayMessage(int c);
};
#endif // MAINWINDOW_H
