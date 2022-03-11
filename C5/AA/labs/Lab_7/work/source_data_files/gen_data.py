import random as rd

def create_array_from_file(f):
    return [line.replace("\n", "") for line in f]

def generate_name_surname_lastname_string(names, surnames, lastnames):
    return surnames[rd.randint(0, len(surnames) - 1)] + ' '\
            + names[rd.randint(0, len(names) - 1)] + ' '\
            + lastnames[rd.randint(0, len(lastnames) - 1)]

def generate_vals(n):
    f_man_names = open('D:/Storage/Andrew/BMSTU/BMSTU/C5/AA/labs/Lab_7/work/source_data_files/man_names.txt', encoding='utf8')
    f_man_lastnames = open('D:/Storage/Andrew/BMSTU/BMSTU/C5/AA/labs/Lab_7/work/source_data_files/man_lastnames.txt', encoding='utf8')
    f_man_surnames = open('D:/Storage/Andrew/BMSTU/BMSTU/C5/AA/labs/Lab_7/work/source_data_files/man_surnames.txt', encoding='utf8')

    man_names = create_array_from_file(f_man_names)
    man_surnames = create_array_from_file(f_man_surnames)
    man_lastnames = create_array_from_file(f_man_lastnames)


    f_woman_names = open('D:/Storage/Andrew/BMSTU/BMSTU/C5/AA/labs/Lab_7/work/source_data_files/woman_names.txt', encoding='utf8')
    f_woman_lastnames = open('D:/Storage/Andrew/BMSTU/BMSTU/C5/AA/labs/Lab_7/work/source_data_files/woman_lastnames.txt', encoding='utf8')
    f_woman_surnames = open('D:/Storage/Andrew/BMSTU/BMSTU/C5/AA/labs/Lab_7/work/source_data_files/woman_surnames.txt', encoding='utf8')

    woman_names = create_array_from_file(f_woman_names)
    woman_surnames = create_array_from_file(f_woman_surnames)
    woman_lastnames = create_array_from_file(f_woman_lastnames)

    records = dict()
    for i in range(0, n):
        if rd.randint(1, 100) > 50:
            t_name = generate_name_surname_lastname_string(man_names, man_surnames, man_lastnames)
        else:
            t_name = generate_name_surname_lastname_string(woman_names, woman_surnames, woman_lastnames)

        if rd.randint(1, 100) > 50:
            s_name = generate_name_surname_lastname_string(man_names, man_surnames, man_lastnames)
        else:
            s_name = generate_name_surname_lastname_string(woman_names, woman_surnames, woman_lastnames)

        records[s_name] = t_name
    return records

if __name__ == '__main__':
    records = generate_vals(10)
    print(records)
    print(list(records))