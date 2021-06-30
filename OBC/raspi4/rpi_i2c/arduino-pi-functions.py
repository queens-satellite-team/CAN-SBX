

#RPi Pinouts

#I2C Pins 
#GPIO2 -> SDA
#GPIO3 -> SCL

#mport the Library Required 
import smbus
import serial,time
import linecache
from serial import Serial


# for RPI version 1, use "bus = smbus.SMBus(0)"
bus = smbus.SMBus(1)

#Slave Address
arduino_address = 17


def writeNumber(address, value):
    bus.write_byte(address, value)
    return -1


def readNumber(address):
    number = bus.read_byte(address)
    return number

def readNumber_Data(address, offset):
    number = bus.read_byte_data(address, offset)
    return number

def readString(address2):
    time.sleep(0.2)
    while (readNumber(address2) != 100):
        time.sleep(0.2)
        number = readNumber(address2)
    return number

time.sleep(1)
while ('true'):
    writeNumber(arduino_address, 0)
    data = readNumber(arduino_address)
    
    time.sleep(0.2)
    print(data)
    
