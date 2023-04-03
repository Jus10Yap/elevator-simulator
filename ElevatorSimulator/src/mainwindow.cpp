#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ElevatorControlSystem.h"
#include "Elevator.h"
#include "ButtonPanel.h"
#include "Subject.h"
#include"Display.h"
#include"Door.h"
#include"DoorSensor.h"
#include "Observer.h"
#include "defs.h"

#include <string>

MainWindow::MainWindow(ElevatorControlSystem *ecs, QWidget *parent)
    : ecs(ecs), QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ecs->attach(this);

    // populating combo boxes
    populateElevatorsDropdown();
    populateFloorsDropdown();

    // push buttons
    connect(ui->simulate, SIGNAL(clicked()), this, SLOT(startSimulation())); // start simulation
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::update(Subject *subj)
{
    // updating ui
    displayPositions();
}

// starting elevator simulation
void MainWindow::startSimulation()
{
    // lock
    ui->simulate->setDisabled(true);
    ui->elevatorsDrop->setDisabled(true);
    ui->floorsDrop->setDisabled(true);

    qInfo("[MainWindow] Starting Simulation..");

    // get amount of floors and elevators based on current index selected
    int floors = ui->floorsDrop->currentIndex();
    int elevators = ui->elevatorsDrop->currentIndex();

    // populate floor and elevator combo boxes
    populateFloorDropdown(floors);
    populateElevatorDropdown(elevators);

    // populate table
    populateTable(floors, elevators);

    // initalize ecs
    ecs->setNumFloors(floors);
    ecs->setNumElevators(elevators);
    ecs->init(floors, elevators);

    // update display
    displayPositions();

    // initialized all push buttons
    connect(ui->next, SIGNAL(clicked()), this, SLOT(next()));             // next
    connect(ui->fireButt, SIGNAL(clicked()), this, SLOT(fire()));         // fire inside elevator
    connect(ui->buildFire, SIGNAL(clicked()), this, SLOT(buildFire()));         // fire inside elevator
    connect(ui->overloadButt, SIGNAL(clicked()), this, SLOT(overload())); // overload
    connect(ui->blockButt, SIGNAL(clicked()), this, SLOT(obstacles()));   // obstacles
    connect(ui->powerButt, SIGNAL(clicked()), this, SLOT(powerOutage())); // power outage
    connect(ui->help, SIGNAL(clicked()), this, SLOT(help()));             // help
    connect(ui->push, SIGNAL(clicked()), this, SLOT(pushed()));           // pushed
    connect(ui->up, SIGNAL(clicked()), this, SLOT(up()));                 // up
    connect(ui->down, SIGNAL(clicked()), this, SLOT(down()));             // down
    connect(ui->close, SIGNAL(clicked()), this, SLOT(close()));           // close
    connect(ui->open, SIGNAL(clicked()), this, SLOT(open()));             // open
}

// move to the next step
void MainWindow::next()
{

    qInfo("[MainWindow] Pressed NEXT");
    ecs->directions();
}

// there is a fire inside a specified elevator number
void MainWindow::fire()
{
    // get index of specified elevator number
    int carNum = ui->carNum->currentIndex();

    qInfo("[MainWindow] Pressed Fire inside Elevator Number %d", carNum);
    ecs->fireAlert(carNum);


    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText(ecs->getElevator(carNum)->getDisplay()->getOutput(-1));
    item->setTextAlignment(Qt::AlignCenter);
    ui->display->setItem(carNum-1, 1, item);
}

// there is a fire in the building
void MainWindow::buildFire()
{

    qInfo("[MainWindow] FIRE in the building");
    ecs->fireAlert(-1);
    displayMessage(-1);

}

// adding obstacles to a specified elevator number
void MainWindow::obstacles()
{
    // get index of specified elevator number
    int carNum = ui->carNum->currentIndex();

    qInfo("[MainWindow] Pressed OBSTACLES for Elevator Number %d", carNum);
    ecs->getElevator(carNum)->setEmergencyStop(true);
    ecs->getElevator(carNum)->getDoor()->getDoorSensor()->obstacles();
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText(ecs->getElevator(carNum)->getDisplay()->getOutput(-3));
    item->setTextAlignment(Qt::AlignCenter);
    ui->display->setItem(carNum-1, 1, item);
}

// overloading specified elevator number
void MainWindow::overload()
{
    // get index of specified elevator number
    int carNum = ui->carNum->currentIndex();
    qInfo("[MainWindow] Pressed OVERLOAD for Elevator Number %d", carNum);
    ecs->getElevator(carNum)->setEmergencyStop(true);
    ecs->getElevator(carNum)->overload();
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText(ecs->getElevator(carNum)->getDisplay()->getOutput(-4));
    item->setTextAlignment(Qt::AlignCenter);
    ui->display->setItem(carNum-1, 1, item);
}



