# Exercise 1B: Create a string made of the middle three characters
# Write a program to create a new string made of the middle three characters of an input string.

def get_middle_three(string):
    length = len(string)
    mid_idx = int(length/2)
    print(string[mid_idx - 1:mid_idx + 2])

get_middle_three('JhonDipPeta')
get_middle_three('JaSonAy')
get_middle_three('ConHeoNho')

