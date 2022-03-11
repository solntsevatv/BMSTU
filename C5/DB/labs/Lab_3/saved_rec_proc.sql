CREATE OR REPLACE PROCEDURE SEARCH_SUB_STUD_LAB_3
(
	age_curr INT,
	dep TEXT,
	sex_s TEXT,
	step INT
)
AS
$$
BEGIN
	IF (SELECT count(*) FROM STUDENTS WHERE age = age_curr AND dep = departament and sex_s = sex) > 0 THEN
		CALL SEARCH_SUB_STUD_LAB_3(age_curr + step, dep, sex_s, step);
		RAISE NOTICE 'age_curr = %, stud_count = %', age_curr, (SELECT count(*) FROM STUDENTS WHERE age = age_curr AND dep = departament and sex_s = sex);
	END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE PROCEDURE SEARCH_STUD_LAB_3
(
	age_curr INT,
	dep TEXT,
	sex_s TEXT
)
AS
$$
BEGIN
	CALL SEARCH_SUB_STUD_LAB_3(age_curr + 1, dep, sex_s, 1);
	RAISE NOTICE 'age_curr = %, stud_count = %', age_curr, (SELECT count(*) FROM STUDENTS WHERE age = age_curr AND dep = departament and sex_s = sex);
	CALL SEARCH_SUB_STUD_LAB_3(age_curr - 1, dep, sex_s, -1);
END;
$$ LANGUAGE plpgsql;