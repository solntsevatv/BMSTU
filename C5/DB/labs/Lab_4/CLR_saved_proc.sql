CREATE OR REPLACE PROCEDURE add_student_lab_4
(
    id INT,
    surname TEXT,
    name TEXT,
    lastname TEXT,
    age INT,
    departament TEXT,
    sex TEXT
) AS $$
insert_plan = plpy.prepare(
    "INSERT INTO STUDENTS VALUES($1, $2, $3, $4, $5, $6, $7)",
     ["INT", "TEXT", "TEXT", "TEXT", "INT", "TEXT", "TEXT"])
res = plpy.execute(insert_plan, [id, surname, name, lastname, age, departament, sex])
$$ LANGUAGE plpython3u;