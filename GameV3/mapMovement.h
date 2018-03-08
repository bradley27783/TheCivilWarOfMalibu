#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <iostream>
#include <string>
using namespace std;

#include "libsqlite.hpp"


class UnitMovement{
    public:

        void guiHeader();
        int moveto_Check(int player_ID);
        int movefrom_Check(int player_ID);
        int unitType_Check(int player_ID);
        int unitAmount_Check(int unitType, int player_ID, int moveFrom);
        int moveUnits(int unitType, int player_ID, int moveFrom, int moveTo, int unitAmount);
        void movement_Menu(int player_ID);
        int execute(int player_ID);
            
};

#endif