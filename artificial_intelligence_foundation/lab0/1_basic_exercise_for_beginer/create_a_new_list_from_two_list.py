# Create a new list from a two list using the following condition
# Given a two list of numbers, write a program to create a new list such that 
# the new list should contain odd numbers from the first list and even numbers from the second list.
# Give list1 = [10, 20, 25, 30, 35]
# list2 = [40, 45, 60, 75, 90]
# Expected
# Result list: [25, 35, 40, 60, 90]

list1 = [10, 20, 25, 30, 35]
list2 = [40, 45, 60, 75, 90]
new_list = []

for num1 in list1:
    if num1 % 2 != 0:
        new_list.append(num1)

for num2 in list2:
    if num2 % 2 == 0:
        new_list.append(num2)

print('result list:', new_list)