
import time
import argparse
import signal
import sys
import socket
import socketserver
import threading
import json
from AppObject import AppObject

class ThreadedUDPRequestHandler(socketserver.BaseRequestHandler):

    def handle(self):
        data = self.request[0].strip()
        socket = self.request[1]
        self.server.print("bite")
        current_thread = threading.current_thread()
        print("{}: client: {}, wrote: {}".format(current_thread.name, self.client_address, data))
        if data != "":
            try:
                data = json.load(data)
                data["cmd"](data["args"])
            except Exception as e:
                print(e)


        #if data != "":
            #if data in MICRO_COMMANDS: # Send message through UART
            #       sendUARTMessage(data)
                    
            #elif data == "getValues()": # Sent last value received from micro-controller
            #        socket.sendto("", self.client_address) 
                    # TODO: Create last_values_received as global variable      
            #else:
            #        print("Unknown message: ",data)

class UDPServer(socketserver.ThreadingMixIn, socketserver.UDPServer, AppObject):
    def __init__(self, host,port):
        self.host = host
        self.port = port
        self.server_thread = threading.Thread(target=self.serve_forever)
        self.server_thread.daemon = True
        super().__init__((host, port),ThreadedUDPRequestHandler)
    
    def run(self):
        self.server_thread.start()
        print(f"Server started at {self.host} port {self.port}")
    
    def close(self):
        print("closing UDP Server...")
        self.shutdown()
        self.server_close()
    
    def print(self, text):
        print(text)
    