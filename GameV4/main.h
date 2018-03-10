#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
using namespace std;

#include "libsqlite.hpp"


class Menu{
    public:

    int menu_militaryUnits(int player_ID,int totalMoney);
    int menu_productionUnits(int player_ID,int totalMoney);
    int store_Menu(int player_ID,int totalMoney);
    int main_Menu(int player_ID, int turn,int totalMoney);    
    int execute(int player_ID, int turn,int totalMoney);
};

#endif