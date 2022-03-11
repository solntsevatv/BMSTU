DROP TABLE IF EXISTS TEST;
CREATE TEMP TABLE TEST AS (
    SELECT *, to_json(students.age) age_json
    FROM students
);

SELECT * FROM TEST;