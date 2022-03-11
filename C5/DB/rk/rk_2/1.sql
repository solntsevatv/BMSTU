--Создание таблицы флористов
CREATE TABLE IF NOT EXISTS florists
(
	id INT primary key,
 	fio text,
 	pass_num numeric,
	phone_num text
);

--Создание таблицы покупателей
CREATE TABLE IF NOT EXISTS buyers
(
	id INT primary key,
 	fio text,
 	birthday text,
	city text,
	phone_num text
);

--Создание таблицы букетов
CREATE TABLE IF NOT EXISTS bouquets
(
	id INT primary key,
 	author INT,
 	title text,
	FOREIGN KEY (author) REFERENCES florists (id)
);

--Создание связочной таблицы для букетов и флористов
CREATE TABLE IF NOT EXISTS florist_buyers
(
	id INT primary key,
	florist INT,
	buyer INT,
	FOREIGN KEY (florist) REFERENCES florists (id),
	FOREIGN KEY (buyer) REFERENCES buyers (id)
);

INSERT INTO florists VALUES 
(1, 'D.F.G', 5674, '88004445343'),
(2, 'F.N.D', 2343, '88000989834'),
(3, 'Y.E.S', 5234, '88012340903'),
(4, 'F.D.W', 2454, '88935749587'),
(5, 'T.D.Q', 5534, '88234235245'),
(6, 'L.D.S', 5342, '89004234234'),
(7, 'T.B.D', 2452, '89002342343'),
(8, 'G.D.P', 4675, '89345362445'),
(9, 'V.T.E', 8676, '88456456456'),
(10, 'D.M.G', 2340, '88745644556');

INSERT INTO bouquets VALUES 
(1, 1, 'Ромашки_1'),
(2, 1, 'Ромашки_2'),
(3, 2, 'Ромашки_3'),
(4, 3, 'Ромашки_4'),
(5, 4, 'Ромашки_5'),
(6, 4, 'Ромашки_6'),
(7, 5, 'Ромашки_7'),
(8, 5, 'Ромашки_8'),
(9, 5, 'Ромашки_9'),
(10, 6, 'Ромашки_10'),
(11, 7, 'Ромашки_11'),
(12, 8, 'Ромашки_12'),
(13, 8, 'Ромашки_13'),
(14, 9, 'Ромашки_14'),
(15, 10, 'Ромашки_15');

INSERT INTO buyers VALUES 
(1, 'd.g.r', '01.10.1993', 'Moscow', '83634675356'),
(2, 'y.f.s', '10.11.1953', 'Moscow', '83634345356'),
(3, 'y.f.n', '26.09.1991', 'Samara', '83345343456'),
(4, 'y.n.s', '21.12.1993', 'Samara', '83634673454'),
(5, 'i.e.d', '12.09.1995', 'New York', '83634345543'),
(6, 'u.n.w', '15.01.1998', 'New York', '83634656765'),
(7, 'u.n.u', '05.02.1981', 'Kazan', '83634678686'),
(8, 'b.s.q', '07.04.1989', 'Kazan', '83634467588'),
(9, 'u.n.s', '21.08.1991', 'Kazan', '83634567765'),
(10, 'i.r.s', '27.11.1990', 'Novgorod', '83634675675');

INSERT INTO florist_buyers VALUES 
(1, 1, 9),
(2, 1, 8),
(3, 2, 7),
(4, 2, 7),
(5, 3, 8),
(6, 4, 2),
(7, 5, 3),
(8, 6, 4),
(9, 6, 1),
(10, 7, 5),
(11, 8, 6),
(12, 8, 7),
(13, 9, 5),
(14, 10, 8),
(15, 10, 1);