# Exercise 2: Merge two Python dictionaries into one

def merge(*args):
    new_dict = dict()
    for arg in args:
        new_dict.update(arg)
    return new_dict


dict1 = {'Ten': 10, 'Twenty': 20, 'Thirty': 30}
dict2 = {'Thirty': 30, 'Fourty': 40, 'Fifty': 50}
print(merge(dict1, dict2))