from random import *

class SoldierTypes:
    #import values via database in actual C++ code;
    #this is for testing algorithm
    soldierName = ["HoloSoldier", "HoloBike", "HoloTank", "HoloXcom"]
    soldierAtk = [10, 25, 60, 100]
    size = len(soldierAtk) 

def enemyArmyBuild(plyrAtkVal):
    enmyTroops = [] #array for tracking how many of each troop
    enmyAtkVal = 0 #tracks how much attack power the enemy has

    #minimum and maximum attack values for enemy army below;
    #using two variables so there is some diversity in
    #enemy armies made.
    #If group thinks it's a good idea, 
    minPerc = 1.25 * plyrAtkVal
    maxPerc = 1.35 * plyrAtkVal

    indWeights = [] #array to hold weighted values, so weaker troops are chosen more often than stronger ones
    totalWeight = 0 #holds maximum for random number, to be used later
    totalTroop = sum(SoldierTypes.soldierAtk)
    for atk in SoldierTypes.soldierAtk:
        curWeight = int((1-(atk/totalTroop)) * 100) #formula for calculating individual weight of one troop; weaker ones have higher numbers
        indWeights.append(curWeight)
        totalWeight = totalWeight+curWeight
    
    
    while minPerc >= enmyAtkVal: #loop means program keeps trying to build army until minimum is reached
        randNum = randint(1, totalWeight)
        counter = 0 #variable to keep track of which troop is used for comparison (in array index)
        weightCheck = 0 #variable to keep track of weight (for comparison)
        for weight in indWeights:
            weightCheck = weightCheck + weight #adds current weight
            if randNum <= weight: #checks if weighted number fits
                if SoldierTypes.soldierAtk[counter] + enmyAtkVal <= maxPerc: #make sure adding this troop doesn't make enemy army too strong
                    enmyTroops.append(SoldierTypes.soldierName[counter])
                    enmyAtkVal += SoldierTypes.soldierAtk[counter]
            counter +=1
                
    #code below just counts and prints how many troops there are in the enemy army,
    #so don't need to adapt it for C++ version. Remember to return enemy troops
    #(whether class, struct or other type) from function in C++ version.
    soldier = 0
    tank = 0
    bike = 0
    xcom = 0
    for i in enmyTroops:
        if i == "HoloSoldier":
            soldier += 1
        elif i == "HoloTank":
            tank +=1
        elif i == "HoloBike":
            bike +=1
        elif i == "HoloXcom":
            xcom += 1
    
    print("Soldier:", soldier)
    print("Tank:", tank)
    print("Bike:", bike)
    print("Xcom:", xcom)
    print("Enemy attack value:", enmyAtkVal)

enemyArmyBuild(500)
