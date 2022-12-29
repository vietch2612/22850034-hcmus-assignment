# Exercise 10: Remove all occurrences of a specific item from a list.
# Given a Python list, write a program to remove all occurrences of given number

def remove_occur(list, item_to_be_removed):
    for i in list:
        if i == item_to_be_removed:
            list.remove(i)
    return list


list1 = [5, 20, 15, 20, 25, 50, 20]
print(remove_occur(list=list1, item_to_be_removed=20))