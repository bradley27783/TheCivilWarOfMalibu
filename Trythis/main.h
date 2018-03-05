#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
using namespace std;

#include "libsqlite.hpp"


class Menu{
    public:

    void menu_militaryUnits();
    void menu_productionUnits();
    void store_Menu();
    void main_Menu();    
    void execute();
};

#endif