CREATE OR REPLACE VIEW student_stair_register_new AS
SELECT *
FROM student_stair_register;

CREATE OR REPLACE FUNCTION update_student_stair_register_func_lab_3()
RETURNS TRIGGER
AS 
$$
BEGIN
	DELETE FROM student_stair_register_new
	WHERE id = new.id;
	RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER update_student_stair_register_trigger_lab_3
INSTEAD OF UPDATE ON student_stair_register_new
FOR EACH ROW
EXECUTE PROCEDURE update_student_stair_register_func_lab_3();