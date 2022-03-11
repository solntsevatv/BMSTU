import random as rd

def create_array_from_file(f):
    return [line.replace("\n", "") for line in f]

def generate_name_surname_lastname_string(names, surnames, lastnames):
    return '\'' + surnames[rd.randint(0, len(surnames) - 1)] + '\'' +', '\
            + '\'' + names[rd.randint(0, len(names) - 1)] + '\'' +', '\
            + '\'' + lastnames[rd.randint(0, len(lastnames) - 1)]+ '\'' + ', '

f_man_names = open('man_names.txt', encoding='utf8')
f_man_lastnames = open('man_lastnames.txt', encoding='utf8')
f_man_surnames = open('man_surnames.txt', encoding='utf8')

man_names = create_array_from_file(f_man_names)
man_surnames = create_array_from_file(f_man_surnames)
man_lastnames = create_array_from_file(f_man_lastnames)


f_woman_names = open('woman_names.txt', encoding='utf8')
f_woman_lastnames = open('woman_lastnames.txt', encoding='utf8')
f_woman_surnames = open('woman_surnames.txt', encoding='utf8')

woman_names = create_array_from_file(f_woman_names)
woman_surnames = create_array_from_file(f_woman_surnames)
woman_lastnames = create_array_from_file(f_woman_lastnames)

f_departaments = open('departaments.txt', encoding='utf8')

departaments = create_array_from_file(f_departaments)

def generate_student_records(n):
    record = ''
    for i in range(0, n):
        record += '(' + str(i + 1) + ', '
        if rd.randint(1, 100) > 50:
            sex = 'м'
            record += generate_name_surname_lastname_string(man_names, man_surnames, man_lastnames)
        else:
            sex = 'ж'
            record += generate_name_surname_lastname_string(woman_names, woman_surnames, woman_lastnames)
        record += str(rd.randint(16, 26)) + ', '
        record += '\'' + departaments[rd.randint(0, len(departaments) - 1)] + '\'' + ', '
        record += '\'' + sex + '\'' + '),\n'
    return record

def generate_teacher_records(n):
    record = ''
    for i in range(0, n):
        record += '(' + str(i + 1) + ', '
        if rd.randint(1, 100) > 50:
            sex = 'м'
            record += generate_name_surname_lastname_string(man_names, man_surnames, man_lastnames)
        else:
            sex = 'ж'
            record += generate_name_surname_lastname_string(woman_names, woman_surnames, woman_lastnames)
        age = rd.randint(25, 80)
        record += str(age) + ', '
        record += '\'' + departaments[rd.randint(0, len(departaments) - 1)] + '\'' + ', '
        degrees = ['магистрант', 'аспирант', 'кандидат наук', 'доктор наук']
        if (age > 28):
            record +=  '\'' + degrees[rd.randint(2, len(degrees) - 1)] + '\'' + ', '
        else:
            record += '\'' + degrees[rd.randint(0, 3)] + '\'' + ', '
        record += '\'' + sex + '\'' + '),\n'
    return record

'''
records = generate_teacher_records(10)

for record in records:
    print(record)
'''