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
        
    def getDevices(self):
        #TODO decoment when test ends and return devices
        #self.cursor.execute("SELECT serialNumber FROM device")
        #devices = self.cursor.fetchall()
    
        return json.dumps({"cmd": "set-devices", "args": ["device_id1", "device_id2", "device_id3"]})
    
    def getMeasures(self, device_id):
        #self.cursor.execute("SELECT data, measure_timestamp FROM measure JOIN device WHERE device = " + device_id)
        #measure = self.cursor.fetchall()
        
        return json.dumps({"cmd": "set-measures", "args": [{"device_id": "device_id1", "measures": [{"temperature": 22.5, "luminosity": 300, "pressure": 1013, "humidity": 45, "datetime": "2024-10-25T15:00:00Z"}, {"temperature": 23.5, "luminosity": 310, "pressure": 1011, "humidity": 35, "datetime": "2024-10-25T15:00:00Z"}]}]})

    def getMeasure(self, device_id):
        #self.cursor.execute("SELECT data, measure_timestamp FROM measure JOIN device WHERE device = " + device_id +" ORDER BY measure_timestamp DESC LIMIT 1")
        #measure = self.cursor.fetchall()
        
        return json.dumps({"cmd": "set-measure", "args": [{"device_id": "device_id1", "last_measure": {"temperature": 22.5, "luminosity": 300, "pressure": 1013, "humidity": 45, "datetime": "2024-10-25T15:00:00Z"}}]})

    def setOrder(self, device_id, order):
        return