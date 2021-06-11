#RPi Pinouts

#I2C Pins 
#GPIO2 -> SDA
#GPIO3 -> SCL

#Import the Library Requreid 
import smbus
import serial,time
from serial import Serial


# for RPI version 1, use "bus = smbus.SMBus(0)"
bus = smbus.SMBus(1)

#Slave Address
address = 0x04


def writeNumber(value):
    bus.write_byte(address, value)
    return -1


def readNumber():
    number = bus.read_byte_data(address, 1)
    return number

if __name__ == '__main__':
    print('Running. Press CTRL-C to exit.')
    with serial.Serial("/dev/ttyACM0", 115200, timeout=1) as arduino:
        time.sleep(0.1) #wait for serial to open
        if arduino.isOpen():
            print("{} connected!".format(arduino.port))

              
                
        else:
            print("no data!")
    
buffer = arduino.inWaiting()
print(buffer)
while True:
    #Receives the data from the User
    if  arduino.inWaiting()>0: 
                 answer=arduino.readline(8)
                 print(answer)
    data_list = list(answer)
    for i in data_list:
        #Sends to the Slaves 
        writeNumber(int(ord(i)))
        time.sleep(.01)
    writeNumber(int(0x0A))
    arduino.flushInput() #remove data after reading