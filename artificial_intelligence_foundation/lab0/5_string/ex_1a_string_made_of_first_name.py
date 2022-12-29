# Exercise 1A: Create a string made of the first, middle and last character
# Write a program to create a new string made of an input string’s first, middle, and last character.
# str1 = "James"
# return Jms

str1 = 'James'
len = len(str1)
char1 = str1[0]
char2 = str1[int(len/2)]
char3 = str1[len-1]
message="{0}{1}{2}"
print(message.format(char1, char2, char3))