#include <QObject>
#include "ButtonPanel.h"
#include "Elevator.h"

ButtonPanel::ButtonPanel(Elevator *elevator, int floorNums) : elevator(elevator), floorNums(floorNums)
{
    // initialize all the buttons of each floor of this elevator
    for (int i = 0; i < floorNums; i++)
    {
        requests[i] = false;
    }
    qInfo("[Button Panel %d] initialized all floor buttons", elevator->getCarNum());
}

void ButtonPanel::pressed(int floorNum)
{
    // Update the requests array with the pressed floor number
    requests[floorNum] = true;

    qInfo("[Button Panel %d] pressed floor number %d", elevator->getCarNum(),floorNum);

    // Call pressButton method of Elevator class passing the floor number
    elevator->pressButton(floorNum);


}

void ButtonPanel::getHelp(){
    elevator->help();

}
