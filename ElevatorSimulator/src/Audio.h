#ifndef AUDIO_H
#define AUDIO_H

#include <string>

class Elevator;
class Audio
{
private:
    Elevator *elevator; // the current message displayed on the screen

public:
    Audio(Elevator *elevator);
    // display a fire alert message on the screen
    void fireDisplay();

    // display a powerOutage alert message on the screen
    void powerOutageDisplay();

    // display a obstacles alert message on the screen
    void obstaclesDisplay();

    // display a overload alert message on the screen
    void overloadDisplay();
};

#endif
