import serial 


class SerialServer:
    def __init__(self, port, baudrate):
        self.ser=serial.Serial()
        # ser = serial.Serial(SERIALPORT, BAUDRATE)
        self.ser.port=port
        self.ser.baudrate=baudrate
        self.ser.bytesize = serial.EIGHTBITS #number of bits per bytes
        self.ser.parity = serial.PARITY_NONE #set parity check: no parity
        self.ser.stopbits = serial.STOPBITS_ONE #number of stop bits
        self.ser.timeout = None          #block read
        # ser.timeout = 0             #non-block read
        # ser.timeout = 2              #timeout block read
        self.ser.xonxoff = False     #disable software flow control
        self.ser.rtscts = False     #disable hardware (RTS/CTS) flow control
        self.ser.dsrdtr = False       #disable hardware (DSR/DTR) flow control
        #ser.writeTimeout = 0     #timeout for write

        self.conn = sqlite3.connect('data.db')
        self.cursor = self.conn.cursor()
        print('Starting Up Serial Monitor')
        try:
            self.ser.open()
        except serial.SerialException:
                print("Serial {} port not available".format(port))
                exit()

    def sendUARTMessage(self, msg):
        self.ser.write(msg)
        print("Message <" + msg + "> sent to micro-controller." )

    def run(self):
        while self.ser.isOpen() :
             if (self.ser.inWaiting() > 0):
                    data_str = self.ser.read(self.ser.inWaiting()) 
                    #stocker data dans sqlite
                    try:
                        # Convertir les bytes en JSON
                        json_data = json.loads(data_bytes.decode('utf-8'))
                        print("Received data:", json_data)

                        # Stocker les données dans la base de données
                        self.store_data_in_db(json_data)
                    except (json.JSONDecodeError, UnicodeDecodeError) as e:
                        print("Error decoding JSON:", e)
                    print(data_str)
        
     def store_data_in_db(self, json_data):
        try:
            # Extraire les informations spécifiques
            opcode = json_data.get("opcode")
            id_source = json_data.get("id_source")
            data_capteur = json_data.get("data_capteur")

            if opcode == 0:
                if id_source:
                    self.cursor.execute("INSERT OR IGNORE INTO device (id_source) VALUES (?)", (id_source,))
                    self.conn.commit()

                if opcode and id_source and data_capteur:
                    self.cursor.execute("INSERT INTO data (opcode, id_source, data_capteur) VALUES (?, ?, ?)",
                                        (opcode, id_source, data_capteur))
                    self.conn.commit()
                    print("Data successfully stored in database.")
                else:
                    print("Some fields are missing in the received JSON data.")
            else :
                
        except sqlite3.Error as e:
            print("Error storing data:", e)

    def close(self):
         self.ser.close()
           