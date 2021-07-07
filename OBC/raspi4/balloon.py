

####################################################################
########################### USER CONFIG ############################
####################################################################

portname = "/dev/ttyS0"  # for comms STM32 on raspberryPi 	

####################################################################
############################# IMPORTS ##############################
####################################################################

from datetime import datetime
import serial as Serial
import sys
import serial
import time
import base64
import smbus
from enum import Enum

####################################################################
############################# GLOBALS ##############################
####################################################################

startMarker = "<"
endMarker = ">"
dataStarted = False
newCMD = False
dataBuf = ""
img_string = ""
messageComplete = False
pack_size = 32
start = 0
stop = pack_size
address = 0x04
global arduino
global answer
# for RPI version 1, use "bus = smbus.SMBus(0)"
bus = smbus.SMBus(1)

####################################################################
############################# ERRORS ###############################
####################################################################

class SatelliteErrors(Enum):
    SERIAL_DEVICE_NOT_FOUND = ()
    SERIAL_PARAM_OUT_OF_RANGE = ()
    UNKNOWN_ERROR = ()

####################################################################
####################### CONTROL SUBROUTINES ########################
####################################################################
def setupSerial(serial, baudRate, serialPortName):
    try:
        return serial.Serial(port=serialPortName,\
                             baudrate=baudRate,\
                             timeout=0,\
                             rtscts=True)
    except Serial.SerialException as e:
        print("Serial port: "+serialPortName+" could not be opened")
        return SatelliteErrors.SERIAL_DEVICE_NOT_FOUND
    except ValueError as e:
        print("Serial port parameter ", baudRate, " was out of range or invalid")
        return SatelliteErrors.SERIAL_PARAM_OUT_OF_RANGE
    except:
        return SatelliteErrors.UNKNOWN_ERROR

def writeNumber(value):
    bus.write_byte(address, value)
    return -1


def readNumber():
    number = bus.read_byte_data(address, 1)
    return number

def OrientationInit():
    global arduino
    arduino = serial.Serial()
    arduino.baudrate= 115200
    arduino.port = "/dev/ttyACM0"
    arduino.open()
    if __name__ == '__main__':
       # with serial.Serial("/dev/ttyACM0", 115200, timeout=1) as arduino:
                time.sleep(1) #wait for serial to open
                print('Running. Press CTRL-C to exit.')
                answer=arduino.readline().decode('utf-8').rstrip()
                arduino.flushInput()
                while answer != 'MPU Initialized':
                    if arduino.isOpen():
                        if  arduino.in_waiting > 0:
                            answer=arduino.readline().decode('utf-8').rstrip()
                            #answer=arduino.readline().decode('utf-8').rstrip()
                            print(answer)
               

def OrientationTransmit():
     if __name__ == '__main__':
        #with serial.Serial("/dev/ttyACM0", 115200, timeout=1) as arduino:
                if arduino.isOpen():
                    time.sleep(0.3)
                    if  arduino.in_waiting > 0:
                        input=arduino.in_waiting
                        answer=arduino.read(input).decode('utf-8').rstrip()
                        print(answer)
                        data_list=list(answer)
                        writeNumber(ord('<'))
                        for i in data_list:
                            #Sends to the Slaves 
                            writeNumber(int(ord(i)))
                            time.sleep(.001)
                        writeNumber(ord('>'))
                        arduino.flushInput()
                    time.sleep(0.1)
                else:
                    print("no data!")
                arduino.flushInput()


####################################################################
########################## MAIN PROGRAM ############################
####################################################################

######################### INITIALIZATION ###########################
OrientationInit()

########################### MAIN LOOP ##############################
while ('true'):
    OrientationTransmit()

