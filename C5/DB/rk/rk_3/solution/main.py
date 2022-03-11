from enum import Enum
import psycopg2 as psy
import datetime as dt
from py_linq import Enumerable

class CommandsBack:
    def __init__(self) -> None:
        pass   
    
    def task_1_sql(self, date):
        with psy.connect(
            host="localhost",
            database="RK3",
            user="postgres",
            password="qaz") as conn:

            cur = conn.cursor()
            cur.execute('''
            SELECT DISTINCT emp_id, fio, departament
            FROM (employee_register JOIN employee ON employee.id = employee_register.emp_id) AS emp_joined
            WHERE emp_joined.enter_date = \'''' + date + '''\' AND entry_time > '09:00:00' AND entry_time - '09:00:00' < '00:05:00';
            ''')
            
            res = cur.fetchall()
            for elem in res:
                print(elem)
            cur.close()

    def task_1_linq(self, date):
        with psy.connect(
            host="localhost",
            database="RK3",
            user="postgres",
            password="qaz") as conn:

            cur = conn.cursor()
            cur.execute('''
            SELECT * FROM employee_register;
            ''')
            emp_reg = Enumerable(cur.fetchall())

            cur.execute('''
            SELECT * FROM employee;
            ''')
            emp = Enumerable(cur.fetchall())

            cur.close()
            print(emp)
            emps = emp_reg.join(emp, lambda s_1: s_1[1], lambda s_2: s_2[0], lambda res: res).where(lambda r: r[0][2] == date and r[0][4] < dt.time(9, 0, 0) and r[0][4] - dt.time(9, 0, 0) < dt.time(0, 5, 0))
            print(emps.select(lambda x: [x[1][1], x[1][3]]))

    def task_3_sql(self):
        with psy.connect(
            host="localhost",
            database="RK3",
            user="postgres",
            password="qaz") as conn:

            cur = conn.cursor()
            cur.execute('''
            SELECT DISTINCT emp_id, fio
            FROM (employee_register JOIN employee ON employee.id = employee_register.emp_id) AS emp_joined
            WHERE entry_time < '08:00:00' AND departament = 'Бухгалтерия';
            ''')
            
            res = cur.fetchall()
            for elem in res:
                print(elem)
            cur.close()

if __name__ == '__main__':
    cb = CommandsBack()
    cb.task_1_sql('2021-12-17')
    cb.task_1_linq('2021-12-17')
    cb.task_3_sql()