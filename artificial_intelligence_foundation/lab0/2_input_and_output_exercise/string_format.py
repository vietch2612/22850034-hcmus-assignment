# Write a program to print the paragraph
# input
# first_name = 'Viet'
# last_name = 'Cao'
# middle_name = 'Hoai'
# expected_gpa = 9

first_name = 'Viet'
last_name = 'Cao'
middle_name = 'Hoai'
expected_gpa = 9
paragraph = "My name is {0} {1} {2} and my expected GPA is {3:.2f}"
print(paragraph.format(last_name, middle_name, first_name, expected_gpa))