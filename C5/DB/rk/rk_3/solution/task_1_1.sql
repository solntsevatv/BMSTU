CREATE OR REPLACE FUNCTION didnt_bother_to_come_today(today DATE)
RETURNS TABLE 
(
	FIO TEXT,
	departament TEXT
)
AS $$
BEGIN
RETURN QUERY
SELECT employee.fio, employee.departament
FROM employee
WHERE id NOT IN (SELECT DISTINCT emp_id
FROM employee_register
WHERE enter_date = today);
END;
$$ LANGUAGE plpgsql