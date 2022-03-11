CREATE OR REPLACE FUNCTION stair_status_dep_lab_4(dep TEXT)
RETURNS TABLE(
	stair_id INT,
	status TEXT
)
AS $$
	def define_stair_status(stair):
		if stair['step_num'] > 1500:
			return stair['id'], 'need repairs'
		if stair['step_num'] > 1000:
			return stair['id'], 'worn'
		if stair['step_num'] > 500:
			return stair['id'], 'normal'
		return stair['id'], 'new'
			
	res = plpy.execute(f"\
			SELECT *\
			FROM (SELECT *\
			FROM STUDENT_STAIR_REGISTER\
			JOIN STUDENTS\
			ON STUDENTS.id = student\
			) AS stair_by_dep\
			JOIN STAIRS\
			ON STAIRS.id = stair\
			WHERE departament = '{dep}';")
					   
	if res:
		for elem in res:
			yield (define_stair_status(elem))
		
$$ LANGUAGE plpython3u;