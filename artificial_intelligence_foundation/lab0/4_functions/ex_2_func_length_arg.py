# Exercise 2: Create a function with variable length of arguments
# Write a program to create function func1() to accept a variable length of arguments and print their value.
# Note: Create a function in such a way that we can pass any number of arguments to this function,
# and the function should process them and display each argument’s value.
def function1(*args):
    for arg in args:
        print(arg)


function1(1,2,3,4,5)
function1(39,10,'a',1,'f',1)