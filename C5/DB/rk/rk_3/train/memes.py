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
















from peewee import *
from datetime import *

# Подключаемся к нашей БД.
con = PostgresqlDatabase(
	database='postgres',
	user='lis',
	password='password',
	host='127.0.0.1',
	port=5432
)


class BaseModel(Model):
	class Meta:
		database = con

class Employee(BaseModel):
	id = IntegerField(column_name='id')
	name = CharField(column_name='name')
	surname = CharField(column_name='surname')
	date_of_birth = DateField(column_name='date_of_birth')
	department = CharField(column_name='department')

	class Meta:
		table_name = 'employee'



class EmployeeVisit(BaseModel):
	id = IntegerField(column_name='id')	
	employee_id = ForeignKeyField(Employee, backref='employee_id')
	employee_data = DateField(column_name='employee_data')
	day_of_week =  CharField(column_name='day_of_week')
	employee_time = TimeField(column_name='employee_time')
	e_type = IntegerField(column_name='type')	

	class Meta:
		table_name = 'employee_visit'




def output(cur):
	rows = cur.fetchall()
	for elem in rows:
		print(*elem)
	print()

def task_2():
	global con

	cur = con.cursor()

	cur.execute(TASK_2_1)
	output(cur)

	cur.execute(TASK_2_2)
	print(*cur.fetchone(), "\n")

	cur.execute(TASK_2_3)
	output(cur)

	cur.close()

def print_query(query):
	for elem in query.dicts().execute():
		print(elem)
		# print(elem['employee_data'].isocalendar()[1] )

def task_2_orm():
	# 1.
	print("Отделы, в которых сотрудники опаздывают более 2х раз в неделю")
	query = Employee.select(Employee.department).join(EmployeeVisit).where(EmployeeVisit.employee_time > '09:00:00').where(EmployeeVisit.e_type==1).group_by(Employee.department).having(fn.Count(Employee.id) > 2)
	#, on=(EmployeeVisit.employee_id==Employee.id))
	print(query) 
	print_query(query)
	 
	# 2.
	print("\nНайти средний возраст сотрудников, не находящихся на рабочем месте 8 часов в неделю.")
	print(datetime.now())
	# datetime.datetime.now().year - Employee.date_of_birth.year
	# Это средний возраст сотрудников.
	query = Employee.select(fn.AVG(datetime.now().year - Employee.date_of_birth.year))
	print_query(query)
	
	# # Это сотрудники, которые находятся на рабочем месте менее 8 часов.
	sql_max = fn.Max(EmployeeVisit.employee_time)
	sql_min = fn.Min(EmployeeVisit.employee_time)
	query = Employee.select(
			EmployeeVisit.employee_data, EmployeeVisit.employee_id, 
			(sql_max - sql_min).alias("cnt")).join(EmployeeVisit).group_by(
			EmployeeVisit.employee_data, EmployeeVisit.employee_id).order_by(EmployeeVisit.employee_id).having(
				sql_max - sql_min > timedelta(hours=8))
	
	# А это недели.
	# res = query.dicts().execute()
	# for elem in res:
	# 	elem['week'] = elem['employee_data'].isocalendar()[1]
	# 	print(elem['employee_data'].isocalendar()[1])

	# query = Employee.select(EmployeeVisit.employee_data).join(EmployeeVisit).group_by(EmployeeVisit.employee_data)
	tmp = Employee.select(
			EmployeeVisit.employee_id).join(EmployeeVisit).group_by(
			EmployeeVisit.employee_data, EmployeeVisit.employee_id).order_by(EmployeeVisit.employee_id).having(
				sql_max - sql_min > timedelta(hours=8))
	query = Employee.select(fn.AVG(datetime.now().year - Employee.date_of_birth.year))#.where(Employee.id << tmp.employee_id)
	
	print_query(tmp)

	# 3.
	print("\nВсе отделы и кол-во сотрудников хоть раз опоздавших за всю историю учета.")
	query = Employee.select(Employee.department, fn.Count(Employee.id)).join(EmployeeVisit).where(
		EmployeeVisit.employee_time > '09:00:00').where(EmployeeVisit.e_type==1).group_by(Employee.department)

	print_query(query)



def main():
	task_2()
	task_2_orm()

if __name__ == "__main__":
	main()

con.close()












import os
import psycopg2
from dotenv import load_dotenv
from tabulate import tabulate
from py_linq import Enumerable

load_dotenv('/root/bmstu-db/.env')
con = psycopg2.connect(
    dbname = 'rk3',
    user = os.getenv("PG_USER"),
    host = os.getenv("PG_HOST"),
    password = os.getenv("PG_PASSWORD")
)

# Найти все отделы, в которых работает более 10 сотрудников (SQL)
def task_1_sql():
    cur = con.cursor()
    try:
        cur.execute('''
            select department from employee
            group by department
            having count(id) > 10;
        ''')
        headers = [desc[0] for desc in cur.description]
        print(tabulate(cur.fetchall(), headers = headers))
        
        con.commit()
        cur.close()
    except:
        con.rollback()