// pressing the help button at specified floor number and elevator number
void MainWindow::help()
{
    // get index of specified elevator and floor number
    int floorNum = ui->floorNum->currentIndex();
    int carNum = ui->carNum->currentIndex();

    qInfo("[MainWindow] Pressed HELP at floor number %d for car number %d", floorNum, carNum);
    ecs->getElevator(carNum)->getPanel()->getHelp();
}

// creating a elevator request at specified floor number and elevator number
void MainWindow::pushed()
{
    int floorNum = ui->floorNum->currentIndex();
    int carNum = ui->carNum->currentIndex();

    qInfo("[MainWindow] Pressed PUSH at floor number %d for car number %d", floorNum, carNum);
    ecs->getElevator(carNum)->getPanel()->pressed(floorNum);
}

// there is a power outage
void MainWindow::powerOutage()
{

    qInfo("[MainWindow] Pressed POWER OUTAGE");
    ecs->powerOutageAlert();
    displayMessage(-2);
}

// pressed up button at specified floor
void MainWindow::up()
{
    int floorNum = ui->floorDrop->currentIndex();
    ecs->handleFloorRequest(floorNum, 0);

    qInfo("[MainWindow] Pressed UP for floor number %d", floorNum);
}

// pressed down button at specified floor number
void MainWindow::down()
{
    int floorNum = ui->floorDrop->currentIndex();
    ecs->handleFloorRequest(floorNum, 1);
    qInfo("[MainWindow] Pressed DOWN for floor number %d", floorNum);
}

// pressed close button
void MainWindow::close()
{
    int floorNum = ui->floorDrop->currentIndex();
    int carNum = ui->carNum->currentIndex();
    qInfo("[MainWindow] Pressed CLOSE door for car number %d at floor %d", carNum, floorNum);
    ecs->getElevator(carNum)->getDoor()->close();


}

// pressed open button
void MainWindow::open()
{
    int floorNum = ui->floorDrop->currentIndex();
    int carNum = ui->carNum->currentIndex();
    qInfo("[MainWindow] Pressed OPEN door for car number %d at floor %d", carNum, floorNum);
     ecs->getElevator(carNum)->getDoor()->close();

}

// populating combo boxes
void MainWindow::populateElevatorsDropdown()
{
    int elevatorsNum = MAX_ELEVATORS;

    for (int i = 0; i <= elevatorsNum; i++)
    {
        ui->elevatorsDrop->addItem(QString::number(i));
    }
}

void MainWindow::populateFloorsDropdown()
{
    int floorsNum = MAX_FLOORS;

    for (int i = 0; i <= floorsNum; i++)
    {
        ui->floorsDrop->addItem(QString::number(i));
    }
}

void MainWindow::populateFloorDropdown(int floors)
{
    qInfo("[MainWindow] POPULATE FLOORS: %d", floors);

    for (int i = 0; i < floors; i++)
    {
        ui->floorNum->addItem(QString::number(i+1));
        ui->floorDrop->addItem(QString::number(i+1));
    }
}

void MainWindow::populateElevatorDropdown(int elevators)
{
    qInfo("[MainWindow]] POPULATE ElEVATORS: %d", elevators);

    for (int i = 0; i < elevators; i++)
    {
        ui->carNum->addItem(QString::number(i));
    }
}

void MainWindow::populateTable(int floors, int elevators)
{
    ui->display->setRowCount(elevators);
    ui->display->setColumnCount(1);

    ui->table->setColumnCount(elevators);
    ui->table->setRowCount(floors);
    QStringList label;

    for (int i = 0; i < floors; i++)
    {
        std::string row = std::to_string(floors - i);
        label.append(row.c_str());
    }
     ui->table->setVerticalHeaderLabels(label);

    QStringList display;

    for (int i = 0; i < elevators; i++)
    {
        std::string row = "Elevator " + std::to_string(i+1);
        display.append(row.c_str());
    }


    QStringList displayLabel;
    displayLabel.append("Display");
    ui->display->setVerticalHeaderLabels(display);
    ui->display->setHorizontalHeaderLabels(displayLabel);
    ui->display->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->display->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::displayPositions()
{
    int elevators = ui->elevatorsDrop->currentIndex();
    int floors = ui->floorsDrop->currentIndex();
    ui->table->clearContents();


    for (int j = 0; j < elevators; j++)
    {
        QTableWidgetItem *item = new QTableWidgetItem();

        item->setText(QString("0"));
        item->setTextAlignment(Qt::AlignCenter);
        ui->table->setItem(floors - 1 - (ecs->getElevatorPositions(j)), j, item);
    }
    displayMessage(1);




}

void MainWindow::displayMessage(int c){
    int elevators = ui->elevatorsDrop->currentIndex();
    ui->display->clearContents();
    for (int j = 0; j < elevators; j++)
    {
        QTableWidgetItem *item = new QTableWidgetItem();

        item->setText(ecs->getElevator(j)->getDisplay()->getOutput(c));
        item->setTextAlignment(Qt::AlignCenter);
        ui->display->setItem(j-1, 1, item);
    }
}
