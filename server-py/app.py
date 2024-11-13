# Program to control passerelle between Android application
# and micro-controller through USB tty
import pathlib
import SerialServer
import UDPServer
import DBManager
from  AppObject import AppObject
import queue
from Event import EventSender, Event
from SerialPacket import SerialPacket

def main():
        app = Application()
        app.init()
        print ('Press Ctrl-C to quit.')
        try:
                app.run()
        except (KeyboardInterrupt, SystemExit):
                app.close()
                exit()

class Application:
        def __init__(self):
                AppObject.__initClass__(self)
                self.q = queue.Queue()


        def init(self):
                self.udpserv = UDPServer.UDPServer("0.0.0.0", 10000)
                #self.serialserv = SerialServer.SerialServer("/dev/ttyACM0", 115200)
                self.dbManager = DBManager.DBManager('data.db', 'script_bdd.sql')
                self.commands = {
                        "get-device": self.dbManager.getDevice,
                        "get-devices": self.dbManager.getDevices,
                        "get-measures": self.dbManager.getMeasures,
                        "get-measure": self.dbManager.getMeasure,
                        "register-measure": self.dbManager.registerMeasure,
                        "set-order": self.setOrder,
                        "log": self.log,
                }

        def run(self):
                self.udpserv.run()
                #self.serialserv.run()
                while True:
                        event = self.q.get()
                        self.processEvent(event)

        def close(self):
                self.udpserv.close()
                #self.serialserv.close()

        def addEvent(self, event: Event):
                self.q.put(event)

        def processEvent(self, event: Event):
                try:
                        command = event.getCmd()
                        args =event.getArgs()
                        sender = event.getSender()
                        print(args)
                        if  command in self.commands:
                                if args:
                                        event.setData(self.commands[command](*event.getArgs()))
                                else:
                                        event.setData(self.commands[command]())
                        else:
                                self.log(f"Unknown command:  {command}")
                        event.setProcessed()
                        if sender == EventSender.SERIAL:
                                self.serialserv.finishEvent(event)
                        if sender == EventSender.UDP:
                                self.udpserv.finishEvent(event)
                except Exception as e:
                        self.log(e)

        def setOrder(self, deviceId, order):
                self.dbManager.setOrder(deviceId, order)
                p :SerialPacket = SerialPacket()
                p.setOpCode(2)
                p.appendBuffer(order)
                deviceId =int(deviceId)
                high_byte = (deviceId >> 8) & 0xFF 
                low_byte = deviceId & 0xFF 
                p.appendBuffer(chr(high_byte))
                p.appendBuffer(chr(low_byte))
                self.serialserv.send(p)


        def log(self, msg):
                print(msg)


# Main program logic follows:
if __name__ == '__main__':
        main()