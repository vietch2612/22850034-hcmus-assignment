# Exercise 6: Return a set of elements present in Set A or B, but not both

def return_items_not_in_both(set1, set2):
    return set1.symmetric_difference(set2)


set1 = {10, 20, 30, 40, 50}
set2 = {30, 40, 50, 60, 70}
print(return_items_not_in_both(set1, set2))