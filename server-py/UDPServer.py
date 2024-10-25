
import time
import argparse
import signal
import sys
import socket
import socketserver
import threading

class ThreadedUDPRequestHandler(socketserver.BaseRequestHandler):

    def handle(self):
        data = self.request[0].strip()
        socket = self.request[1]
        current_thread = threading.current_thread()
        print("{}: client: {}, wrote: {}".format(current_thread.name, self.client_address, data))
        #if data != "":
            #if data in MICRO_COMMANDS: # Send message through UART
            #       sendUARTMessage(data)
                    
            #elif data == "getValues()": # Sent last value received from micro-controller
            #        socket.sendto("", self.client_address) 
                    # TODO: Create last_values_received as global variable      
            #else:
            #        print("Unknown message: ",data)

class ThreadedUDPServer(socketserver.ThreadingMixIn, socketserver.UDPServer):
    pass


class UDPServer:
    def __init__(self, host,port):
        self.host = host
        self.port = port
        self.server = ThreadedUDPServer((host, port), ThreadedUDPRequestHandler)
        self.server_thread = threading.Thread(target=self.server.serve_forever)
        self.server_thread.daemon = True
    
    def run(self):
        self.server_thread.start()
        print(f"Server started at {self.host} port {self.port}")
    
    def stop(self):
        self.server.shutdown()
        self.server.server_close()

    