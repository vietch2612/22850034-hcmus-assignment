# Exercise 6: Find the intersection (common) of two sets and
# remove those elements from the first set

def find_common_and_remove(first_set, second_set):
    common_set = []
    for i in first_set:
        for j in second_set:
            if i == j:
                common_set.append(i)
    print('Intersection:', common_set)
    for k in common_set:
        first_set.remove(k)
    print('First set after removed:', first_set)

first_set = {23, 42, 65, 57, 78, 83, 29}
second_set = {57, 83, 29, 67, 73, 43, 48}
find_common_and_remove(first_set=first_set, second_set=second_set)