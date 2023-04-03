#ifndef DISPLAY_H
#define DISPLAY_H
#include <QObject>
#include <string>
class Elevator;

class Display
{
private:
    Elevator *elevator; // the current message displayed on the screen

public:
    Display(Elevator *elevator);
    // return a message on the screen
    QString getOutput(int c);


};

#endif
