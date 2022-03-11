DROP TABLE IF EXISTS users_import;
CREATE TEMP TABLE IF NOT EXISTS users_import(doc json);

COPY users_import FROM '/labs/lab_5/students.json';

SELECT * FROM users_import;

SELECT tab.* FROM users_import, json_populate_recordset(null::students, doc) as tab;