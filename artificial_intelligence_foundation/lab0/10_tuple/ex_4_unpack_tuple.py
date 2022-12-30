# Exercise 4: Unpack the tuple into 4 variables
# Write a program to unpack the following tuple into four variables and display each variable.

def unpack_tuple(tup):
    a, b, c, d = tup
    print(a)
    print(b)
    print(c)
    print(d)


tup = (1,2,3,4)
unpack_tuple(tup)