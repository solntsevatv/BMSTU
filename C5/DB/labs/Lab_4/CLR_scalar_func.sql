CREATE OR REPLACE FUNCTION get_step_count_lab_4(student_id INT)
RETURNS INT
AS $$
res = plpy.execute(f" \
    SELECT count(*) as step_count\
	FROM STUDENT_STAIR_REGISTER\
	WHERE student = {student_id};")
if res:
    return res[0]['step_count']
$$ LANGUAGE plpython3u;