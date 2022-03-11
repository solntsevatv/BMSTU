CREATE TABLE Table1(
	id integer,
	var1 text,
	valid_from_dttm date,
	valid_to_dttm date
);

CREATE TABLE Table2(
	id integer,
	var2 text,
	valid_from_dttm date,
	valid_to_dttm date
);

INSERT INTO table1 VALUES
(1, 'A', '2018-09-01', '2018-09-15'),
(1, 'B', '2018-09-16', '5999-12-31');

INSERT INTO table2 VALUES
(1, 'A', '2018-09-01', '2018-09-18'),
(1, 'B', '2018-09-19', '5999-12-31');