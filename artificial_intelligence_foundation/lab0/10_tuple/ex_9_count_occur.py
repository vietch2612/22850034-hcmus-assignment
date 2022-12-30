# Exercise 9: Counts the number of occurrences of item 50 from a tuple

def count_occur(tup, item):
    return tup.count(item)


tuple1 = (45, 45, 45, 45)
print(count_occur(tuple1, 45))