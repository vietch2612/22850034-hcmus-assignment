# Exercise 2: Append new string in the middle of a given string
# Given two strings, s1 and s2. 
# Write a program to create a new string s3 by appending s2 in the middle of s1.

def add_to_middle(s1, s2):
    length = len(s1)
    mid = int(length/2)
    return s1[0:mid] + s2 + s1[mid:length+1]

print(add_to_middle('123789', '456'))

