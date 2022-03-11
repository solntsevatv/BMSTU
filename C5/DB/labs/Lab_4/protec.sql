CREATE OR REPLACE FUNCTION find_all_students_by_stair_id(stair_id INT)
RETURNS TABLE(
	student_id INT
)
AS $$		
	res = plpy.execute(f"\
			SELECT SSRS.student\
            FROM (\
                SELECT * FROM STUDENT_STAIR_REGISTER\
                JOIN\
                STUDENTS\
                ON STUDENTS.id = STUDENT_STAIR_REGISTER.student\
                ) AS SSRS\
            WHERE SSRS.stair = {stair_id};")
					   
	if res:
		for elem in res:
			yield elem['student']
		
$$ LANGUAGE plpython3u;