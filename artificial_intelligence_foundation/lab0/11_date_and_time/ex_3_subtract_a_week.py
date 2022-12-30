# Exercise 3: Subtract a week (7 days)  from a given date in Python

from datetime import datetime, timedelta


def subtract_by_day(dt, days):
    return dt - timedelta(days=days)


given_date = datetime(2020, 2, 25)
print(subtract_by_day(given_date, 7))
