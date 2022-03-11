CREATE OR REPLACE PROCEDURE check_print(database_name TEXT)
LANGUAGE plpgsql
AS
$$
DECLARE
check_record record;
BEGIN
	for check_record in (SELECT constraint_name, check_clause 
	FROM INFORMATION_SCHEMA.CHECK_CONSTRAINTS 
	AS constraints_vals
	WHERE check_clause LIKE '%LIKE%' and (SELECT current_database()) == database_name)
	LOOP
	RAISE NOTICE 'Имя ограничения: % , Выражение SQL: %', check_record.constraint_name, check_record.check_clause;
	END LOOP;
END;
$$