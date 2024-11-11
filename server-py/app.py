# Program to control passerelle between Android application
# and micro-controller through USB tty
import pathlib
import SerialServer
import UDPServer
import DBManager
from  AppObject import AppObject
import queue

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
                self.serialserv = SerialServer.SerialServer("/dev/ttyACM0", 115200)
                self.dbManager = DBManager.DBManager('data.db', 'script_bdd.sql')
                self.UDPCommands ={
                        "get-devices": self.dbManager.getDevices
                }
                self.serialCommands ={
                        "get-device": self.dbManager.getDevice
                }

        def run(self):
                self.udpserv.run()
                self.serialserv.run()
                while True:
                        item = self.q.get()
                        print(item)

        def close(self):
                self.udpserv.close()
                self.serialserv.close()

        def execUDPCommand(self, command, args= None):
                try:
                        if command in self.UDPCommands:
                                if args:
                                        self.UDPCommands[command](args)
                                else:
                                        self.UDPCommands[command]()    
                        else:
                                self.log("Unknown UDP command: ", command)
                except Exception as e:
                        self.log(e)

        def execSerialCommand(self, command, args=None):
                try:
                        if command in self.serialCommands:
                                if args:
                                        self.serialCommands[command](args)
                                else:
                                        self.serialCommands[command]()    
                        else:
                                self.log("Unknown Serial command: ", command)
                except Exception as e:
                        self.log(e)

        def log(self, msg):
                self.q.put(msg)


# Main program logic follows:
if __name__ == '__main__':
        main()