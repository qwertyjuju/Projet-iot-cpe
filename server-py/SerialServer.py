import serial
import json
from AppObject import AppObject
import threading
import queue
import datetime
from SerialPacket import SerialPacket
from Event import Event, EventSender

class SerialServer(AppObject):
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
            try:   
                bytes =self.ser.read_until(b"EOT\n")[:-4]
                print(bytes)
                packet: SerialPacket = SerialPacket(bytes)
                opcode= packet.getOpCode()
                if opcode == 0: # si opcode == 0: récuperation/création du device dans la base de donnée et envoie de l'ID pour la communication
                    self.app.addEvent(Event(EventSender.SERIAL,"get-device", [packet.getData()["SNumber"], True]))
                if opcode ==1:  # si opcode == 1: décode les données et envoie dans la base de donnée
                    self.app.addEvent(Event(EventSender.SERIAL,"register-measure", [packet.getData()["IDsrc"], packet.getData()["data"], datetime.datetime.now()]))
                if opcode ==255: # si opcode == 2: log du message
                    self.app.addEvent(Event(EventSender.SERIAL,"log", [packet.getData()["msg"]]))
            except Exception as e:
                self.app.log(f"error: {e}")

    def _run_write(self):
        while self.ser.isOpen():
            try:
                msg : SerialPacket = self.q.get()
                if self.ser.isOpen():
                    sendmsg= msg.getBuffer()+"\r\n"
                    self.ser.write(sendmsg.encode())
                self.app.addEvent(Event(EventSender.SERIAL,"log", ["Message <" + str(sendmsg.encode()) + "> sent to micro-controller." ]))
            except Exception as e:
                self.app.addEvent(Event(EventSender.SERIAL,"log", [e]))

    def finishEvent(self, event: Event):
        if event.isprocessed():
            if event.getCmd() == "get-device":
                data :list =event.getData()
                p =SerialPacket()
                p.appendBuffer(data[2])
                p.appendBuffer(data[0])
                p.appendBuffer(data[3])
                self.send(p)

    def send(self, msg: SerialPacket):
        self.q.put(msg)
    
    def close(self):
         print("closing serial ...")
         self.ser.close()
           