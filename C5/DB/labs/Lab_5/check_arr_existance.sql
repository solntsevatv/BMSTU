DROP TABLE IF EXISTS users_import;
CREATE TEMP TABLE IF NOT EXISTS users_import(doc json);

COPY users_import FROM '/labs/lab_5/students.json';

SELECT doc::json->0->'id' IS NOT NULL field_exists FROM users_import;
SELECT doc::json->0->'did' IS NOT NULL field_exists FROM users_import;