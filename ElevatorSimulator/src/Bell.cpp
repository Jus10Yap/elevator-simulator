#include"Bell.h"
#include"Door.h"
#include<QObject>

Bell::Bell(Door* door): door(door){

}

//ring bell
void Bell::ring(){
    qInfo("[Bell %d] RING", door->getDoorNum());
}
