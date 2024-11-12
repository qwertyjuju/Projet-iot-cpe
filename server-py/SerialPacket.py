class SerialPacket:
    def __init__(self, buffer: bytes=None):
        if buffer:
            self.buffer = buffer
            self.opcode = int(self.buffer[0])
            self.size =len(buffer)
            self.data ={}
            if self.opcode == 0:
                self.data["SNumber"]= buffer[1:].decode()
            if self.opcode == 255:
                self.data["msg"] = buffer[1:].decode()
            if self.opcode == 1:
                self.data["data"]
        else:
            self.opcode =0
            self.buffer =""

    def setOpCode(self,code):
        self.opcode = code

    def appendBuffer(self, i):
        self.buffer += str(i)

    def getBuffer(self):
        self.buffer =str(self.opcode) +self.buffer
        return self.buffer


    def getData(self):
        return self.data
    
    def getOpCode(self):
        return self.opcode

    