import serial 


class SerialServer:
    def __init__(self, port, baudrate):
        self.ser=serial.Serial()
        # ser = serial.Serial(SERIALPORT, BAUDRATE)
        self.ser.port=port
        self.ser.baudrate=baudrate
        self.ser.bytesize = serial.EIGHTBITS #number of bits per bytes
        self.ser.parity = serial.PARITY_NONE #set parity check: no parity
        self.ser.stopbits = serial.STOPBITS_ONE #number of stop bits
        self.ser.timeout = None          #block read
        # ser.timeout = 0             #non-block read
        # ser.timeout = 2              #timeout block read
        self.ser.xonxoff = False     #disable software flow control
        self.ser.rtscts = False     #disable hardware (RTS/CTS) flow control
        self.ser.dsrdtr = False       #disable hardware (DSR/DTR) flow control
        #ser.writeTimeout = 0     #timeout for write
        print('Starting Up Serial Monitor')
        try:
            self.ser.open()
        except serial.SerialException:
                print("Serial {} port not available".format(port))
                exit()

    def sendUARTMessage(self, msg):
        self.ser.write(msg)
        print("Message <" + msg + "> sent to micro-controller." )

    def run(self):
        while self.ser.isOpen() :
            data_str = self.ser.read_until(b"EOT\n");
            # Store data HERE
            print(data_str)
         
    def close(self):
         self.ser.close()
           