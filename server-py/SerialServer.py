import serial
import json
from AppObject import AppObject
import threading
import queue

class SerialPacket(AppObject):
    def __init__(self, buffer: bytes):
        self.buffer = buffer
        self.opcode = self.buffer[0]
        if self.opcode ==0:
            pass
        else:
            pass

class SerialServer:
    def __init__(self, port, baudrate):
        self.q = queue.Queue()
        self.ser: serial.Serial =serial.Serial()
        self.ser.port=port
        self.ser.baudrate=baudrate
        self.ser.bytesize = serial.EIGHTBITS #number of bits per bytes
        self.ser.parity = serial.PARITY_NONE #set parity check: no parity
        self.ser.stopbits = serial.STOPBITS_ONE #number of stop bits
        self.ser.timeout = None          #block read
        self.ser.xonxoff = False     #disable software flow control
        self.ser.rtscts = False     #disable hardware (RTS/CTS) flow control
        self.ser.dsrdtr = False       #disable hardware (DSR/DTR) flow control
        print('Starting Up Serial Monitor')
        
        try:
            self.ser.open()
        except serial.SerialException as e:
            print(f"Serial {port} port not available: {e}")
            exit()

    def run(self):
        rthread = threading.Thread(target =self._run_read)
        rthread.daemon = True
        rthread.start()
        wthread = threading.Thread(target= self._run_write)
        wthread.daemon =True
        wthread.start()
        print("serial server threading up")

    def _run_read(self):
        while self.ser.isOpen() :
            data_bytes = self.ser.read_until(b"EOT\n")
            try:
                # Convertir les bytes en JSON
                json_data = json.loads(data_bytes.decode('utf-8'))
                #print("Received data:", json_data)
                # Stocker les données dans la base de données
                self.store_data_in_db(json_data)
            except (json.JSONDecodeError, UnicodeDecodeError) as e:
                pass
                #print("Error decoding JSON:", e)
            print(data_bytes[:-4])

    def _run_write(self):
        while self.ser.isOpen():
            msg = self.q.get()
            if self.ser.isOpen():
                self.ser.write(msg)
            print("Message <" + msg + "> sent to micro-controller." )

    def send(self, msg: bytes):
        
        self.q.put(msg)
    
    def close(self):
         print("closing serial ...")
         self.ser.close()
           