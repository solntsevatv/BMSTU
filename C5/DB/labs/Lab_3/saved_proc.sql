CREATE OR REPLACE PROCEDURE INSERT_STEP_LAB_3
(
	student_id INT,
	stair_id INT,
	entry_date TEXT,
	entry_time TEXT
)
AS
$$
BEGIN
	INSERT INTO student_stair_register
	VALUES (
		(SELECT count(*) FROM student_stair_register) + 1,
		stair_id,
		student_id,
		entry_date,
		entry_time
	);
END;
$$ LANGUAGE plpgsql;