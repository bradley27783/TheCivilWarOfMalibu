#include <iostream>
#include <string>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h> 
#include <tuple>
#include "libsqlite.hpp"

using namespace std;


int aiPers = 90; //100 full agression, 0 full defence
int aiDefence = 70; //100 full military units, 0 full production units



int main()
{

}

void AI()
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
		if((rand()%100)>aiPers)//Defence
			{
				//Can do both Production and army
				if((rand()%100)>10)//Production
				{
					buyProduction();
				}
				if((rand()%100)>40)//Army
				{
					buyArmy();
				}
				
			}
			else
			{//Attack
				//attack code
			}
	}
	else
	{

		if((rand()%100)>10)//Production
		{
			buyProduction();
		}
		if((rand()%100)>40)//Army
		{
			buyArmy();
		}
	}

	

}

bool worthAttack(playerDefence,attackValue)
{
	if(attackValue > playerDefence)
	{
		return True;
	}
	else
	{
		return False;
	}
}

tuple terrToAttack(map) //Finds an appropriate place to attack or defend
{
	int terr = 1;
	int maxTerritories = 9;
	while(true){
		if(any_of(begin(map[0]), end(map[0]), [&](int i) {return i == terr+1;} == False); //Solution from https://stackoverflow.com/questions/19299508/how-can-i-check-if-given-int-exists-in-array
		{//Not an AI territory
			if(terr+1 > maxTerritories)
			{
			
			}
			else
			{
				return make_tuple(terr,terr+1);
			}
		}
		else if (any_of(begin(map[0]), end(map[0]), [&](int i) {return i == terr-1;} == False);
		{//Not an AI territory
			if(terr-1 <= 0)
			{
				
			}
			else
			{
				return make_tuple(terr,terr-1);
			}
		}
		terr++;
	}
}

int mapDB() // Gets the map information
{
	
	int aiMap [9] = [1,2,3]; //list of ai territories
	return(aiMap);
}

int playerArmyDB() //Gets the player stats for specific territories
{

}

int aiArmyDB() //Gets the ai army stats for specific terroriories
{

}

int updateMap() //Sends information to update the map
{

}