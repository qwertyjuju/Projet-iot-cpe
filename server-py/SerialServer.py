import serial
import json
from AppObject import AppObject
import threading
import queue
import time
from SerialPacket import SerialPacket

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
                packet: SerialPacket = SerialPacket(self.ser.read_until(b"EOT\n")[:-4])
                match packet.getOpCode():
                    case 0:
                        self.app.execSerialCommand("get-device", packet.getData()["SNumber"])
                        break
                    case 255:
                        self.app.log(packet.getData()["msg"])
                        break
            except Exception as e:
                self.app.log(f"error: {e}")

    def _run_write(self):
        while self.ser.isOpen():
            try:
                msg = self.q.get()
                if self.ser.isOpen():
                    sendmsg= msg+"EOT\n"
                    self.ser.write(sendmsg.encode())
                self.app.log("Message <" + sendmsg + "> sent to micro-controller." )
            except Exception as e:
                self.app.log(e)

    def send(self, msg: bytes):
        self.q.put(msg)
    
    def close(self):
         print("closing serial ...")
         self.ser.close()
           