# Exercise 4: Print a date in a the following format
# Expected output: Tuesday 25 February 2020

from datetime import datetime


def format_date(dt, format):
    return dt.strftime(format)


given_date = datetime(2020, 2, 25)
format = '%A %d %B %Y'
print(format_date(given_date, format))