# Найти все отделы, в которых работает более 10 сотрудников (LINQ)
def task_1_linq():
    cur = con.cursor()
    try:
        cur.execute('''
            select * from employee;
        ''')

        emp = Enumerable(cur.fetchall())
        con.commit()
        cur.close()

        deps = (
            emp.group_by(key_names=['department'], key = lambda t: t[3])
        ).select(
            lambda c: {'department': c.key.department, 'count':c.count()}
        ).where(
            lambda f: f['count'] > 10
        ).to_list()

        print(deps)
        
    except:
        con.rollback()


# Найти сотрудников, которые не выходят с рабочего места в течение всего рабочего дня (SQL)
def task_2_sql():
    cur = con.cursor()
    try:
        cur.execute('''
            select id, name, department from employee
            where id not in (
                select id_emp from (
                    select id_emp, visit_type, count(*) from visits
                    group by id_emp, visit_type
                    having visit_type = 2 and count(*) > 1
                ) as not_exitors
            )
        ''')
        headers = [desc[0] for desc in cur.description]
        print(tabulate(cur.fetchall(), headers = headers))
        
        con.commit()
        cur.close()
    except:
        con.rollback()

# Найти сотрудников, которые не выходят с рабочего места в течение всего рабочего дня (LINQ)
def task_2_linq():
    cur = con.cursor()
    try:
        cur.execute('''
            select * from visits;
        ''')

        visits = Enumerable(cur.fetchall())
        con.commit()
        cur.close()

        non_exitors = (
            visits.group_by(key_names=['id_emp', 'visit_type'], key=lambda t: (t[0], t[4]))
        ).select(
            lambda a: {'visit_type':a.key.visit_type, 'id_emp':a.key.id_emp, 'count':a.count()}
        ).where (
            lambda r: r['visit_type'] == 2 and r['count'] > 1
        ).to_list()
            
        print(non_exitors)
        
    except:
        con.rollback()

# Найти все отделы, в которых есть сотрудники, опоздавшие в определенную дату (SQL)
def task_3_sql():
    cur = con.cursor()
    date = input('Input date > ')
    try:
        query = '''
            set datestyle to SQL,dmy;
            set datestyle = dmy;
            select distinct department from employee
            where id in (
                select id_emp from (
                    select id_emp, min(visit_time) from visits
                    where visit_type = 1 and visit_date = date (%s)
                    group by id_emp
                    having min(visit_time) > '9:00'::time
                ) as res
            );
        '''
        cur.execute(query, (date, ))
        headers = [desc[0] for desc in cur.description]
        print(tabulate(cur.fetchall(), headers = headers))
        
        con.commit()
        cur.close()
    except:
        con.rollback()

# Найти все отделы, в которых есть сотрудники, опоздавшие в определенную дату (LINQ)
def task_3_linq():
    cur = con.cursor()
    date = input('Input date > ')
    try:
        cur.execute('''
            select * from visits;
        ''')

        visits = Enumerable(cur.fetchall())
        con.commit()
        cur.close()

        cur = con.cursor()
        cur.execute('''
            select * from employee;
        ''')

        emp = Enumerable(cur.fetchall())
        con.commit()
        cur.close()

        laters = (
            visits.group_by(key_names=['id_emp', 'visit_date', 'visit_time', 'visit_type'], key=lambda t: (t[0], str(t[1]), str(t[3]), t[4]))
        ).select(
            lambda a: {'id_emp':a.key.id_emp, 'visit_date':a.key.visit_date, 'visit_time':a.key.visit_time, 'visit_type':a.key.visit_type}
        ).where(
            lambda r: r['visit_type'] == 1 and r['visit_date'] == date and r['visit_time'] > '9:00'
        ).to_list()

        laters = [l['id'] for l in laters]

        deps = (
            emp.group_by(key_names=['id', 'department'], key=lambda t: (t[0], t[3]))
        ).select(
            lambda a: {'id':a.key.id, 'department':a.key.department}
        ).where(
            lambda a: a['id'] in laters
        ).to_list()
        print(deps)
        
    except:
        con.rollback()

def print_menu():
    print("\n\
1.  Найти все отделы, в которых работает более 10 сотрудников (SQL) \n\
2.  Найти все отделы, в которых работает более 10 сотрудников (LINQ) \n\
3.  Найти сотрудников, которые не выходят с рабочего места в течение всего рабочего дня (SQL) \n\
4.  Найти сотрудников, которые не выходят с рабочего места в течение всего рабочего дня (LINQ) \n\
5.  Найти все отделы, в которых есть сотрудники, опоздавшие в определенную дату (SQL) \n\
6.  Найти все отделы, в которых есть сотрудники, опоздавшие в определенную дату (LINQ) \n\
7. Завершить работу\n"
    )

execute = [
    '__empty__',

    task_1_sql, task_1_linq,
    task_2_sql, task_2_linq,
    task_3_sql, task_3_linq,
    
    lambda: print('Bye!'),
]
__exit = len(execute) - 1

if __name__ == '__main__':
    choice = -1
    while choice != __exit:
        print_menu()
        choice = int(input('> '))
        execute[choice]()