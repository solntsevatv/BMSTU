CREATE OR REPLACE FUNCTION public.getStudentByID_lab_3(
    student_id INT
)
RETURNS STUDENTS
AS $$
	SELECT *
	FROM STUDENTS
	WHERE id = student_id;
$$
LANGUAGE  sql;