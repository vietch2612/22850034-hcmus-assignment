# Display numbers divisible by 5 from a list
# Given list is  [10, 20, 33, 46, 55]
# Divisible by 5
# 10
# 20
# 55

given_list = [10, 20, 33, 46, 55]
print('Given list is', end=" ")
print(given_list)
print('Devisible by 5')
for num in given_list:
    if num % 5 == 0:
        print(num)