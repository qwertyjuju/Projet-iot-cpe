from enum import Enum

class EventType(Enum):
    APP=0,
    SERIAL=1,
    UDP=2
    

class Event:
    def __init__(self, eventType: EventType, cmd=None, args=[]):
        self.type = eventType
        self.cmd= None
        self.args=[]
        self.data = {}
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
    
    def getType(self):
        return self.type

    def getArgs(self):
        return self.args
    
    def getCmd(self):
        return self.cmd