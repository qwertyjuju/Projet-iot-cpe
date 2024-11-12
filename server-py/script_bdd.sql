CREATE TABLE IF NOT EXISTS Device (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    serialNumber TEXT NOT NULL UNIQUE,
    displayorder TEXT NOT NULL DEFAULT "LTH"
);


CREATE TABLE IF NOT EXISTS Mesure (
    id INTEGER PRIMARY KEY AUTOINCREMENT,  
    data TEXT NOT NULL,
    measure_timestamp DATETIME NOT NULL,
    device_id INTEGER NOT NULL,
        FOREIGN KEY (device_id) REFERENCES Device(id)
);

UPDATE SQLITE_SEQUENCE SET seq = 1 WHERE name = 'Device'
