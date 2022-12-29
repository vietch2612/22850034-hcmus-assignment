# Exercise 3: Create a new string made of the first, middle, and last characters of each input string
# Given two strings, s1 and s2, write a program to return a new string made of s1 and s2’s first, middle, and last characters.

def create_new_string(s1, s2):
    char1 = s1[0]
    char2 = s2[0]
    char3 = s1[int(len(s1) / 2)]
    char4 = s2[int(len(s2) / 2)]
    char5 = s1[len(s1) - 1]
    char6 = s2[len(s2) - 1]
    return "{0}{1}{2}{3}{4}{5}".format(char1, char2, char3, char4, char5, char6)


print(create_new_string("America", "Japan"))