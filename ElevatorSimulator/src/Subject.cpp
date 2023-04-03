#include <list>
#include "Subject.h"
#include "Observer.h"
using namespace std;

Subject::Subject()
{
    observers = new std::list<Observer *>;
}
void Subject::attach(Observer *observer)
{
    observers->push_back(observer);
}
void Subject::dettach(Observer *observer)
{
    observers->remove(observer);
}
void Subject::notify()
{
    for (Observer *observer : *observers)
    {
        observer->update(this);
    }
}
