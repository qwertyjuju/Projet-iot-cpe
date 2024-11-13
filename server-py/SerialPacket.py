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
                i =3
                self.data["IDsrc"] = int(buffer[1:2])
                self.data["data"] ={}
                while(i<=self.size-1):
                    measuretype  = int(buffer[i])
                    if measuretype == 1:
                        self.data["data"]["temp"]=int.from_bytes(buffer[i+1:i+4], "little", signed = True)
                        i+=5
                    if  measuretype == 2:
                        self.data["data"]["pres"]=int.from_bytes(buffer[i+1:i+4], "little")
                        i+=5
                    if  measuretype == 4:
                        self.data["data"]["hum"]=int.from_bytes(buffer[i+1:i+4], "little")
                        i+=5
                    if measuretype== 8:
                        self.data["data"]["lux"]=int.from_bytes(buffer[i+1:i+4], "little")
                        i+=5
                    if measuretype == 16:
                        self.data["data"]["ir"]=int.from_bytes(buffer[i+1:i+2], "little")
                        i+=3
                    if  measuretype == 32:
                        self.data["data"]["uv"]=int.from_bytes(buffer[i+1:i+2], "little")
                        i+=3
                
        else:
            self.opcode =0
            self.buffer =""

    def setOpCode(self,code):
        self.opcode = code

    def appendBuffer(self, i):
        self.buffer += str(i)

    def getBuffer(self):
        self.buffer =str(self.opcode)+self.buffer
        return self.buffer


    def getData(self):
        return self.data
    
    def getOpCode(self):
        return self.opcode

    