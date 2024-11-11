class SerialPacket:
    def __init__(self, buffer: bytes):
        self.buffer = buffer
        self.opcode = int(self.buffer[0])
        print(self.opcode)
        self._rawdata  = buffer[1:]
        self.size =len(buffer)
        self.data ={}
        if self.opcode == 0:
            self.data["SNumber"]
        if self.opcode == 255:
            self.data["msg"]

    def getData(self):
        return self.data
    
    def getOpCode(self):
        return self.opcode

    