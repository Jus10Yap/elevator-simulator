#include "Audio.h"
#include "Elevator.h"

#include <QObject>
//constructor
Audio::Audio(Elevator *elevator) : elevator(elevator)
{

    qInfo("[Audio %d] Initialized", elevator->getCarNum());
}


//play audio for fire alert
void Audio::fireDisplay()
{
    qInfo("[Audio %d] Fire! Exit the elevator", elevator->getCarNum());
}

//play audio for poweroutage alert
void Audio::powerOutageDisplay()
{
    qInfo("[Audio %d] Power Outage! Exit the elevator", elevator->getCarNum());
}

//play audio for obstacles alert
void Audio::obstaclesDisplay()
{
    qInfo("[Audio %d] Remove obstacles", elevator->getCarNum());
}

//play audio for overload alert
void Audio::overloadDisplay()
{
    qInfo("[Audio %d] Remove weight", elevator->getCarNum());
}
