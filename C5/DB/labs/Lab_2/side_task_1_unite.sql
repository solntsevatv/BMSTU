with time_union AS (
	SELECT table1.id, var1, var2, GREATEST(table1.valid_from_dttm, table2.valid_from_dttm) AS valid_from_dttm,
	LEAST(table1.valid_to_dttm, table2.valid_to_dttm) AS valid_to_dttm
	FROM table1 JOIN table2 ON table1.id = table2.id
)

SELECT *
FROM time_union
WHERE valid_from_dttm <= valid_to_dttm
ORDER BY valid_from_dttm;