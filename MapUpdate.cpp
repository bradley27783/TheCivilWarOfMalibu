#include <iostream> 
#include <string> //using string library to gain access to functions that can replace parts of string
#include "ArmyCalc.cpp"
#include "libsqlite.hpp"

using namespace std;

string mapUpdate(int playerID)
{
    /* This function takes a playerID, and based on that ID, it returns a string containing a map,
     * with the enemy's army values in displayed on relevant territories and a note of which maps
     * the player already owns
     */
    
    sqlite::sqlite db("civilwarofMalibu.db"); //connect to database
    auto cur = db.get_statement(); //set query
    cur->set_sql("SELECT Owned "
		"FROM Map "
        "WHERE player_ID = ? " 
        "ORDER BY map_ID ASC;");
    
    cur->prepare(); //run query
    
    cur->bind(1, playerID); //using placeholders to protect against SQL injection

    
    
	string map;
	map =
		"#######################################################################################################\n"
		"#######################################################################################################\n"
		"##    #################################################################################################\n"
		"##         ############################################################################################\n"
		"##      1       ##################################################################     ###########   ##\n"
		"##     1L1      |   ############################################ #  #####  # ####         #####      ##\n"
		"##    1EEE1     |       |   ######################         ###       |        |            |         ##\n"
		"#######         |   2   |          |             |    5    |    6    |    7   |    8       |    9    ##\n"
		"#################  2L2  |     3    |      4      |   5L5   |   6L6   |   7L7  |   8L8      |   9L9   ##\n"
		"################# 2EEE2 |    3L3   |     4L4     |  5EEE5  |  6EEE6  |  7EEE7 |  8EEE8     |  9EEE9  ##\n"
		"######################  |   3EEE3  |    4EEE4    |         |        ####      |      #########       ##\n"
		"############################       |          #####       ####     ######   #####################    ##\n"
		"##############################     |       ######### ### ##########################################  ##\n"
		"################################   |   ################################################################\n"
		"#######################################################################################################\n"
		"#######################################################################################################\n";
    /* Note: characters like "1L1" in the string above (for the map) are meant to act as placeholders to 
	 * show specific values, which will then then be replaced (with strings like "OWN", 
	 * for example, to show that the player owns the territory). Numbers on their own mark the 
	 * territory number and don't change. Numbers like "11E11" mark where enemy army values will be displayed.
	 */

    
    int curTerrInt = 1; //keeps track of which index current territory is at
    int curEnInt = 9; //another variable for keeping track (this time for where to place enemy value)
    while( cur->step() )
    {
        int currTerrain = cur->get_int(0); //using "get_int" because SQLite doesn't support boolean data types
        string terrStringToReplace = to_string(curTerrInt) + "L" + to_string(curTerrInt); //loops through strings on map that say "1L1", "2L2", etc.
        string enStringToReplace = to_string(curEnInt) + "EEE" + to_string(curEnInt); //loops through strings on map that say "1EEE1", "2EEE2", etc.

        string terrReplacedWith;
        string enReplacedWith;
        
        string::size_type terrCheck = map.find(terrStringToReplace); //finds position of string to replace
        string::size_type enCheck = map.find(enStringToReplace);
        
        switch(currTerrain) //makes appropriate adjustment based on data value
        {
            case 0:
                terrReplacedWith = "   "; //string with three spaces when territory is not owned
                break;
            case 1:
                terrReplacedWith = "OWN"; //this string tells user they won the territory on the map
                break;
            default: //if map stores an integer other than 1 and 0, this means value is invalid, so throw exception
                throw invalid_argument("The maps table has an invalid value!\nIt is only meant to have 1s or 0s.\n");
        }
        map.replace(terrCheck, 3, terrReplacedWith); //performs the actual replacement in the map for owning
        
        enReplacedWith = armyCalc(playerID, curEnInt, "ai");
        
        switch(enReplacedWith.length()) //formatting string to 5 characters so it fits in map
        {
            case 1:
                enReplacedWith = "  " + enReplacedWith + "  ";
                break;
            case 2:
                enReplacedWith = " " + enReplacedWith + "  ";
                break;
            case 3:
                enReplacedWith = " " + enReplacedWith + " ";
                break;
            case 4:
                enReplacedWith = enReplacedWith + " ";
                break;
            case 5:
                break;
            case 6 ... 9: //if length is between 6 and 9 characters; very unlikely it wil reach this
                enReplacedWith = ">9999"; //tells user what value is over, since doesn't fit
                break;
            default:
                enReplacedWith = "     ";
        }
        map.replace(enCheck, 5, enReplacedWith); //performs the actual replacement in the map for enemy army values
		curTerrInt++;
        curEnInt--;
    }
    
    cur->reset();
    
    /* Note: Cannot close database connection because, in libsqlite.hpp, the destructor (~sqlite())
     * does not require any arguments, but a function it calls inside does (and the inner function, which
     * is sqlite3_close() expects an sqlite3 class, while libsqlite.hpp provides an sqlite::sqlite class). 
     * 
     * If it were possible, I would have closed the connection to the database, but that is not important
     * because the connection will close when this function finishes since the connection is encapsulated
     * in this function.*/

    return map; //return rather than print if someone wants to do further manipulation
}
