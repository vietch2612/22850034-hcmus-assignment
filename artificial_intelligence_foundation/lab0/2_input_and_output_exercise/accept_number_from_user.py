# Write a program to accept two numbers from the user and calculate multiplication
number_1 = int(input("Enter your first number: "))
number_2 = int(input("Enter your second number: "))
paragraph = "{0} * {1} = {2}"
print(paragraph.format(number_1, number_2, number_1 * number_2))