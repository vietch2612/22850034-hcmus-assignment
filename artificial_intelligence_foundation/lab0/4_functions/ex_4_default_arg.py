# Exercise 4: Create a function with a default argument
# Write a program to create a function show_employee() using the following conditions.
# It should accept the employee’s name and salary and display both.
# If the salary is missing in the function call then assign default value 9000 to salary
def show_employee(name, salaray=9_000):
    message = "Name: {0}, Salary: {1}"
    print(message.format(name, salaray))

show_employee("Viet", 4_000)
show_employee("Tam")