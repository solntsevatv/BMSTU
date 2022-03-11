import prettytable
import psycopg2 as psy
import ui as u

class CommandsBack:
    def __init__(self) -> None:
        self.conn = psy.connect(
            host="localhost",
            database="smart_stairs",
            user="postgres",
            password="qaz")    
    
    def get_scalar_with_limit(self, table_name, limit=10):
        try:
            cur = self.conn.cursor()
            cur.execute("SELECT column_name FROM INFORMATION_SCHEMA.COLUMNS WHERE table_name = '" + table_name + "';")
            cols = [] 
            for row in cur.fetchall():
                cols.append(row[0])

            # execute a statement
            que_str = ''
            for i in range(0, len(cols) - 1):
                que_str += cols[i] + ', '
            que_str += cols[len(cols) - 1]

            cur.execute('SELECT ' + que_str + ' FROM ' + table_name + ' LIMIT ' + str(limit) + ';')
            
            res = cur.fetchall()
            u.print_table(cols, res)

            # close the communication with the PostgreSQL
            cur.close()
        except Exception as e:
            print('Error, exception occured: ', e)
    
    def get_joined_register_with_limit(self, table_name, limit=10):
        try:
            cur = self.conn.cursor()

            if table_name == 'students':
                cur.execute("""
                CREATE OR REPLACE TEMP VIEW student_register_table_joined
                AS
                SELECT *
                FROM (
                    SELECT stud_reg.*, stairs.id as stair_id, staircase_id, step_num, height, len, width
                    FROM (
                        SELECT student_stair_register.*, students.id AS stud_id, surname, name, lastname, age, departament, sex
                        FROM student_stair_register JOIN students ON student_stair_register.student = students.id
                        ) AS stud_reg
                    JOIN stairs ON stud_reg.stair = stairs.id) AS stud_reg_table;
                    
                SELECT * FROM student_register_table_joined
                LIMIT """ + str(limit) + """;
                """)

                res = cur.fetchall()

                cur.execute("SELECT column_name FROM INFORMATION_SCHEMA.COLUMNS WHERE table_name = 'student_register_table_joined';")
                cols = [] 
                for row in cur.fetchall():
                    cols.append(row[0])
                
                u.print_table(cols, res)
                cur.execute("DROP VIEW student_register_table_joined;")

            if table_name == 'teachers':
                cur.execute("""
                CREATE OR REPLACE TEMP VIEW teacher_register_table_joined
                AS
                SELECT *
                FROM (
                    SELECT teach_reg.*, stairs.id as stair_id, staircase_id, step_num, height, len, width
                    FROM (
                        SELECT teacher_stair_register.*, teachers.id AS stud_id, surname, name, lastname, age, departament, sex, degree
                        FROM teacher_stair_register JOIN teachers ON teacher_stair_register.teacher = teachers.id
                        ) AS teach_reg
                    JOIN stairs ON teach_reg.stair = stairs.id) AS teach_reg_table;
                    
                SELECT * FROM teacher_register_table_joined
                LIMIT """ + str(limit) + """;
                """)

                res = cur.fetchall()

                cur.execute("SELECT column_name FROM INFORMATION_SCHEMA.COLUMNS WHERE table_name = 'teacher_register_table_joined';")
                cols = [] 
                for row in cur.fetchall():
                    cols.append(row[0])
                
                u.print_table(cols, res)
                cur.execute("DROP VIEW teacher_register_table_joined;")
            cur.close()
        except Exception as e:
            print('Error, exception occured: ', e)

    def get_cte_with(self, table_name):
        try:
            cur = self.conn.cursor()

            if table_name == 'students':
                cur.execute("""
                WITH IU7_STUDS AS (
                    SELECT STUDENTS.ID, STUDENTS.NAME, STUDENTS.SURNAME, STUDENTS.AGE
                    FROM STUDENTS
                    WHERE STUDENTS.DEPARTAMENT = 'ИУ7'
                )

                SELECT AVG(AGE) AS avg_age
                FROM IU7_STUDS;
                """)

                res = cur.fetchall()

                cols = ['average student age']
                
                u.print_table(cols, res)

            if table_name == 'teachers':
                cur.execute("""
                WITH IU7_TEACHS AS (
                    SELECT TEACHERS.ID, TEACHERS.NAME, TEACHERS.SURNAME, TEACHERS.AGE
                    FROM TEACHERS
                    WHERE TEACHERS.DEPARTAMENT = 'ИУ7'
                )

                SELECT AVG(AGE) AS avg_age
                FROM IU7_TEACHS;
                """)

                res = cur.fetchall()

                cols = ['average teacher age']
                
                u.print_table(cols, res)
            cur.close()
        except Exception as e:
            print('Error on server side, exception occured: ', e)

    def get_table_names(self):
        try:
            cur = self.conn.cursor()

            cur.execute('''
            SELECT table_name
            FROM information_schema.tables
            WHERE table_schema='public'
            AND table_type='BASE TABLE';
                ''')

            res = cur.fetchall()

            cols = ['table names']
            
            u.print_table(cols, res)
        except Exception as e:
            print('Error, exception occured: ', e)
    
    # scalar table func
    def get_student_step_volume(self, student_id):
        try:
            cur = self.conn.cursor()

            cur.execute('''
            SELECT * FROM getVolumeSumForStudent_lab_3(''' + str(student_id) + ''');
                ''')

            res = cur.fetchall()

            cols = ['stepped stair volume for student']
            
            u.print_table(cols, res)
        except Exception as e:
            print('Error, exception occured: ', e)

    # multy oper func
    def get_sort_by_gender(self, dep_name, limit=10):
        try:
            cur = self.conn.cursor()
            cur.execute("""
            CREATE OR REPLACE TEMP VIEW gen_select AS
            SELECT * FROM genderSelectForDepartament_lab_3('""" + dep_name + """');

            SELECT * FROM gen_select LIMIT """ + str(limit) + """;
            """)

            res = cur.fetchall()

            cur.execute("SELECT column_name FROM INFORMATION_SCHEMA.COLUMNS WHERE table_name = 'gen_select';")
            cols = [] 
            for row in cur.fetchall():
                cols.append(row[0])
            
            u.print_table(cols, res)
            cur.execute("DROP VIEW gen_select;")

            # close the communication with the PostgreSQL
            cur.close()
        except Exception as e:
            print('Error, exception occured: ', e)

    def get_meta_for_table(self, table_name):
        try:
            cur = self.conn.cursor()
            cur.execute("""
            CALL metadata_lab_3('""" + table_name + """');
            """)

            res = []
            for notice in self.conn.notices:
                res.append(notice.split(' ')[2:])
            del(res[0][1])
            cols = []
            res_tab = []
            for i in range(0, len(res)):
                for j in range(0, len(res[i])):
                    res[i][j] = res[i][j].replace('\n', '')
                    res[i][j] = res[i][j].replace(',', '')
                cols.append(res[i][0])
                res_tab.append(res[i][1])

            u.print_table(cols, [res_tab])
            cur.close()
        except Exception as e:
            print('Error, exception occured: ', e)
        
    def get_curr_query(self):
        try:
            cur = self.conn.cursor()
            cur.execute("""
            CREATE OR REPLACE TEMP VIEW temp_query AS
            SELECT * FROM current_query();
            SELECT * FROM temp_query;
            """)

            res = cur.fetchall()

            cur.execute("SELECT column_name FROM INFORMATION_SCHEMA.COLUMNS WHERE table_name = 'temp_query';")
            cols = [] 
            for row in cur.fetchall():
                cols.append(row[0])
            
            u.print_table(cols, res)
            cur.execute("DROP VIEW temp_query;")

            # close the communication with the PostgreSQL
            cur.close()
        except Exception as e:
            print('Error, exception occured: ', e)

    def create_stair_repair_table(self):
        cur = self.conn.cursor()
        cur.execute("""
        CREATE TABLE IF NOT EXISTS stair_repair_register(
            stair_id INT primary key,
            repair_crew_id INT
        );
        """)
        cur.close()
    
    def insert_into_stair_repair(self, id, stair_id):
        try:
            cur = self.conn.cursor()
            cur.execute("""
            INSERT INTO stair_repair_register
            VALUES (""" + str(id) + ',' + str(stair_id) + """);
            """)

            cur.execute("SELECT column_name FROM INFORMATION_SCHEMA.COLUMNS WHERE table_name = 'stair_repair_register';")
            cols = [] 
            for row in cur.fetchall():
                cols.append(row[0])

            cur.execute('SELECT * FROM stair_repair_register;')
            
            res = cur.fetchall()
            u.print_table(cols, res)
            
            cur.close()
        except Exception as e:
            print('Error, exception occured: ', e)


if __name__ == '__main__':
    cb = CommandsBack()
    '''
    cb.get_scalar_with_limit('students', 10)
    cb.get_joined_register_with_limit('students', 10)
    cb.get_cte_with('students')
    cb.get_table_names()
    cb.get_student_step_volume(1)
    cb.get_sort_by_gender('ИУ7')
    cb.get_meta_for_table('students')
    cb.get_curr_query()
    cb.create_stair_repair_table()
    cb.insert_into_stair_repair(2, 5)
    '''