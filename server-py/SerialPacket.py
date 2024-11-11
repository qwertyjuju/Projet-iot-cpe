class SerialPacket:
    def __init__(self, buffer: bytes):
        self.buffer = buffer
        self.opcode = int(self.buffer[0])
        self._rawdata :bytes = buffer[1:]
        self.size =len(buffer)
        self.data ={}
        if self.opcode == 0:
            self.data["SNumber"]= buffer[1:].decode()
        if self.opcode == 255:
            self.data["msg"] = buffer[1:].decode()

    def getData(self):
        return self.data
    
    def getOpCode(self):
        return self.opcode

    