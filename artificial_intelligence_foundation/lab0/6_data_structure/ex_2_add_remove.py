# Exercise 2: Remove and add item in a list
# Write a program to remove the item present at index 4
# and add it to the 2nd position and at the end of the list.

def add_and_remove(list):
    print('Original list: ', list)

    e = list.pop(4)
    print('The list after removing an element at index 4:', list)

    list.insert(2, e)
    print('The list after inserting an element at index 2:', list)

    list.append(e)
    print('The list after appending an element in the last:', list)


add_and_remove([0,1,2,3,4,5,6,7,8,9])

