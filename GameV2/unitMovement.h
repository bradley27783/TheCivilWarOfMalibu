#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <iostream>
#include <string>
using namespace std;

#include "libsqlite.hpp"


class UnitMovement{
    public:

    void show_Values();
    int from_Input();
    int to_Input();
    void move_Soldiers();    
    void execute();
};

#endif