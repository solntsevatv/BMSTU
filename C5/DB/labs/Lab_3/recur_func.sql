CREATE OR REPLACE FUNCTION student_step_count_lab_3(student_id BIGINT, step_count BIGINT)
RETURNS TABLE (step_count_res BIGINT)
AS
$$
BEGIN
	RETURN QUERY
	SELECT step_count;
	IF (SELECT count(*)
	FROM student_stair_register
	WHERE student_id = student) < (SELECT count(*) FROM student_stair_register) 
	AND
	student_id <= 100
	THEN
		RETURN QUERY
			SELECT *
			FROM student_step_count_lab_3(
				student_id + 1, 
				(SELECT count(*)
				FROM student_stair_register
				WHERE student_id = student) + step_count);
	END IF;
END
$$ LANGUAGE plpgsql;