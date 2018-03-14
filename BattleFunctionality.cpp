#include <iostream>
#include <string>
#include <stdlib.h> 
#include "libsqlite.hpp"
#include <vector>
using namespace std;

vector<int> troopCounter(int map_ID, int player_ID) ///Counts the attack and defence of the total amount of units 
{
    string file = "civilwarofMalibu.db";
    try
    {
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();

        cout << "TroopTest1" << endl;
        int totalAtk = 0;
        int totalDef = 0;

        cur1->set_sql("SELECT military_Units.Attack , military_Units.Defence "
                      "FROM military_Units "
                      "INNER JOIN player_Army ON military_Units.ID = player_Army.military_ID "
                      "WHERE player_Army.player_ID = ? ");        
        cur1->prepare();
        cur1->bind(1, player_ID);
        cout << "TroopTest2" << endl;
        while( cur1->step() )
        {
            int attackValue = cur1->get_int(0);
            totalAtk = totalAtk + attackValue;
            int defenceValue = cur1->get_int(1);
            totalDef = defenceValue + totalDef;
        }
        vector<int> Atk_Def = {totalAtk,totalDef};
        cout << Atk_Def[0] << " || " << Atk_Def[1] << endl;
        return Atk_Def;
    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}


int delTroops(int threshold, int map_ID, int player_ID, string AIorPlayer) ///Deletes the top value in the army database tables until it is under the army threshold
{
    const string file = "civilwarofMalibu.db";
    
    
    try
    {
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();
        if( AIorPlayer == "Ai")
        cur1->set_sql("DELETE TOP FROM ? "
                          "WHERE map_ID = ? AND player_ID = ? "
                          "SORT BY uniqueunit_id ASC");
        else:
        delete from player
        cur1->prepare();
        ///auto cur2=db.get_statement();
        

        
        vector<int> armyValues = troopCounter(map_ID, player_ID);
        int attackValue = armyValues[0];
        
        cout << "TestDelete1" << endl;
        
        while( attackValue > threshold )
        {
            vector<int> armyValues = troopCounter(map_ID, player_ID);
            int attackValue = armyValues[0];
            
            
            cur1->bind(1, AIorPlayer);
            cur1->bind(2, map_ID);
            cur1->bind(3, player_ID);
            cur1->step();
        }
        
        cout << "done" << endl << flush;
        
    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}


int battle(int map_ID, int player_ID, int AI_map_ID) ///Calculates the threshold for the loss of troops to be used to delete troops from database
{
    vector<int> AI_Army = troopCounter(AI_map_ID, player_ID);
    int AIAttackTotal = AI_Army[0];
    int AIDefenceTotal = AI_Army[1];
    vector<int> player_Army = troopCounter(map_ID, player_ID);
    int playerAttackTotal = player_Army[0];
    int playerDefenceTotal = player_Army[1];
    cout << "testBattle1" << endl;
    int AIAttack = rand() % AIAttackTotal/10 + AIAttackTotal;
    int AIDefence = rand() % AIDefenceTotal/10 + AIDefenceTotal;
    int playerAttack = rand() % playerAttackTotal/10 + playerAttackTotal;
    int playerDefence = rand() % playerDefenceTotal/10 + playerDefenceTotal;
    
    cout << "Player Attack roll is: " << playerAttack << endl;
    cout << "AI Attack roll is: " << AIAttack << endl;
    
    cout << "testBattle2" << endl;
    if (AIAttack>playerAttack)
    {
        cout << "TestBattleAIWin" << endl;
        if (AIAttack>2*playerAttack)
        {
            cout << "AI wiped out your army!" << endl;
            return 0;
        }
        else
        {
            cout << "AI won the battle!" << endl;
            
            int threshold = playerAttack - (playerAttack*(playerDefence/AIAttack));
            cout << "HERE1" << endl << flush;
            delTroops(threshold, map_ID, player_ID, "AI_Army");
            cout << "HERE2" << endl << flush;
            return 0;
        }
    }
    else if (playerAttack>AIAttack)
    {
        cout << "TestBattlePlayerWin" << endl;
        if (playerAttack>2*AIAttack)
        {
            cout<< "You wiped out the AI army!" << endl;
            
            return 0;
            
        }
        else
        {
            cout << "You won the battle!" << endl;
            int threshold = AIAttack - (AIAttack*(AIDefence/playerAttack));
            delTroops(threshold, map_ID, player_ID, "player_Army");
            
            return 0;
        }
    }
    else if (playerAttack==AIAttack)
    {
        cout << "Whatever" << endl;
        return 0;
    }
}

main()
{
    battle(4, 1, 6);
}
