# Exercise 6: Create a recursive function
# Write a program to create a recursive function to calculate the sum of numbers from 0 to 10.
# A recursive function is a function that calls itself again and again.

def add(num):
    if num > 0:
        return num + add(num - 1)
    else:
        return 0


print(add(20))