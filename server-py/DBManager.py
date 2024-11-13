import json
import sqlite3
from AppObject import AppObject

class DBManager(AppObject):
    def __init__(self, dbname, initsqlfile):
        self.conn = sqlite3.connect(dbname)
        self.cursor = self.conn.cursor()
        with open(initsqlfile, 'r') as f:
            initsql = f.read()
            self.cursor.executescript(initsql)

    def getDevice(self, snNumber, createIfNotExists=False):
        if createIfNotExists:
            try:
                self.cursor.execute("INSERT INTO Device (serialNumber) VALUES (?)", [snNumber])
                self.conn.commit()
            except:
                pass
        res = self.cursor.execute("SELECT * FROM Device WHERE serialNumber = (?)", [snNumber]).fetchall()
        return res[0]
        
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

    def registerMeasure(self, devID, data, time):
        self.cursor.execute("INSERT INTO Mesure (device_id, measure_timestamp, data) VALUES (?, ?, ?)", [devID, time, json.dumps(data)])
        self.conn.commit()
        
    def getDevices(self):
        #TODO decoment when test ends and return devices
        self.cursor.execute("SELECT serialNumber FROM device")
        devices = self.cursor.fetchall()
    
        return json.dumps(devices)
    
    def getMeasures(self, device_id):
        self.cursor.execute("SELECT data, measure_timestamp FROM measure JOIN device WHERE device = (?)", (device_id))
        measure = self.cursor.fetchall()

        return json.dumps(measure)

    def getMeasure(self, device_id):
        self.cursor.execute("SELECT data, measure_timestamp FROM measure JOIN device WHERE device = (?) ORDER BY measure_timestamp DESC LIMIT 1", (device_id))
        measure = self.cursor.fetchall()
        return json.dumps(measure)

    def setOrder(self, device_id, order):
        self.cursor.execute("UPDATE Device SET displayorder = (?) WHERE id = (?)", (order, device_id))
        self.conn.commit()


