#include <iostream>
#include "libsqlite.hpp"

using namespace std;

string armyCalc(int playerID, int terrID, string whoseArmy)
{
    /* This function takes player ID and territory number, and then returns army value stats
     * for that territory as string (because I want to manipulate it as a string later). It 
     * also takes a string, "whoseArmy", which specifies whether it's meant to be the player's
     * or the enemy's army to be taken'*/
    
    if ((whoseArmy != "player") && (whoseArmy != "ai"))
    {
        cout << whoseArmy << endl;
        return "Did not specify correct string paramater!/n String paramater must be 'player' or 'ai'!\n";
        /* Breaks function and reprimands programmer using this function for not following rules.
         * Also protects against SQL injection because only two valid values can be specified, 
         * and neither of these values allows an unintended consequence.*/
    }
    
    int armyVal = 0;
    
    sqlite::sqlite db("civilwarofMalibu.db"); //connect to database
    auto cur = db.get_statement(); //set query
    cur->set_sql(
        "SELECT COUNT(military_ID), Attack " //counts every occurrence of each military_ID and relevant attack value
        "FROM " + whoseArmy + "_Army "
        "INNER JOIN military_Units ON " + whoseArmy + "_Army.military_ID = military_Units.ID " //joins table so can combine columns from both
        "WHERE player_ID = ? AND map_ID = ? " //limits to relevant player and territory
        "GROUP BY Attack; "); 
    
    cur->prepare(); //run query
    
    cur->bind(1, playerID); //using placeholders to insert relevant values
    cur->bind(2, terrID);

    while(cur->step())
    {
        armyVal = armyVal + (cur->get_int(0) * cur->get_int(1)); 
        //multiplies occurrences of troop with attack value and then adds to army value
    }
    
    if (armyVal == 1){
        return "     "; //placeholder information to keep map proper size if no value
    }
    
    return to_string(armyVal);
}
