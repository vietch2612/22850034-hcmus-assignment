# Exercise 7: Check if two sets have any elements in common. If yes, display the common elements

def get_common_items(set1, set2):
    return set1.intersection(set2)


set1 = {10, 20, 30, 40, 50}
set2 = {60, 70, 80, 90, 10}
print(get_common_items(set1, set2))