# Exercise 5: Create an inner function to calculate the addition in the following way
# Create an outer function that will accept two parameters, a and b
# Create an inner function inside an outer function that will calculate the addition of a and b
# At last, an outer function will add 5 into addition and return it

def get_calculation(a, b):
    def add(a, b):
        return a + b
    return add(a, b) + 5


print(get_calculation(5, 10))
