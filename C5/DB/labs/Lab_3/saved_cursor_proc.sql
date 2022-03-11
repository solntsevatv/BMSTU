CREATE OR REPLACE PROCEDURE steps_for_departament_lab_3(
	dep TEXT
)
AS
$$
DECLARE
search_cursor CURSOR FOR
	SELECT stair, staircase_id, step_num, height, len, width
	FROM
		((
			SELECT *
			FROM student_stair_register 
			JOIN students 
			ON students.id = student_stair_register.student
		) AS student_register
		LEFT JOIN stairs
		ON student_register.stair = stairs.id) AS student_stair_register_unwrapped
		WHERE departament = dep;
tmp stairs;
step_count INT;
BEGIN
	OPEN search_cursor;
	step_count = 0;
	LOOP
		FETCH search_cursor
		INTO tmp;
		EXIT WHEN NOT FOUND;
		step_count = step_count + tmp.step_num;
	END LOOP;
	RAISE NOTICE 'Step num = %', step_count;
	CLOSE search_cursor;
END;
$$ LANGUAGE plpgsql;