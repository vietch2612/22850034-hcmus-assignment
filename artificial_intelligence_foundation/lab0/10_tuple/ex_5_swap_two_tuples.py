# Exercise 5: Swap two tuples in Python


def swap_tuples(tup1, tup2):
    return tup2, tup1

tup1 = (11, 22)
tup2 = (99, 88)

tup1, tup2 = swap_tuples(tup1, tup2)
print(tup1)
print(tup2)


