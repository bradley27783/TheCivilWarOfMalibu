#include <iostream>
#include <string>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h> 
#include "libsqlite.hpp"

using namespace std;



const char* database = "civilwarofMalibu.db";
const char* player_ID = "1";
int player_IDint = 1;


int addArmy(int terr)//Adds units to the ai to territory
{

	int amount = rand() % 10;//How many units
	for(int i = 0; i< amount;i++)
	{
		try
		{

		
		int military_ID=rand() % 4 + 1;//Which military unit?

		sqlite::sqlite db( database );//Opens database

		auto cur = db.get_statement(); //Prepares cursor

		cur->set_sql("INSERT INTO ai_Army ( player_ID, military_ID, map_ID)"
			"VALUES (?,?,?);"); //Inserting army values

		cur->prepare();//Send query

		//Binds the variables
		cur->bind(1,player_ID);
		cur->bind(2,military_ID);
		cur->bind(3,terr);

		cur->step();
		}

		catch( sqlite:: exception e )
		{
		    cerr << e.what() << endl;//Shows error
		    return 1;
		}
	}
}

int findAmountAi()//Find amount of AI territories
{
	int aiNum=0;//Number identifier for AI
	try
	{
		sqlite::sqlite db( database );//Opens database

		auto cur1 = db.get_statement();
		cur1->set_sql("SELECT Owned FROM Map WHERE player_ID = ?;");//Selecting owned column of map
		cur1->prepare();

		cur1->bind(1,player_ID);
		int aiAmount=0;

		int i;
		while(cur1->step())//Go through the results
		{
			int CurMap = cur1->get_int(0);//Get results

			if(CurMap == 0)//If ai
			{
				aiAmount++;//add to ai amount
			}
		}
		return aiAmount;
	}

	catch( sqlite:: exception e )
	{
	    cerr << e.what() << endl;//Shows error
	    return 1;
	}

}


int* findAI(int* map) 
{
	int aiNum=0;
	try{
		sqlite::sqlite db( database );//Opens database

		auto cur = db.get_statement();
		cur->set_sql("SELECT map_ID FROM Map WHERE Owned = ?; ");//Selecting ai territory
		cur->prepare();

		cur->bind(1,aiNum);


		int i =0;
		int currentMapID;
		while(cur->step())//Go through the results
		{
			currentMapID = cur->get_int(0);
			map[i]=currentMapID;
			i++;
		}
	}

	catch( sqlite:: exception e )//Codio week 4
	{
	    cerr << e.what() << endl;//Shows error
	    return NULL;
	}
	return map;
}

bool inArray(int look, int* array, int size)//Take in a search value, array and size of array
{
	int i;
	for(i=0; i < size; i++)//Go through
	{
		if(array[i]==look)//Check for search value
		{
			return true;//Yes, it's here
		}
	}
	return false;//Nope, didn't find it
}

int* selectTerr(int* Aimap, int aSize, int* returnValue)//Find appropriate territory
{	
	int terr[aSize];
	int i;
	int sT;
	int playerTerritory;
	for(i = 0; i < aSize;i++)//Go through the map
	{
		sT=Aimap[i];//Selected territory

		if( !(inArray(sT+1, Aimap, aSize)) || !(inArray(sT-1, Aimap, aSize)) )//Checks if it is owned by AI already
		{
			//Checks which way the player is
			if( !(inArray(sT+1, Aimap, aSize)) )//Player territory is one behind
			{
				playerTerritory=-1;
			}
			else if ( !(inArray(sT-1, Aimap, aSize)) )//Player territory is one ahead
			{
				playerTerritory=+1;
			}

			//Edge detection
			if(sT+1 < 10 && sT-1 > 0)//Checks if it is at the edge
			{
				terr[i]=sT;//Sets its entry as usable; it's map ID
			}
			else
			{
				terr[i]=0;//Unusable
			}
		}
		else
		{
			terr[i]=0;
		}
	}
	int timer = 0;
	while(timer < 9)//Makes sure it doesn't stick
	{
		int terChoose=rand() % aSize;//Chooses random territory from list, makes sure it is useable (it has enemy next to it)
		if(terr[terChoose]>0)//If useable
		{
			returnValue[0] = terr[terChoose];
			returnValue[1] = playerTerritory;
			return returnValue;
		}
		timer++;//increment timer
	}
	return 0;
	//enter win condition intergration here	
}

