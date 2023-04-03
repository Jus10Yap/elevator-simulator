#include "Display.h"
#include "Elevator.h"

#include <QObject>
//constructor
Display::Display(Elevator *elevator) : elevator(elevator)
{

    qInfo("[Display %d] Initialized", elevator->getCarNum());
}

//return qstring based on situation
// 1 current floor
// -1 fire alert
// -2 power outage
//-3 obstacles
//-4 overload
QString Display::getOutput(int c)
{
    QString msg;
    switch(c){
    case 1:
        qInfo("[Display %d] Floor: %d", elevator->getCarNum(), elevator->getCurrentFloor());
        msg = QString::number(elevator->getCurrentFloor()+1);


        return msg;
    case -1:
        qInfo("[Display %d] There is a fire. Please leave the elevator.", elevator->getCarNum());
        msg ="FIRE";
        return msg;
    case -2:
        qInfo("[Display %d] There is a Poweroutage. Please leave the elevator.", elevator->getCarNum());
        msg = "POWEROUTAGE";
        return msg;
    case -3:
        qInfo("[Display %d] Remove Obstacles", elevator->getCarNum());
        msg = "OBSTACLES";
        return msg;
    case -4:
        qInfo("[Display %d] Remove Weight", elevator->getCarNum());
        msg = "OVERLOAD";
        return msg;
    default:
        return "";
    }


}
