# Exercise 4: Count the occurrence of each element from a list
# Write a program to iterate a given list and count the occurrence of each element
# and create a dictionary to show the count of each element.

def count_occur(list):
    occur_list = dict()
    for item in list:
        if item in occur_list:
            continue
        count = 0
        for i in list:
            if i == item:
                count += 1
        occur_list[item] = count
    return occur_list


print(count_occur([11, 45, 8, 11, 23, 45, 23, 45, 89]))
