from random import *

class army():
    totalAtk = 0
    totalDef = 0
    def __init__(self):     
        upkeep = 0.1 * self.totalAtk

    def soldier(self, amount):
            self.totalAtk += 10 * amount
            self.totalDef += 5 * amount

    def tank(self, amount):
            self.totalAtk += 60 * amount
            self.totalDef += 30 * amount
        
    def horse(self, amount):
            self.totalAtk += 25 * amount
            self.totalDef += 15 * amount

def battle(a1,a2):
    atk1 = randint(int(a1.totalAtk*0.9),int(a1.totalAtk*1.1))
    atk2 = randint(int(a2.totalAtk*0.9),int(a2.totalAtk*1.1))
    def1 = randint(int(a1.totalDef*0.9),int(a1.totalDef*1.1))
    def2 = randint(int(a2.totalDef*0.9),int(a2.totalDef*1.1))
    print("Army 1 has rolled " + str(atk1) + " for attack")
    print("Army 2 has rolled " + str(atk2) + " for attack")
    print("Army 1 has rolled " + str(def1) + " for defense")
    print("Army 2 has rolled " + str(def2) + " for defense")
    if atk1>atk2:
        if atk1>=(2*atk2):
            print("Army 1 obliterated Army 2")
        else:
            print("Army 1 Wins the battle!")
            finalatk1 = atk1-(atk1*((def1/atk2)/2))
            finalatk2 = atk2-(atk2*(def2/atk1))
            print("Army 1 now has " + str(int(finalatk1)) + " ATK")
            print("Army 2 now has " + str(int(finalatk2)) + " ATK remaining")
    elif atk2>atk1:
        if atk2>=(2*atk1):
            print("Army 2 destroyed Army 1")
        else:
            print("Army 2 Wins the battle!")
            finalatk1 = atk1-(atk1*(def1/atk2))
            finalatk2 = atk2-(atk2*((def2/atk1)/2))
            print("Army 2 now has " + str(int(finalatk2)) + " ATK")
            print("Army 1 now has " + str(int(finalatk1)) + " ATK remaining")
    else:
        print("Battle was a draw!")
        finalatk1 = atk1*((def1/atk2)*0.75)
        finalatk2 = atk2*((def2/atk1)*0.75)
        print("Army 1 now has " + str(int(finalatk1)) + " ATK")
        print("Army 2 now has " + str(int(finalatk2)) + " ATK")
    print("--------------------------------")
    
    ### Works until the values are massively skewed in one favour
