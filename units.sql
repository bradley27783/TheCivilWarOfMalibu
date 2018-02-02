CREATE TABLE units(
	UnitID int NOT NULL,
	name varchar(255),
	attack int,
	defence int,
	cost float(8),
	upkeep float(8),
	PRIMARY KEY (ID)
);

CREATE TABLE production(
	ProductionID int NOT NULL,
	name varchar(255),
	profit int,
	cost int
	PRIMARY KEY (ID)
);

--Table for saves
CREATE TABLE save(
	SaveID int NOT NULL,
	saveName varchar(255),

);

--t1 stands for territory 1.
CREATE TABLE territorys(
	terID int NOT NULL
	playerOwn boolean, --True if player owns it

	--Magic parts
	defenceProb int,


	--Unit amounts
	holotank int,
	holobike int,
	holosoldier int,
	holoxcom int,
	--Production amounts
	holofishing int,
	holoplatform int,
	holomine int,
	
	FOREIGN KEY(SaveID) REFERENCES save(SaveID)
	PRIMARY KEY(terID)
);
