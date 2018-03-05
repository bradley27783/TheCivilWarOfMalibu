#include <iostream>
#include <string>
using namespace std;

#include "libsqlite.hpp"
#include "db.h"

void database::holoSoldier(){
    
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO military_Units (Name, Attack, Defence, Cost)"
                      "VALUES (?, ?, ?, ?);");

        cur->prepare();
        cur->bind(1,"HoloSoldier");
        cur->bind(2,10);
        cur->bind(3,5);
        cur->bind(4,5);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void database::holoBike(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO military_Units (Name, Attack, Defence, Cost)"
                      "VALUES (?, ?, ?, ?);");

        cur->prepare();
        cur->bind(1,"HoloBike");
        cur->bind(2,25);
        cur->bind(3,20);
        cur->bind(4,100);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void database::holoTank(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO military_Units (Name, Attack, Defence, Cost)"
                      "VALUES (?, ?, ?, ?);");

        cur->prepare();
        cur->bind(1,"HoloTank");
        cur->bind(2,60);
        cur->bind(3,90);
        cur->bind(4,250);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void database::holoXCOM(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO military_Units (Name, Attack, Defence, Cost)"
                      "VALUES (?, ?, ?, ?);");

        cur->prepare();
        cur->bind(1,"HoloXCOM");
        cur->bind(2,100);
        cur->bind(3,40);
        cur->bind(4,350);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void database::createtable_mUnits(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db(file);
        auto cur = db.get_statement();

        cur->set_sql("CREATE TABLE IF NOT EXISTS military_Units (ID INTEGER PRIMARY KEY NOT NULL,Name CHAR(16),Attack INTEGER,Defence INTEGER,Cost INTEGER);");
        cur->prepare();
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
    holoSoldier();
    holoBike();
    holoTank();
    holoXCOM();
}

//Creates the production/income based units/structures

void database::holoFishing(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO production_Units (Name, Income, Cost)"
                      "VALUES (?, ?, ?);");

        cur->prepare();
        cur->bind(1,"HoloFishing");
        cur->bind(2,25);
        cur->bind(3,100);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void database::holoMine(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO production_Units (Name, Income, Cost)"
                      "VALUES (?, ?, ?);");

        cur->prepare();
        cur->bind(1,"HoloMine");
        cur->bind(2,100);
        cur->bind(3,200);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void database::holoPlatform(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO production_Units (Name, Income, Cost)"
                      "VALUES (?, ?, ?);");

        cur->prepare();
        cur->bind(1,"HoloPlatform");
        cur->bind(2,200);
        cur->bind(3,5000);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void database::createtable_pUnits(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db(file);
        auto cur = db.get_statement();

        cur->set_sql("CREATE TABLE IF NOT EXISTS production_Units (ID INTEGER PRIMARY KEY NOT NULL,Name TEXT,Income INTEGER,Cost INTEGER);");
        cur->prepare();
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
    holoFishing();
    holoMine();
    holoPlatform();
}

//Owned territories

void database::mapA(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO Map (Name, Owned)"
                      "VALUES (?, ?);");

        cur->prepare();
        cur->bind(1,"A");
        cur->bind(2,true);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void database::mapB(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO Map (Name, Owned)"
                      "VALUES (?, ?);");

        cur->prepare();
        cur->bind(1,"B");
        cur->bind(2,true);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void database::mapC(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO Map (Name, Owned)"
                      "VALUES (?, ?);");

        cur->prepare();
        cur->bind(1,"C");
        cur->bind(2,true);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void database::mapD(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO Map (Name, Owned)"
                      "VALUES (?, ?);");

        cur->prepare();
        cur->bind(1,"D");
        cur->bind(2,true);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void database::mapE(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO Map (Name, Owned)"
                      "VALUES (?, ?);");

        cur->prepare();
        cur->bind(1,"E");
        cur->bind(2,false);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void database::mapF(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO Map (Name, Owned)"
                      "VALUES (?, ?);");

        cur->prepare();
        cur->bind(1,"F");
        cur->bind(2,false);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void database::mapG(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO Map (Name, Owned)"
                      "VALUES (?, ?);");

        cur->prepare();
        cur->bind(1,"G");
        cur->bind(2,false);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void database::mapH(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO Map (Name, Owned)"
                      "VALUES (?, ?);");

        cur->prepare();
        cur->bind(1,"H");
        cur->bind(2,false);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void database::mapI(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO Map (Name, Owned)"
                      "VALUES (?, ?);");

        cur->prepare();
        cur->bind(1,"I");
        cur->bind(2,false);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void database::mapJ(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();

        cur->set_sql( "INSERT INTO Map (Name, Owned)"
                      "VALUES (?, ?);");

        cur->prepare();
        cur->bind(1,"J");
        cur->bind(2,false);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void database::createtable_map(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db(file);
        auto cur = db.get_statement();

        cur->set_sql("CREATE TABLE IF NOT EXISTS Map (ID INTEGER PRIMARY KEY NOT NULL,Name TEXT NOT NULL,Owned BOOLEAN NOT NULL, Attack INTEGER NULL, Defence INTEGER NULL, Income INTEGER NULL);");
        cur->prepare();
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
    mapA();
    mapB();
    mapC();
    mapD();
    mapE();
    mapF();
    mapG();
    mapH();
    mapI();
    mapJ();
}

void database::createtable_save(){
    string file = "civilwarofMalibu.db";

    try{
        sqlite::sqlite db(file);
        auto cur = db.get_statement();

        cur->set_sql("CREATE TABLE IF NOT EXISTS Saves (Name TEXT PRIMARY KEY NOT NULL,Attack1 INTEGER,Defence1 INTEGER,Attack2 INTEGER ,Defence2 INTEGER ,Territories TEXT);");
        cur->prepare();
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void database::execute(){
    int user_Input;
    cout << "\033[2J\033[1;1H";
    cout << "1: Yes" << endl << "2: No" << endl <<"Before getting started can you tell us if you have played before? Please enter here: ";
    cin >> user_Input;
    if(user_Input == 2){
        createtable_mUnits();
        createtable_pUnits();
        createtable_map();
        createtable_save();
    }
}