DROP TABLE IF EXISTS users_import;
CREATE TEMP TABLE IF NOT EXISTS users_import(doc json);

COPY users_import FROM '/labs/lab_5/students.json';

DROP TABLE IF EXISTS divide_test;
CREATE TEMP TABLE divide_test AS (SELECT doc::json FROM users_import AS test);

SELECT doc::json->0 FROM divide_test;

SELECT json_build_object('student_id', test.doc::json->0->'id'), json_build_object('student_name', test.doc::json->0->'name')
FROM divide_test test;