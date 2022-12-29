# Exercise 3: Turn every item of a list into its square
# Given a list of numbers. write a program to turn every item of a list into its square.

def turn_into_square(list):
    return [x * x for x in list]


numbers = [1, 2, 3, 4, 5, 6, 7]
print(turn_into_square(numbers))