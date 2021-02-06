

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
import time
import base64
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

