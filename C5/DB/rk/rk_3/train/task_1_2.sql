CREATE OR REPLACE FUNCTION late_guyz(late_time TIME)
RETURNS NUMERIC
AS $$
DECLARE
	late NUMERIC;
BEGIN
	SELECT COUNT(*) AS lt INTO late
	FROM employee_register
	WHERE entry_time > late_time AND entry_type = 1;
	RETURN late;
END;
$$ LANGUAGE plpgsql