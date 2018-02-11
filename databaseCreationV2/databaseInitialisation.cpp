#include <iostream>
#include <string>
using namespace std;

#include "libsqlite.hpp"

//Creates the military unit table

void holoSoldier(){
    
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO military_Units "
                      "VALUES (?, ?, ?, ?, ?);");

        cur->prepare();
        cur->bind(1,001);
        cur->bind(2,"HoloSoldier");
        cur->bind(3,10);
        cur->bind(4,5);
        cur->bind(5,5);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void holoBike(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO military_Units "
                      "VALUES (?, ?, ?, ?, ?);");

        cur->prepare();
        cur->bind(1,002);
        cur->bind(2,"HoloBike");
        cur->bind(3,25);
        cur->bind(4,20);
        cur->bind(5,100);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void holoTank(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO military_Units "
                      "VALUES (?, ?, ?, ?, ?);");

        cur->prepare();
        cur->bind(1,003);
        cur->bind(2,"HoloTank");
        cur->bind(3,60);
        cur->bind(4,90);
        cur->bind(5,250);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void holoXCOM(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO military_Units "
                      "VALUES (?, ?, ?, ?, ?);");

        cur->prepare();
        cur->bind(1,004);
        cur->bind(2,"HoloXCOM");
        cur->bind(3,100);
        cur->bind(4,40);
        cur->bind(5,350);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void createtable_mUnits(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db(file);
        auto cur = db.get_statement();
        
        cur->set_sql("CREATE TABLE IF NOT EXISTS military_Units (ID INTEGER,Name TEXT,Attack INTEGER,Defence INTEGER,Cost INTEGER);");
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

void holoFishing(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO production_Units "
                      "VALUES (?, ?, ?, ?);");

        cur->prepare();
        cur->bind(1,001);
        cur->bind(2,"HoloFishing");
        cur->bind(3,25);
        cur->bind(4,300);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void holoMine(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO production_Units "
                      "VALUES (?, ?, ?, ?);");

        cur->prepare();
        cur->bind(1,002);
        cur->bind(2,"HoloMine");
        cur->bind(3,100);
        cur->bind(4,200);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void holoPlatform(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO production_Units "
                      "VALUES (?, ?, ?, ?);");

        cur->prepare();
        cur->bind(1,003);
        cur->bind(2,"HoloPlatform");
        cur->bind(3,200);
        cur->bind(4,5000);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void createtable_pUnits(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db(file);
        auto cur = db.get_statement();
        
        cur->set_sql("CREATE TABLE IF NOT EXISTS production_Units (ID INTEGER,Name TEXT,Income INTEGER,Cost INTEGER);");
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

void mapA(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO Map "
                      "VALUES (?, ?, ?);");

        cur->prepare();
        cur->bind(1,0001);
        cur->bind(2,"A");
        cur->bind(3,true);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void mapB(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO Map "
                      "VALUES (?, ?, ?);");

        cur->prepare();
        cur->bind(1,0010);
        cur->bind(2,"B");
        cur->bind(3,true);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void mapC(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO Map "
                      "VALUES (?, ?, ?);");

        cur->prepare();
        cur->bind(1,0011);
        cur->bind(2,"C");
        cur->bind(3,true);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void mapD(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO Map "
                      "VALUES (?, ?, ?);");

        cur->prepare();
        cur->bind(1,0100);
        cur->bind(2,"D");
        cur->bind(3,true);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void mapE(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO Map "
                      "VALUES (?, ?, ?);");

        cur->prepare();
        cur->bind(1,0101);
        cur->bind(2,"E");
        cur->bind(3,true);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void mapF(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO Map "
                      "VALUES (?, ?, ?);");

        cur->prepare();
        cur->bind(1,0110);
        cur->bind(2,"F");
        cur->bind(3,true);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void mapG(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO Map "
                      "VALUES (?, ?, ?);");

        cur->prepare();
        cur->bind(1,0111);
        cur->bind(2,"G");
        cur->bind(3,true);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void mapH(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO Map "
                      "VALUES (?, ?, ?);");

        cur->prepare();
        cur->bind(1,1000);
        cur->bind(2,"H");
        cur->bind(3,true);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void mapI(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO Map "
                      "VALUES (?, ?, ?);");

        cur->prepare();
        cur->bind(1,1001);
        cur->bind(2,"I");
        cur->bind(3,true);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}
void mapJ(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db( file );
        auto cur = db.get_statement();
        
        cur->set_sql( "INSERT INTO Map "
                      "VALUES (?, ?, ?);");

        cur->prepare();
        cur->bind(1,1010);
        cur->bind(2,"J");
        cur->bind(3,true);
        cur->step();
    }
    catch( sqlite::exception e){
        std::cerr << e.what() << endl;
    }
}

void createtable_map(){
    string file = "civilwarofMalibu.db";
    
    try{
        sqlite::sqlite db(file);
        auto cur = db.get_statement();
        
        cur->set_sql("CREATE TABLE IF NOT EXISTS Map (ID INTEGER,Name TEXT,Owned BOOLEAN);");
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


int main(){
    createtable_mUnits();
    createtable_pUnits();
    createtable_map();
}