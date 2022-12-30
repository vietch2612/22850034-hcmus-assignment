# OOP Exercise 3: Create a child class Bus that will inherit all of the variables and methods of the Vehicle class

class Vehicle:
    def __init__(self, max_speed, mileage):
        self.max_speed = max_speed
        self.mileage = mileage


class Truck(Vehicle):
    pass


hovo = Vehicle(80, 30)
print(hovo.max_speed)
print(hovo.mileage)
