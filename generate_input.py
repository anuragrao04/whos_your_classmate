#!/usr/bin/python3
import random
from indian_names import get_full_name

def generate_file(num_classes, num_students):
    students = []
    for i in range(1, num_students + 1):
        name = get_full_name()  # generate a random Indian name
        srn = "PES2UG22CS" + str(i).zfill(3)  # zfill pads the string with zeros
        gpa = round(random.gauss(7.5, 1), 2)  # round to 2 decimal places
        if gpa > 10:  # ensure GPA is not greater than 10
            gpa = 10
        elif gpa < 0:  # ensure GPA is not less than 0
            gpa = 0
        students.append((name, srn, gpa))

    with open('input_students.txt', 'w') as f:
        f.write(str(num_classes) + "\n")
        f.write(str(num_students) + "\n")
        for student in students:
            f.write(student[0] + "\n")
            f.write(student[1] + "\n")
            f.write(str(student[2]) + "\n")

# collect input from the user
num_classes = int(input("Enter the number of classes: "))
num_students = int(input("Enter the total number of students: "))

# generate the file
generate_file(num_classes, num_students)
