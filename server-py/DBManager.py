import json
import sqlite3
from AppObject import AppObject

class DBManager(AppObject):

    """
    classe pour la gestion des données dans la base de données
    """
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
    

    def registerMeasure(self, devID, data, time):
        self.cursor.execute("INSERT INTO Mesure (device_id, measure_timestamp, data) VALUES (?, ?, ?)", [devID, time, json.dumps(data)])
        self.conn.commit()
        
    def getDevices(self):
        self.cursor.execute("SELECT serialNumber FROM Device")
        result = self.cursor.fetchall()
    
        args = [row[0] for row in result]
        command = {"cmd":"set-devices","args":args}

        return json.dumps(command)
    
    def getMeasures(self, device_id):
        self.cursor.execute(f"SELECT data, measure_timestamp FROM mesure JOIN Device WHERE serialNumber = {device_id} ORDER BY measure_timestamp DESC LIMIT 20")
        result = self.cursor.fetchall()
        
        measurements = []
        for measurement_json, timestamp in result:
            measurement_data = json.loads(measurement_json)
            
            measurements.append({"measure": measurement_data,"measure_timestamp": timestamp})

        args = [{"device_id": device_id, "measures": measurements}]
        command = {"cmd":"set-measures","args":args}

        return json.dumps(command)

    def getMeasure(self, device_id):
        self.cursor.execute(f"SELECT data, measure_timestamp FROM mesure JOIN Device WHERE serialNumber = {device_id} ORDER BY measure_timestamp DESC LIMIT 1")
        result = self.cursor.fetchall()

        args = [{"device_id":device_id, "last_measure":json.loads(record[0]), "measure_timestamp":record[1]} for record in result]
        command = {"cmd":"set-measure","args":args}

        return json.dumps(command)

    def setOrder(self, device_id, order):
        self.cursor.execute(f"UPDATE Device SET displayorder = {order} WHERE id = {device_id}")
        self.conn.commit()

