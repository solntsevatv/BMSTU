CREATE TABLE IF NOT EXISTS STAIRS(
    id int PRIMARY KEY,
    staircase_id int DEFAULT 0,
    step_num int DEFAULT 0,
    height int DEFAULT 15,
    len int DEFAULT 105,
    width int DEFAULT 25
);

CREATE TABLE IF NOT EXISTS STUDENTS(
    id int PRIMARY KEY,
    surname text not null,
    name text not null,
    lastname text not null,
    age int,
    departament text not null,
    sex text not null
);

CREATE TABLE IF NOT EXISTS TEACHERS(
    id int PRIMARY KEY,
    surname text not null,
    name text not null,
    lastname text not null,
    age int,
    departament text not null,
    degree text not null,
    sex text not null
);

CREATE TABLE IF NOT EXISTS STUDENT_STAIR_REGISTER(
    id int PRIMARY KEY,
    stair int not null,
    student int not null,
    FOREIGN KEY (stair) REFERENCES STAIRS (id),
    FOREIGN KEY (student) REFERENCES STUDENTS (id),
    entry_date text not null,
    entry_time text not null
);

CREATE TABLE IF NOT EXISTS TEACHER_STAIR_REGISTER(
    id int PRIMARY KEY,
    stair int not null,
    teacher int not null,
    FOREIGN KEY (stair) REFERENCES STAIRS (id),
    FOREIGN KEY (teacher) REFERENCES TEACHERS (id),
    entry_date text not null,
    entry_time text not null
);