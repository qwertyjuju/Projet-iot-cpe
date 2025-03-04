from enum import Enum

class EventSender(Enum):
    APP=0,
    SERIAL=1,
    UDP=2
    

class Event:
    """
    Classe Event a envoyé aux differents threads
    """
    def __init__(self, sender: EventSender, cmd=None, args=[], address = None):
        self.sender = sender
        self.cmd = cmd
        self.args = args
        self.data = {}
        self.address = address
        self.processed=False

    def setcmd(self,cmd):
        self.cmd = cmd

    def setData(self, data):
        self.data = data

    def setProcessed(self):
        self.processed = True    
        
    def setargs(self, args):
        self.args = args

    def getData(self):
        return self.data
    
    def isprocessed(self):
        return self.processed
    
    def getSender(self):
        return self.sender

    def getArgs(self):
        return self.args
    
    def getCmd(self):
        return self.cmd
    
    def getAddress(self):
        return self.address