SELECT row_to_json(students)
FROM students;

SELECT array_to_json(array_agg(row_to_json(students)))
FROM students;