from os import write


def generate_file(fname, input_file):
    f_input = open(input_file, 'r', encoding='utf8')
    f_out = open(fname, 'w', encoding='utf8')
    for line in f_input:
        new_line = line
        new_line = new_line.replace(', ', ',')
        new_line = new_line.replace(',\n', '\n')
        new_line = new_line.replace('(', '')
        new_line = new_line.replace(')', '')
        f_out.write(new_line)

generate_file('data_students_copy.txt', 'insert_data_files\data_students.txt')
generate_file('data_teachers_copy.txt', 'insert_data_files\data_teachers.txt')
generate_file('data_stairs_copy.txt', 'insert_data_files\data_stairs.txt')
generate_file('data_students_register_copy.txt', 'insert_data_files\data_records_students.txt')
generate_file('data_teachers_register_copy.txt', 'insert_data_files\data_records_teachers.txt')