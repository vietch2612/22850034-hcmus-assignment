# OOP Exercise 1: Create a Class with instance attributes
# Write a Python program to create a Vehicle class with max_speed and mileage instance attributes.

class Vihicle:
    def __init__(self, max_speed, mileage):
        self.max_speed = max_speed
        self.mileage = mileage


toyotaCross = Vihicle(160, 10)
print(toyotaCross.max_speed)
print(toyotaCross.mileage)

