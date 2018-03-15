#include <iostream>
#include <string>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h> 
#include "libsqlite.hpp"

using namespace std;

//declarations

int addArmy(int terr);
int balancedAI();
bool worthAttack(int playerDefence, int attackValue);
int terrToAttack(int map[]);
int[] mapDB();

const char* database = "civilwarofMalibu.db";
const char* player_ID = "1";
sqlite::sqlite db( database );//Opens database

int addArmy(int terr){
	int military_ID=((rand()%1)>4);

	auto cur = db.get_statement();
	cur->set_sql("INSERT INTO ai_Army ( player_ID, military_ID, map_ID)"
		"VALUES (?,?,?);");

	cur->prepare();//Send query

	cur->bind(1,player_ID);
	cur->bind(2,military_ID);
	cur->bind(3,terr);

	cur->step();
}


int balancedAI()
{
	int map = mapDB();//Gets an array of AI owned territories, for checking

	array moveStats = terrToAttack(map);//Gets territory ai owns and attacking territory
	int moveStats_aiTerr=moveStats[0];
	int moveStats_Way=moveStats[1];



	int attackValue=aiArmyDB(moveStats_Way);
	int defenceValue=aiArmyDB(moveStats_Way);

	int playerAttack=playerArmyDB(moveStats_Way);
	int playerDefence=playerArmyDB(moveStats_Way);


	if(worthAttack(playerDefence,attackValue))//Is attack worth it?
	{
		if((rand()%100)>20)//Defence
			{
				addArmy(moveStats_aiTerr);//Adds army to ai
			}
			else
			{//Attack
				//attack code
			}
	}
	else
	{
		addArmy(moveStats_aiTerr);
	}

	return 0;

}

bool worthAttack(int playerDefence, int attackValue)
{
	if(attackValue > playerDefence)//Attack value is bigger than defence 
	{
		return true;
	}
	else
	{
		return false;
	}
}

int terrToAttack(int map[]) //Finds an appropriate place to attack or defend
{
	int terr = 1;
	while(true)
	{
		if(any_of(begin(map[0]), end(map[0]), [&](int i)) {return i == terr+1;} == False) //Solution from https://stackoverflow.com/questions/19299508/how-can-i-check-if-given-int-exists-in-array
		{//Not an AI territory
			return(terr,terr+1);
		}
		else if (any_of(begin(map[0]), end(map[0]), [&](int i)) {return i == terr-1;} == False)
		{//Not an AI territory
			return(terr,terr-1);
		}
		terr++;
	}
}

int[] mapDB() // Gets the map information
{
	int aiMap[3] {2,3,4};
	return(aiMap);//list of ai territories
}

int playerArmyDB() //Gets the player stats for specific territories
{

}

int aiArmyDB() //Gets the ai army stats for specific terroriories
{

}

int endTurn() //Sends information to update the map
{

}

int main()
{
	addArmy(5);
	return 0;
}
