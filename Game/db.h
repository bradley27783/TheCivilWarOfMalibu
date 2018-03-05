#ifndef DB_H
#define DB_H

#include <iostream>
#include <string>
using namespace std;

#include "libsqlite.hpp"

class database{
    public:

    void holoSoldier();
    void holoBike();
    void holoTank();
    void holoXCOM();
    void createtable_mUnits();

    //Creates the production/income based units/structures

    void holoFishing();
    void holoMine();
    void holoPlatform();
    void createtable_pUnits();
    
    //Owned territories

    void mapA();
    void mapB();
    void mapC();
    void mapD();
    void mapE();
    void mapF();
    void mapG();
    void mapH();
    void mapI();
    void mapJ();
    void createtable_map();
    void createtable_save();
    
    void execute();
};

#endif