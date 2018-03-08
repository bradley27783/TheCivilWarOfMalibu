#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
using namespace std;

#include "libsqlite.hpp"


class Menu{
    public:

    int menu_militaryUnits(int player_ID);
    int menu_productionUnits(int player_ID);
    int store_Menu(int player_ID);
    int main_Menu(int player_ID);    
    int execute(int player_ID);
};

#endif