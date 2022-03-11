CREATE TYPE staircase_params AS
(
    staircase_id INT,
    stair_count INT
);

CREATE OR REPLACE FUNCTION get_staircase_params(staircase_id INT)
RETURNS staircase_params
AS
$$
query = plpy.prepare(f"\
    SELECT stairs.staircase_id, count(stairs.staircase_id)\
    FROM STAIRS\
    WHERE stairs.staircase_id = {staircase_id}\
	GROUP BY stairs.staircase_id;",
    ["VARCHAR"])

res = plpy.execute(query, [staircase_id])

if res.nrows():
    return (res[0]["staircase_id"], res[0]["count"])
$$ LANGUAGE plpython3u;