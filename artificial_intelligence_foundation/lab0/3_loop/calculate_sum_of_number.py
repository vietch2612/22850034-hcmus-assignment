# Write a program to accept a number from a user and
# calculate the sum of all numbers from 1 to a given number
# For example, if the user entered 10 the output should be
# 55 (1+2+3+4+5+6+7+8+9+10)
number = int(input("Enter your number: "))
total = 0
for i in range(1, number + 1):
    total += i
print("The sum number is: ", total)