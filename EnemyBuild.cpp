#include <iostream>
#include <random> //using this to generate random number
#include <vector> //using vector because database is dynamic and do not know how many troop types in database; therefore, vector is easier because it does not require an upper limit to be defined
                  //edit: vector usage only for test purposes (counting how many troops there are)

#include "libsqlite.hpp"
#include "ArmyCalc.cpp" //using this to find player's army value

using namespace std;

struct SoldierInfo  //class for storing variables related to soldiers/troops
{
	vector<string> soldierNames;
	vector<int> soldierAttackValues;

	vector<int> individualWeights; //vector to store weighted values, so weaker troops are chosen more often
	int totalWeights = 0; //stores maximum value for random integer, to store later
	double totalTroopAttack = 0; //stores attack value of all troops added together, to use for creating a weighted troop-picker
};

void enemyArmyBuild(int playerID, int territoryID)
{
	/* This function takes the player's ID and a territory ID, and then generates
	 * a random AI army for a specific territory that is somewhere between 90% and
	 * 110% of the player army's attack value in the "highest" territory number they
	 * own. The AI's army is then stored in the database, so it can be used later.
	 */
    
	SoldierInfo currentInfo; //creates object from struct, to interact with

	sqlite::sqlite db("civilwarofMalibu.db"); //connect to database
	auto cur = db.get_statement(); //set cursor
	
    int playerAttackVal = 0;
    
    cur->set_sql(
		"SELECT map_ID "
		"FROM Map "
        "WHERE player_ID = ? AND Owned = 1 " //beore and specifies player, after and specifies army at territory owned by player
        "ORDER BY map_ID DESC " //Highest number first (which is what I want)
        "LIMIT 1; "); //using "LIMIT" because implementation of "TOP" varies more depending on SQL dialect (Oracle, Microsoft and MySQL all have different ways of specifying "TOP").
    
    cur->prepare();
    cur->bind(1, playerID);
    cur->step();
    
    int topTerritory = cur->get_int(0); //gets top territory 
    playerAttackVal = stoi(armyCalc(playerID, topTerritory, "player")); //calls function to get player's army attack value. (Converts string to integer, because that's what's needed.)
    
    if (playerAttackVal < 10)
    {
        playerAttackVal = 10; /* quick code to protect against cases where top territory might not have any troops,
                               * so enemy can still build (very weak) army in this case. */
    }
    
    cur->reset(); //resets cursor to prepare for new query
    
	cur->set_sql(
		"SELECT Name, Attack "
		"FROM military_Units;"); //get required troop data from relevant table in database (using multiple lines to make SQL code clearer)
	
	cur->prepare();
    
	while (cur->step()) //while loop to import all relevant data from database into struct
	{
		currentInfo.soldierNames.push_back(cur->get_text(0));
		currentInfo.soldierAttackValues.push_back(cur->get_int(1));
	}

	for (int troopAttack : currentInfo.soldierAttackValues)
	{
		currentInfo.totalTroopAttack += troopAttack;
	}

	//vector<string> enemyTroops; //stores troops in enemy army; this is just for testing purposes
	int enemyAttackVal = 0; //stores attack value of enemy army

	//below two integers are const because the value does not need to change, 
	//and they are ints instead o floats/doubles because precision is not needed
	const int minPerc = 0.9 * playerAttackVal; //defines minimum attack value enemy army can have in relation to player's army
	const int maxPerc = 1.1 * playerAttackVal; //defines maximum attack value enemy army can have in relation to player's army

	for (double troopAttack : currentInfo.soldierAttackValues) //for loopcalculates weights to decide how often troops are chosen for the enemy army in here
	{
		int tempWeight = (1 - (troopAttack / currentInfo.totalTroopAttack)) * 100; //formula for calculating individual weight of one troop; weaker ones have higher numbers
		currentInfo.individualWeights.push_back(tempWeight);
		currentInfo.totalWeights += tempWeight;
	}
    
    cur->reset(); //resets cursor, clears previous data so it can be used for a new SQL statement
    
    cur->set_sql("DELETE FROM ai_Army WHERE player_ID = ? AND map_ID =  ? ;"); 
    //deletes all previous troops for enemy at this territory because I don't want attack to stack up
    
    cur->prepare(); //sets new SQL query
    
    cur->bind(1, playerID);
    cur->bind(2, territoryID);
    
    
	while (cur->step())
    {
        //no body; this while loop just deletes all rows specified in SQL code
    }

    cur->reset(); //reset in preparation for adding troops to AI army's table
    
    
    cur->set_sql("SELECT MAX(uniqueunit_ID) FROM ai_Army; "); 
    cur->prepare();
    cur->step();
    int uniqueTroopID = cur->get_int(0) + 1; 
    /* above variable keeps track of unique unit ID to insert in SQL later;
     * it is incremented by 1 so it is unique and does not conlict with database's rules'. */
    
	while (minPerc >= enemyAttackVal) //loop means program keeps trying to build army until minimum is reached
	{
		//note: using random number generator from http://www.cplusplus.com/reference/random/mt19937/
		//because rand(), which is standard generator, always returned the same values, so there
		//was no variety for enemy armies. Also, rand() does not have a universal distribution,
		//so it does not work very well to generate more "random" numbers (all computers can only
		//generate pseudo-random numbers, but some are more random than others).
		
		random_device randGen; //random number generator
		mt19937 generator(randGen()); //mt19937 is an implementatino of a random number class
		uniform_int_distribution<int> distr(1, currentInfo.totalWeights); //defines range for random number
		int randNum = distr(generator);  //gets a number from the random number generator

		int counter = 0; // variable to track index of current troop
		int weightCheck = 0; //variable to keep track of weight (for checking which troop the current random number represents)
        
        cur->reset(); 
        /* reset SQL query each time to make room for a new one, because cannot set SQL on query if 
         * previous query has already been run, except by resetting. */

		for (int currentWeight : currentInfo.individualWeights)
		{
			weightCheck += currentWeight; //adds current weight to track
			if (randNum <= weightCheck) //checks if weighted number fits this value; if it doesn't, then next weight is tried
			{
				if (currentInfo.soldierAttackValues[counter] + enemyAttackVal <= maxPerc) //makes sure adding this troop doesn't make the enemy army too strong
				{
					enemyAttackVal += currentInfo.soldierAttackValues[counter]; //adds current troop's attack to overall value
					//enemyTroops.push_back(currentInfo.soldierNames[counter]); //no longer need vector, so commented this out	
					
                    cur->set_sql("INSERT INTO ai_Army "
                                 "VALUES (?, ?, ?, ?);"); //insert relevant values into AI army's table
                    cur->prepare(); 
                    cur->bind(1, playerID);
                    cur->bind(2, uniqueTroopID);
                    cur->bind(3, counter+1); //add 1 to counter variable because vector index starts at 0, while database starts at 1
                    cur->bind(4, territoryID);
                    cur->step(); //runs SQL statement/adds current troop to table
                    uniqueTroopID++; //increments by one so next uniqueTroopID can be given
					break; 
					/* break this loop and generate another random number, 
					 * because the appropriate troop has been found for this random number. */
				}
			}
			else
			{
				counter++; //increments counter by one so next index is tried afterwards
			}
		}
	}

	//testing code below
	/*
    int soldier = 0;
	int bike = 0;
	int tank = 0;
	
	int xcom = 0;
	for (string troop : enemyTroops)
	{
		if (troop == "HoloSoldier")
		{
			soldier += 1;
		}
		else if (troop == "HoloBike")
		{
			bike += 1;
		}
		else if (troop == "HoloTank")
		{
			tank += 1;
		}
		else if (troop == "HoloXcom")
		{
			xcom += 1;
		}
	}
	
	cout << "Holosoldiers: " << soldier << endl;
	cout << "HoloBikes: " << bike << endl;
	cout << "HoloTanks: " << tank << endl;
	cout << "HoloXcoms: " << xcom << endl;
	cout << "Total attack value: " << enemyAttackVal << endl;
	*/
	/*
    for (string name : currentInfo.soldierNames)
    {
        cout << "Name: " << name << endl;
    }
    for (int atkval : currentInfo.soldierAttackValues)
    {
        cout << "Attack value: " << atkval << endl;
    }
    for (int test : currentInfo.individualWeights)
    {
        cout << test << endl;
    }
    cout << currentInfo.totalWeights << endl;*/
}
