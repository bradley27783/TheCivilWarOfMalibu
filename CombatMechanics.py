class army():
    totalAtk = 0
    totalDef = 0
    def __init__(self):     
        upkeep = 0.1 * army.totalAtk

class soldier(army):
    def __init__(self, amount):
        army.totalAtk += 5 * amount
        army.totalDef += 3 * amount

class tank(army):
    def __init__(self, amount):
        army.totalAtk += 50 * amount
        army.totalDef += 25 * amount
        
class horse(army):
    def __init__(self, amount):
        army.totalAtk += 10 * amount
        army.totalDef += 5 * amount
