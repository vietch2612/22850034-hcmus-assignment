# Exercise 4: Initialize dictionary with default values


def get_dict(list):
    defaults = {"designation": 'Developer', "salary": 8000}
    return dict.fromkeys(list, defaults)


employees = ['Kelly', 'Emma']
print(get_dict(employees))