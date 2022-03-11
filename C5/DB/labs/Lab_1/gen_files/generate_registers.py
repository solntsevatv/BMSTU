from generate_stairs import generate_stair_records
import random as rd

def generate_stair_student_records(n, student_col, stair_col):
    record = ''
    for i in range(0, n):
        record += '(' + str(i + 1) + ', '
        record += str(rd.randint(1, stair_col)) + ', '
        record += str(rd.randint(1, student_col)) + ', '
        record += '\'' + str(rd.randint(1, 31)) + '.' + str(rd.randint(1, 12)) + '.' + str(rd.randint(2019, 2021)) + '\'' + ', '
        record += '\'' + str(rd.randint(0, 23)) + ':' + str(rd.randint(1, 59)) + ':' + str(rd.randint(1, 59)) + '\''
        record += '),\n'
    return record

def generate_stair_teacher_records(n, teacher_col, stair_col):
    record = ''
    for i in range(0, n):
        record += '(' + str(i + 1) + ', '
        record += str(rd.randint(1, stair_col)) + ', '
        record += str(rd.randint(1, teacher_col)) + ', '
        record += '\'' + str(rd.randint(1, 31)) + '.' + str(rd.randint(1, 12)) + '.' + str(rd.randint(2019, 2021)) + '\'' + ', '
        record += '\'' + str(rd.randint(0, 23)) + ':' + str(rd.randint(1, 59)) + ':' + str(rd.randint(1, 59)) + '\''
        record += '),\n'
    return record
