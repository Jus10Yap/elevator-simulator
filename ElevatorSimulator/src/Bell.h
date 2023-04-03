#ifndef BELL_H
#define BELL_H
class Door;
class Bell
{
public:
   Bell(Door* door);
  // Rings elevator door bell
  void ring();
private:
  Door* door;
};

#endif
