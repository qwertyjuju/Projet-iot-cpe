CREATE TABLE Device (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT
);

CREATE TABLE Capteur (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    device_id INTEGER,  
    FOREIGN KEY (device_id) REFERENCES Device(id)
);

CREATE TABLE Mesure (
    id INTEGER PRIMARY KEY AUTOINCREMENT,  
    data TEXT NOT NULL,
    capteur_id INTEGER, 
    FOREIGN KEY (capteur_id) REFERENCES Capteur(id)
)