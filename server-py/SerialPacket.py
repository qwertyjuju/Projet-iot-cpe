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
        else:
            self.opcode =0
            self.buffer = bytearray()

    def setOpCode(self,code):
        self.opcode = code

    def appendBuffer(self, i, size=None):
        if type(i) is int:
            if size:
                self.buffer.extend(i.to_bytes(size,"big"))
            else:
                self.buffer.extend(i.to_bytes(2,"big"))
        if type(i) is str:
            self.buffer.extend(i.encode())
        

    def getBuffer(self):
        tbuffer =bytearray(self.opcode.to_bytes(2,"big"))
        self.buffer = tbuffer+self.buffer
        return self.buffer


    def getData(self):
        return self.data
    
    def getOpCode(self):
        return self.opcode

    