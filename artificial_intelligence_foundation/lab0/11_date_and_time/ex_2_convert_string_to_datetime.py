# Exercise 2: Convert string into a datetime object
# For example, You received the following date in string format. Please convert it into Python’s DateTime object.
from datetime import datetime


def convert_string_to_dt(str):
    dt = datetime.strptime(str, '%b %d %Y %I:%M%p')
    return dt

date_string = "Feb 25 2020 4:20PM"
print(convert_string_to_dt(date_string))