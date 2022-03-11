DROP VIEW IF EXISTS students_new;

CREATE VIEW students_new AS
SELECT *
FROM STUDENTS
WHERE id < 15;

CREATE OR REPLACE FUNCTION del_students_soft_func()
RETURNS TRIGGER
AS $$
old_id = TD["old"]["id"]
res = plpy.execute(f" \
UPDATE students_new\
SET\
name = \'none\',\
surname = \'none\',\
lastname = \'none\',\
age = NULL,\
departament = \'none\',\
sex = \'none\'\
WHERE students_new.id = {old_id}")
return TD["new"]
$$ LANGUAGE plpython3u;

CREATE TRIGGER del_students_soft_trigger
INSTEAD OF DELETE ON students_new
FOR EACH ROW
EXECUTE PROCEDURE del_students_soft_func();