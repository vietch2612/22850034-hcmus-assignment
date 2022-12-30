# Exercise 5: Remove items from the set at once
# Write a Python program to remove items 10, 20, 30 from the following set at once

def remove_from_set(input_set, set_to_be_removed):
    input_set.difference_update(set_to_be_removed)
    return input_set


input_set = {10, 20, 30, 40, 50}
set_to_be_removed = {10, 20, 30}
print(remove_from_set(input_set, set_to_be_removed))