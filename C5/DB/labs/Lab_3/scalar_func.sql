CREATE OR REPLACE FUNCTION public.getVolumeSumForStudent_lab_3(
    student_id INT
)
RETURNS NUMERIC AS $$
DECLARE
	volume NUMERIC;
BEGIN
    SELECT SUM(height * width * len) AS vol INTO volume
    FROM ((
		SELECT * 
		FROM students JOIN student_stair_register ON students.id = student_stair_register.student
		WHERE students.id = student_id
		) AS STUDENT_STAIR_MATCH JOIN STAIRS ON STAIRS.id = STUDENT_STAIR_MATCH.stair) AS SSM_JOINED;
    RETURN volume;
END;
$$ LANGUAGE plpgsql