from ui import *
from commands_back import *

commands = CommandsBack()
user_input = ''

if __name__ == "__main__":
    print_greetings()
    while user_input != 'exit':
        user_input = input('Enter command: ')
        command = user_input.split(' ')

        if command[0] == 'help':
            print_help()
        if command[0] == 'scalar':
            if len(command) == 3:
                commands.get_scalar_with_limit(command[1], command[2])
            elif len(command) == 2:
                commands.get_scalar_with_limit(command[1])
            else:
                print('Error, incorrect command!')
                
        if command[0] == 'join':
            if len(command) == 3:
                commands.get_joined_register_with_limit(command[1], command[2])
            elif len(command) == 2:
                commands.get_joined_register_with_limit(command[1])
            else:
                print('Error, incorrect command!')

        #CTE + WITH AS
        if command[0] == 'avg_age':
            if len(command) == 2:
                commands.get_cte_with(command[1])
            else:
                print('Error, incorrect command!')

        if command[0] == 'table_names':
            if len(command) == 1:
                commands.get_table_names()
            else:
                print('Error, incorrect command!')

        if command[0] == 'get_vol_stud':
            if len(command) == 2:
                commands.get_student_step_volume(int(command[1]))
            else:
                print('Error, incorrect command!')

        if command[0] == 'col_types':
            if len(command) == 2:
                commands.get_meta_for_table(command[1])
            else:
                print('Error, incorrect command!')

        if command[0] == 'test_get_query':
            if len(command) == 1:
                commands.get_curr_query()
            else:
                print('Error, incorrect command!')

        if command[0] == 'create_stair_repair':
            if len(command) == 1:
                commands.create_stair_repair_table()
            else:
                print('Error, incorrect command!')

        if command[0] == 'insert_into_stair_repair':
            if len(command) == 3:
                commands.insert_into_stair_repair(command[1], command[2])
            else:
                print('Error, incorrect command!')