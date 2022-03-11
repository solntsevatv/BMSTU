CREATE OR REPLACE FUNCTION get_stair_square_by_id_lab_4(stair_id INT)
RETURNS NUMERIC
AS $$
res = plpy.execute(f" \
    SELECT height, width\
	FROM STAIRS\
	WHERE id = {stair_id};")
if res:
    return res[0]['height'] * res[0]['width']
$$ LANGUAGE plpython3u;