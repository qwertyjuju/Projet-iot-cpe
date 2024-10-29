import sqlite3
from AppObject import AppObject

class DBManager(AppObject):
    def __init__(self, dbname):
        self.conn = sqlite3.connect(dbname)
        self.cursor = self.conn.cursor()

    def store_data_in_db(self, data):
        try:
            # Extraire les informations spécifiques
            opcode = data["opcode"]
            id_source = data["id_source"]
            data_capteur = data["data_capteur"]
            if opcode == 0:
                if id_source:
                    self.cursor.execute("INSERT OR IGNORE INTO device (id_source) VALUES (?)", (id_source,))
                    self.conn.commit()
                if opcode and id_source and data_capteur:
                    self.cursor.execute("INSERT INTO data (opcode, id_source, data_capteur) VALUES (?, ?, ?)",(opcode, id_source, data_capteur))
                    self.conn.commit()
                    print("Data successfully stored in database.")
                else:
                    print("Some fields are missing in the received JSON data.")
        except sqlite3.Error as e:
            print("Error storing data:", e)
        
    def getDevices (self):
        self.cursor.execute("SELECT * FROM device")
        devices = self.cursor.fetchall()
        print(devices)
        devices = ["678", "123", "bite"]
        return devices