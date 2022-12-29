# Exercise 4: Concatenate two lists in the following order
# list1 = ["Hello ", "take "]
# list2 = ["Dear", "Sir"]
# Result
# ['Hello Dear', 'Hello Sir', 'take Dear', 'take Sir']

def concatenate(list1, list2):
    return [x + y for x in list1 for y in list2]


list1 = ["Hello ", "take "]
list2 = ["Dear", "Sir"]
print(concatenate(list1, list2))
