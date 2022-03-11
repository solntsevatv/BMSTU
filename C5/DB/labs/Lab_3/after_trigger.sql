CREATE OR REPLACE FUNCTION update_student_stair_register_id_on_delete_lab_3()
RETURNS TRIGGER
AS
$$
BEGIN
	UPDATE student_stair_register
	SET id = id - 1
	WHERE id > old.id;
	RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER update_student_stair_register_on_delete_lab_3
AFTER DELETE ON student_stair_register
FOR EACH ROW
EXECUTE PROCEDURE update_student_stair_register_id_on_delete_lab_3();