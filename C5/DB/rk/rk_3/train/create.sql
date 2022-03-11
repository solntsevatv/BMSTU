CREATE TABLE IF NOT EXISTS employee(
	id INT primary key,
	FIO TEXT,
	date_of_birth DATE DEFAULT CURRENT_DATE,
	departament TEXT
);

CREATE TABLE IF NOT EXISTS employee_register(
	id INT primary key,
	emp_id INT,
	foreign key (emp_id) references employee (id),
	enter_date DATE DEFAULT CURRENT_DATE,
	day_of_the_week TEXT,
	entry_time TIME DEFAULT CURRENT_TIME,
	entry_type INT
);