#ifndef SUBJECT_H
#define SUBJECT_H
#include <list>
#include "Observer.h"
using namespace std;
class Observer;

class Subject
{
public:
    Subject();
    virtual void attach(Observer *observer);
    virtual void dettach(Observer *observer);
    virtual void notify();

private:
    std::list<Observer *> *observers;
};

#endif // SUBJECT_H
