# Program to control passerelle between Android application
# and micro-controller through USB tty

import threading
import SerialServer
import UDPServer
import DBManager
import AppObject

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

        def init(self):
                self.udpserv = UDPServer.UDPServer("0.0.0.0", 10000)
                self.serialserv = SerialServer.SerialServer("/dev/ttyACM0", 115200)
                self.dbManager = DBManager.DBManager('data.db')      

        def run(self):
                self.udpserv.run()
                self.serialserv.run()

        def close(self):
                self.udpserv.close()
                self.serialserv.close()


# Main program logic follows:
if __name__ == '__main__':
        main()