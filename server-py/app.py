# Program to control passerelle between Android application
# and micro-controller through USB tty

import SerialServer
import UDPServer
import DBManager
import AppObject
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
                AppObject.AppObject.__initClass__(self)
                self.q = queue.Queue()

        def init(self):
                self.udpserv = UDPServer.UDPServer("0.0.0.0", 10000)
                self.serialserv = SerialServer.SerialServer("/dev/ttyACM0", 115200)
                self.dbManager = DBManager.DBManager('data.db')
                self.commands ={
                        "get-devices": self.dbManager.getDevices
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

        def execCommand(self, command, args= None):
                if command in self.commands:
                        if args:
                                self.commands[command](args)
                        else:
                                self.commands[command]()    
                else:
                        print("Unknown command: ", command)



# Main program logic follows:
if __name__ == '__main__':
        main()