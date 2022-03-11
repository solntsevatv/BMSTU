touch students.json
psql --username=postgres -c "\copy (SELECT array_to_json(array_agg(row_to_json(students))) FROM students) to '/labs/lab_5/students.json'"
-- OR --
docker cli -> psql -U postgres -> \c smart_stairs -> \copy (SELECT array_to_json(array_agg(row_to_json(students))) FROM students) to '/labs/lab_5/students.json';