//
//Adam's code
//

vector<int> troopCounter(int map_ID, int player_ID, string AIorPlayer) ///Counts the attack and defence of the total amount of units 
{
    string file = "civilwarofMalibu.db";
    try
    {
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();

        int totalAtk = 0;
        int totalDef = 0;
        
        if (AIorPlayer=="Player")
        {
            cur1->set_sql("SELECT military_Units.Attack , military_Units.Defence "
                          "FROM military_Units "
                          "INNER JOIN player_Army ON military_Units.ID = player_Army.military_ID "
                          "WHERE player_Army.player_ID = ? ");        
            cur1->prepare();
            cur1->bind(1, player_ID);
            while( cur1->step() )
            {
                int attackValue = cur1->get_int(0);
                totalAtk = totalAtk + attackValue;
                int defenceValue = cur1->get_int(1);
                totalDef = defenceValue + totalDef;
            }
            vector<int> Atk_Def = {totalAtk,totalDef};
            return Atk_Def;
            }
        
        else if(AIorPlayer=="AI")
        {
            cur1->set_sql("SELECT military_Units.Attack , military_Units.Defence "
                          "FROM military_Units "
                          "INNER JOIN ai_Army ON military_Units.ID = ai_Army.military_ID "
                          "WHERE ai_Army.player_ID = ? ");        
            cur1->prepare();
            cur1->bind(1, player_ID);
            while( cur1->step() )
            {
                int attackValue = cur1->get_int(0);
                totalAtk = totalAtk + attackValue;
                int defenceValue = cur1->get_int(1);
                totalDef = defenceValue + totalDef;
            }
            vector<int> Atk_Def = {totalAtk,totalDef};
            return Atk_Def;
            }

    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}


int delTroops(int threshold, int map_ID, int player_ID, int AI_map_ID, string AIorPlayer) ///Deletes the top value in the army database tables until it is under the army threshold
{
    const string file = "civilwarofMalibu.db";
    
    try
    {
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();
        
        if( AIorPlayer == "AI")
        {
            vector<int> armyValues = troopCounter(map_ID, player_ID,  "Player");
            int attackValue = armyValues[0];
            while(attackValue>threshold)
            {
                cur1->set_sql("DELETE FROM player_Army "
                              "WHERE map_ID = ? AND player_ID = ? "
                              "ORDER BY uniqueunit_id ASC "
                              "LIMIT 1; ");
                 cur1->prepare();
                 cur1->bind(1, map_ID);
                 cur1->bind(2, player_ID);
                 cur1->step();
                 cur1->reset();
                 vector<int> armyValues = troopCounter(map_ID, player_ID, "Player");
                 attackValue = armyValues[0];
            }
        }
        
        else if ( AIorPlayer == "Player")
        {
            vector<int> armyValues = troopCounter(AI_map_ID, player_ID, "AI");
            int attackValue = armyValues[0];
            cout << attackValue << " !!!!!!! " << threshold << endl;
            while(attackValue>threshold)
            {
                cur1->set_sql("DELETE FROM ai_Army "
                              "WHERE map_ID = ? AND player_ID = ? "
                              "ORDER BY uniqueunit_id ASC "
                              "LIMIT 1; ");
                 cur1->prepare();
                 cur1->bind(1, AI_map_ID);
                 cur1->bind(2, player_ID);
                 cur1->step();
                 cur1->reset();
                 vector<int> armyValues = troopCounter(AI_map_ID, player_ID, "AI");
                 attackValue = armyValues[0];
            }
        }
    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}


int battle(int map_ID, int player_ID, int AI_map_ID) ///Calculates the threshold for the loss of troops to be used to delete troops from database
{
    string file = "civilwarofMalibu.db";
    try
    {
        sqlite::sqlite db(file);
        auto cur1=db.get_statement();

        vector<int> AI_Army = troopCounter(AI_map_ID, player_ID, "AI");
        int AIAttackTotal = AI_Army[0];
        int AIDefenceTotal = AI_Army[1];
        vector<int> player_Army = troopCounter(map_ID, player_ID, "Player");
        int playerAttackTotal = player_Army[0];
        int playerDefenceTotal = player_Army[1];
        int AIAttack = rand() % AIAttackTotal/10 + AIAttackTotal;
        int AIDefence = rand() % AIDefenceTotal/10 + AIDefenceTotal;
        int playerAttack = rand() % playerAttackTotal/10 + playerAttackTotal;
        int playerDefence = rand() % playerDefenceTotal/10 + playerDefenceTotal;

        cout << "Player Attack roll is: " << playerAttack << endl;
        cout << "AI Attack roll is: " << AIAttack << endl;
        cout << "Player Def roll is: " << playerDefence << endl;
        cout << "AI Def roll is: " << AIDefence << endl;    
        if (AIAttack>playerAttack)
        {
            if (AIAttack>2*playerAttack)
            {
                cout << "AI wiped out your army!" << endl;
                cur1->set_sql("DELETE FROM player_Army "
                              "WHERE map_ID = ? AND player_ID = ? ");
                cur1->prepare();
                cur1->bind(1, map_ID);
                cur1->bind(2, player_ID);
                cur1->step();
            }
            else
            {
                cout << "AI won the battle!" << endl;
                int threshold = static_cast<double>(AIAttack) - (static_cast<double>(AIAttack)*(static_cast<double>(AIDefence)/static_cast<double>(playerAttack)));
                delTroops(threshold, map_ID, player_ID, AI_map_ID, "AI");
            }
        }
        else if (playerAttack>AIAttack)
        {
            if (playerAttack>2*AIAttack)
            {
                cur1->set_sql("DELETE FROM ai_Army "
                              "WHERE map_ID = ? AND player_ID = ? ");
                cur1->prepare();
                cur1->bind(1, AI_map_ID);
                cur1->bind(2, player_ID);
                cur1->step();
            }
            else
            {
                cout << "You won the battle!" << endl;
                int threshold = static_cast<double>(playerAttack) - (static_cast<double>(playerAttack)*(static_cast<double>(playerDefence)/static_cast<double>(AIAttack)));
                delTroops(threshold, map_ID, player_ID, AI_map_ID, "Player");
            }
        }
        else if (playerAttack==AIAttack)
        {
            cout << "Battle was a draw!" << endl;
        }
    }
    catch(sqlite::exception e)
    {
        std::cerr << e.what() << endl;
    }
}

//
//Adam's code END
//

int AITurn() //runs from here
{
	int aSize = findAmountAi();//Find size of AI territory
	int mapStep[aSize];//Start the map
	int* map = findAI(mapStep); //Get the map

	int territoryArray[2];
	int* selTerritory =selectTerr(map,aSize,territoryArray);//Returns ai territory and selected player territory

	int selPlayerTerritory = selTerritory[0]+selTerritory[1];
	int selAiTerritory = selTerritory[0];

	int defence = rand() % (100);//generates a random number for AI personality per turn
	int attack = rand() % (100);

	if(attack >= defence)//attack wins WE FIGHT TODAY LADS
	{
		battle(selPlayerTerritory, player_IDint, selAiTerritory);//Start adams code and work the battle out
		cout << "AI attacked player!" << endl;
	}
	else//Be boring and make more army
	{
		addArmy(selTerritory[0]);//Add some army to the AI
		cout << "AI added forces." << endl;
	}


}

int main()
{
	srand(time(0));//Sets the seed for RNG
	AITurn();//calls function to run ai's turn
	return 0;
}
