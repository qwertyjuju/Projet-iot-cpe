CREATE TABLE Device (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT
);

CREATE TABLE data (
    id INTEGER PRIMARY KEY AUTOINCREMENT,  
    data TEXT NOT NULL,                    
    device_id INTEGER NOT NULL,            
    FOREIGN KEY (device_id) REFERENCES device(id) 
);