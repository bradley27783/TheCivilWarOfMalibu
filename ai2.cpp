#include <iostream>
#include <string>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h> 
#include "libsqlite.hpp"

using namespace std;



const char* database = "civilwarofMalibu.db";
const char* player_ID = "0";


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
	int aiNum=0;
	try
	{
		sqlite::sqlite db( database );//Opens database

		auto cur1 = db.get_statement();
		cur1->set_sql("SELECT Owned FROM Map;");//Selecting owned column of map
		cur1->prepare();


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

int selectTerr(int* Aimap, int aSize)//Find appropriate territory
{	
	int terr[aSize];
	int i;
	int sT;
	for(i = 0; i < aSize;i++)//Go through the map
	{
		sT=Aimap[i];//Selected territory

		if( !(inArray(sT+1, Aimap, aSize)) || !(inArray(sT-1, Aimap, aSize)) )//Checks if it is owned by AI already
		{
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
			return(terr[terChoose]);
		}
		timer++;//increment timer
	}
	return 0;
	//enter win condition intergration here	
}

int attackPlayer()
{

	//intergration here
}

int AITurn() //runs from here
{
	int aSize = findAmountAi();//Find size of AI territory
	int mapStep[aSize];//Start the map
	int *map = findAI(mapStep); //Get the map

	int selTerritory =selectTerr(map,aSize);

	int defence = rand() % (100);//generates a random number for AI personality per turn
	int attack = rand() % (100);

	if(attack >= defence)//attack wins WE FIGHT TODAY LADS
	{
		attackPlayer();
		cout << "AI attacked player!" << endl;
	}
	else
	{
		addArmy(selTerritory);
		cout << "AI added forces." << endl;
	}


}

int main()
{
	srand(time(0));//Sets the seed for RNG
	AITurn();//calls function to run ai's turn
	return 0;
}
