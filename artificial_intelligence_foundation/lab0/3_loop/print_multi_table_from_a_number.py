# Write a program to print multiplication table of a given number
# For example, num = 2 so the output should be
# 2
# 4
# 6
# 8
# 10
# 12
# 14
# 16
# 18
# 20
num = 3
str_format = "{0} * {1} = {2}"
for i in range (1, 11):
    result = num * i
    print(str_format.format(num, i, result))