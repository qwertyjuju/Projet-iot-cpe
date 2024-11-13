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
        self.cursor.execute("SELECT serialNumber FROM Device")
        result = self.cursor.fetchall()
    
        args = [row[0] for row in result]
        command = {"cmd":"set-devices","args":args}

        return json.dumps(command)
    
    def getMeasures(self, device_id):
        self.cursor.execute(f"SELECT data, measure_timestamp FROM mesure JOIN Device WHERE serialNumber = {device_id}")
        result = self.cursor.fetchall()

        measures = [row[0] for row in result]

        args =[{"device_id":device_id, "measures":measures}]
        command = {"cmd":"set-measures","args":args}

        return json.dumps(command)

    def getMeasure(self, device_id):
        self.cursor.execute(f"SELECT data, measure_timestamp FROM mesure JOIN Device WHERE serialNumber = {device_id} ORDER BY measure_timestamp DESC LIMIT 1")
        result = self.cursor.fetchall()
        print(result)
        print(type(result))

        args = [{"device_id":device_id, "last_measure":json.loads(result[0])} for result in result]
        print(args)
        command = {"cmd":"set-measure","args":args}

        return json.dumps(command)

    def setOrder(self, device_id, order):
        self.cursor.execute(f"UPDATE Device SET displayorder = {order} WHERE id = {device_id}")
        self.conn.commit()

