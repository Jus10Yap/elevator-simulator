#ifndef BUTTON_PANEL_H
#define BUTTON_PANEL_H

#include "defs.h"
class Elevator;

class ButtonPanel
{
public:
    // Constructor to initialize the direction, open/close status, and help flag
    ButtonPanel(Elevator *elevator, int floorNums);

    // Function to handle the button press event for a given floor number
    void pressed(int floorNum);

    // Function to get help
    void getHelp();

    //function for fire in elevator
    void getFire();

    //button to close and open door
    void openCloseButton(int openClose);

private:
    Elevator *elevator;
    int floorNums;
    int requests[MAX_FLOORS];

    // Variable to store the status of the door (1 for open, 0 for closed)
    int openClose;

    //    // Flag to indicate whether the help button has been pressed
    //    bool help;
};

#endif
