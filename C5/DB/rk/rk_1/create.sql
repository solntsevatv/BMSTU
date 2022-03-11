CREATE TABLE IF NOT EXISTS Drivers (
	DriverID numeric primary key,
	DriverLicense text,
	FIO text,
	Phone text
);

CREATE TABLE IF NOT EXISTS Cars (
	CarID text primary key,
	Model text,
	Color text,
	Year numeric,
	FineDate date
);

CREATE TABLE IF NOT EXISTS Fine (
	FineID numeric primary key,
	FineType text,
	Amount numeric,
	FineDate date,
	DriverID numeric,
	FOREIGN KEY (DriverID) REFERENCES Drivers(DriverID)
);

CREATE TABLE IF NOT EXISTS DC (
	CarID text,
	DriverID numeric,
	FOREIGN KEY (CarID) REFERENCES Cars (CarID),
	FOREIGN KEY (DriverID) REFERENCES Drivers (DriverID)
);