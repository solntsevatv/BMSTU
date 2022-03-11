from generate_humans import *
from generate_registers import *
from generate_stairs import *

file_teachers = open('data_teachers.txt', 'w', encoding='utf8')
file_students = open('data_students.txt', 'w', encoding='utf8')
file_stairs = open('data_stairs.txt', 'w', encoding='utf8')

file_records_teachers = open('data_records_teachers.txt', 'w', encoding='utf8')
file_records_students = open('data_records_students.txt', 'w', encoding='utf8')

file_teachers.write(generate_teacher_records(1000))
file_students.write(generate_student_records(3000))
file_stairs.write(generate_stair_records(10000))

file_records_students.write(generate_stair_student_records(5000, 3000, 10000))
file_records_teachers.write(generate_stair_teacher_records(5000, 1000, 10000))