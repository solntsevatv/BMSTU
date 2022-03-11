from prettytable import PrettyTable
import prettytable

def print_greetings():
    print(
    '''
    ==========|SMART STAIRS|==========
    To get info about commands type "help" into input field.
    '''
    )

def print_help():
    print(
    '''
    HELP:
    scalar [table_name] [limit] - gets table by name from data base and displays 'limit' number of rows.
    join [students/teachers] [limit] - get joined information about students or teachers and displays 'limit' number of rows.
    avg_age [students/teachers] - get average age of students or teachers.
    table_names - get table names.
    get_vol_stud [student_id] - get stepped stair volume for student by student_id.
    col_types [table_name] - get column type for each column of the table.
    test_get_query - get syntax for exetuted query.
    create_stair_repair - create table for stair repair register.
    insert_into_stair_repair [id, repair_crew_id] - inserts values intp stair repair register.
    exit - end programm.
    '''
    )

def print_table(th, td):
    table = PrettyTable(th)
    for row in td:
        table.add_row(row)
    print(table)