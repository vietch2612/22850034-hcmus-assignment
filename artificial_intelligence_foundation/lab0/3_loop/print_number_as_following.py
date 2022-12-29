# Exercise 7: Print the following pattern
# 5 4 3 2 1 
# 4 3 2 1 
# 3 2 1 
# 2 1 
# 1

number = 9
while(number > 0):
    i = number
    while(i > 0):
        print(i, end = " ")
        i -= 1
    print('\t\t')
    number -= 1