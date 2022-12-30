# Exercise 1: Convert two lists into a dictionary
# keys = ['Ten', 'Twenty', 'Thirty']
# values = [10, 20, 30]
# Expected output
# {'Ten': 10, 'Twenty': 20, 'Thirty': 30}

def convert_list_to_dictionary(list1, list2):
    new_dict = dict()
    new_dict = dict(zip(list1, list2))
    return new_dict


keys = ['Ten', 'Twenty', 'Thirty']
values = [10, 20, 30]
print(convert_list_to_dictionary(keys, values))