####################################################################
################### Instructions and Definitions ###################
####################################################################
"""
Introduction:
This code will facilitate all communication between balloon subsystems, as well as control the LED indicator.
Author: Jake Milley
Email:  jake.milley@queensu.ca
Date:   July 4th, 2021

Notes:
- The OBC to COMMS Communication requires that a start char be sent to indicate that a string will be coming.
    - The start char is '<'
- The OBC to COMMS Communication requires that an end char be sent to indicate that the transmission of the string is complete.
    - The end char is '>'
- Sometimes information from OBC to COMMS will be lost during transmission. An error char is then sent indicating that information was lost 
    - The error char is '~'
"""
####################################################################
########################### USER CONFIG ############################
####################################################################

portname = "/dev/ttyS0"  # for comms STM32 on raspberryPi   

####################################################################
######################## IMPORTS & GLOBALS #########################
####################################################################

import smbus
import serial,time
from serial import Serial
import RPi.GPIO as GPIO
import time
import board
import neopixel
import os
import subprocess


# for RPI version 1, use "bus = smbus.SMBus(0)"
bus = smbus.SMBus(1)

#STM Slave Address
global stm_address
stm_address = 0x04

#Arduino Slave Address
global arduino_address
arduino_address = 0x11


####################################################################
####################### CONTROL SUBROUTINES ########################
####################################################################

def LEDInit():
    print("initializing the LED indicator...")
    #GPIO pins that each subsystem connects to on the pi
    global payload1Pin
    global payload2Pin
    global adcsPin
    global commsPin
    global epsPin

    #led numbers for each subsystem
    global statusLed
    global payload1Led
    global payload2Led
    global adcsLed
    global commsLed
    global epsLed

     #GPIO pins that each subsystem connects to on the pi
    payload1Pin = 13
    payload2Pin = 19
    adcsPin = 16
    commsPin = 26
    epsPin = 5

    #led numbers for each subsystem
    statusLed = 0
    payload1Led = 2
    payload2Led = 4
    adcsLed = 6
    commsLed = 8
    epsLed = 10

    GPIO.setmode(GPIO.BCM)
    GPIO.setup(statusLed, GPIO.IN)
    GPIO.setup(payload1Pin, GPIO.IN)
    GPIO.setup(payload2Pin, GPIO.IN)
    GPIO.setup(adcsPin, GPIO.IN)
    GPIO.setup(commsPin, GPIO.IN)
    GPIO.setup(epsPin, GPIO.IN)
    GPIO.setup(18, GPIO.OUT) 
    pixel_pin = board.D18
    
    num_pixels = 12
    
    ORDER = neopixel.GRB
    
    global pixels 
    pixels = neopixel.NeoPixel(
        pixel_pin, num_pixels, brightness=0.4, auto_write=False, pixel_order=ORDER
    ) 

#Turn all the leds off when the code runs for the first time
    for i in range(12):
        pixels[i] = (0,0,0)
        pixels.show()


##### LED indicator ####
def LEDindicator():
    print("run the LED function")
    if GPIO.input(payload1Pin) and GPIO.input(payload2Pin) and GPIO.input(epsPin) and GPIO.input(adcsPin) and GPIO.input(commsPin):
        pixels[statusLed] = (0, 255, 0)  # green
        pixels.show()
        time.sleep(5)
    else :
        pixels[statusLed] = (0, 0, 0)

#payload
    if GPIO.input(payload1Pin):
        pixels[payload1Led]=(0,0,0)
        pixels.show()
    else:
        pixels[payload1Led]=(127,0,153) #  purple
        pixels.show()

    if GPIO.input(payload2Pin):
        pixels[payload2Led]=(0,0,0)
        pixels.show()
    else:
        pixels[payload2Led]=(255,255,255) #  white
        pixels.show()
    
#adcs
    if GPIO.input(adcsPin):
        pixels[adcsLed]=(0,0,0)
        pixels.show()
    else:
        pixels[adcsLed]=(255,128,0) # orange
        pixels.show()
    
#comms
    if GPIO.input(commsPin):
        pixels[commsLed]=(0,0,0)
        pixels.show
    else:
        pixels[commsLed]=(0,0,225)  #  blue
        pixels.show()

#eps
    if GPIO.input(epsPin):
        pixels[epsLed]=(0,0,0)
        pixels.show()
    else:
        pixels[epsLed]=(255,0,0)    #  yellow
        pixels.show()

#Ensuring the I2C Device is connected
def isConnectedI2C(address):
    p = subprocess.Popen(['i2cdetect', '-y', '1'],stdout=subprocess.PIPE,)
    for i in range(0,9):
        line = str(p.stdout.readline())
    print(p)
    print(line)
    isConnected = line.find(str(address))
    if (isConnected == -1):
        return False
    else:
        return True
        
    

#Writing to I2C bus @ specific address
def writeNumber(address, value):
    try:
        bus.write_byte(address, value)
    except:
        print("STM Not Connected!")
        pass
    return -1
#Read from I2c bus @ specific address
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
                writeNumber(stm_address, ord('<'))
                for i in data_list:
                    #Sends to the Slaves 
                    writeNumber(stm_address, int(ord(i)))
                    time.sleep(.001)
                writeNumber(stm_address, ord('>'))
                arduino.flushInput()
            time.sleep(0.1)
        else:
            print("no data!")
        arduino.flushInput()

def print_list(l):
    if l == ' ' or l is None:
        print()
    else:
        for c in l:
            print(c, end='')
        print()
        
def read_single_EPS():
    try:
        number = bus.read_byte_data(arduino_address, 1)
        return chr(number)
    except:
        print("EPS not connected!")
        pass
    
def read_multi_EPS(count):
    rx = []
    for i in range(count):
        rx.append(read_single_EPS())
    return rx

def do_read_EPS(data):
    request_num = int(data)
    if request_num != 0 or not None:
        rx_data = read_multi_EPS(request_num)
        print_list(rx_data)
        data_list=list(rx_data)
        writeNumber(stm_address, ord('<'))
        for i in data_list:
            #Sends to the Slaves
            if i is None:
                writeNumber(stm_address, int(ord('~')))
                print ("Could not write value to STM!")
            else:
                writeNumber(stm_address, int(ord(i)))
                time.sleep(.001)
        writeNumber(stm_address, ord('>'))
        time.sleep(0.1)
    else:
        raise ValueError("error: expected number of rx bytes!")
   


####################################################################
########################## MAIN PROGRAM ############################
####################################################################

def main():
    
######################### INITIALIZATION ###########################
    print("Hello World!")
    LEDInit()
    #OrientationInit()
    
########################### MAIN LOOP ##############################
    
    while(1):

        #call LED indicator
        LEDindicator()
        #Transmit data from ADCS to Comms
        #OrientationTransmit()
        do_read_EPS(5)
        #readFromEPS()
        #sendToComms()
        time.sleep(0.5)

if __name__ == "__main__":
    main()
