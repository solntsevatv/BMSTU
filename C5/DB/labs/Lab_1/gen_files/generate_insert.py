insert_file = open('new_insert.sql', 'w', encoding='utf8')

data_stairs = open('data_stairs.txt', 'r', encoding='utf8')

insert_file.write(
    'INSERT INTO STAIRS (\n'
    'id,\n'
    'staircase_id,\n'
    'step_num,\n'
    'height,\n'
    'len,\n'
    'width\n'
    ')\n'
    'VALUES\n'
)

for line in data_stairs:
    insert_file.write(line)

insert_file.write(';')


data_students = open('data_students.txt', 'r', encoding='utf8')

insert_file.write(
    '\n'
    'INSERT INTO STUDENTS (\n'
    'id,\n'
    'surname,\n'
    'name,\n'
    'lastname,\n'
    'age,\n'
    'departament,\n'
    'sex\n'
    ')\n'
    'VALUES\n'
)

for line in data_students:
    insert_file.write(line)

insert_file.write(';')


data_teachers = open('data_teachers.txt', 'r', encoding='utf8')

insert_file.write(
    '\n'
    'INSERT INTO TEACHERS (\n'
    'id,\n'
    'surname,\n'
    'name,\n'
    'lastname,\n'
    'age,\n'
    'departament,\n'
    'degree,\n'
    'sex\n'
    ')\n'
    'VALUES\n'
)

for line in data_teachers:
    insert_file.write(line)

insert_file.write(';')


data_records_students = open('data_records_students.txt', 'r', encoding='utf8')

insert_file.write(
    '\n'
    'INSERT INTO STUDENT_STAIR_REGISTER (\n'
    'id,\n'
    'stair,\n'
    'student,\n'
    'entry_date,\n'
    'entry_time\n'
    ')\n'
    'VALUES\n'
)

for line in data_records_students:
    insert_file.write(line)

insert_file.write(';')


data_records_teachers = open('data_records_teachers.txt', 'r', encoding='utf8')

insert_file.write(
    '\n'
    'INSERT INTO TEACHER_STAIR_REGISTER (\n'
    'id,\n'
    'stair,\n'
    'teacher,\n'
    'entry_date,\n'
    'entry_time\n'
    ')\n'
    'VALUES\n'
)

for line in data_records_teachers:
    insert_file.write(line)

insert_file.write(';')