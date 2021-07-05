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

global program_start_time
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

#Short Timeout. Will return FALSE if over one second has passed in the loop
def Timeout(current_time, timeout):
    if time.time() > current_time + timeout:
        time_marker = 0;
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

#Writing to I2C bus @ specific address
def writeString(address, word):
    try:
        for character in word:
            bus.write_byte(address, ord(character))
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
        saved_time = time.time()
        while answer != 'MPU Initialized' and Timeout(saved_time, 1):
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
                writeNumber(stm_address, ord('<'))
                OBC_to_COMMS(answer)
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
    
def read_multi_EPS():
        rx = []
        i = 0
        if read_single_EPS() == '<':
            rx.append(read_single_EPS())
            while rx[i] != '>':
                rx.append(read_single_EPS())
                i = i + 1
            return rx
def EPS_PreData():
    writeNumber(stm_address, ord('<'))
    time = "Time:"
    writeString(stm_address, time)
    current_time = int(program_start_time) - int(time.time())
    minutes = str(int(current_time/60))
    seconds = str(current_time % 60)
    writeString(stm_address, minutes)
    writeNumber(stm_address, ord('m'))   
    writeString(stm_address, seconds)
    writeNumber(stm_address, ord('s'))
    
def do_read_EPS(data):
    request_num = int(data)
    if request_num != 0 or not None:
        rx_data = read_multi_EPS()
        if len(rx_data)>0:
            print_list(rx_data)
            EPS_PreData()
            OBC_to_COMMS(rx_data)
            writeNumber(stm_address, ord('>'))
    else:
        raise ValueError("error: expected number of rx bytes!")
   
def OBC_to_COMMS(data):
    data_list=list(data)
    for i in data_list:
        #Sends to the Slaves
        if i is None:
            writeNumber(stm_address, int(ord('~')))
            print ("Could not write value to STM!")
        else:
            writeNumber(stm_address, int(ord(i)))
            time.sleep(.001)

####################################################################
########################## MAIN PROGRAM ############################
####################################################################
'''
begintime = time.gmtime(0)
print(begintime)
Program_Start_Time = time.time()
intstarttime = int(Program_Start_Time)
print(intstarttime)
while (Timeout(Program_Start_Time, 10)):
    current_time = int(time.time()) - intstarttime
    print(current_time)
       
'''
def main():
    
######################### INITIALIZATION ###########################
    program_start_time = time.time()
    print("Hello World!")
    LEDInit()
    OrientationInit()
    current_time = time.time()
    while Timeout(current_time, 1):
           print(current_time)
           print(time.time())
########################### MAIN LOOP ##############################
    
    while(1):

        #call LED indicator
        LEDindicator()
        #Transmit data from ADCS to Comms
        OrientationTransmit()
        do_read_EPS(6)
        #readFromEPS()
        #sendToComms()
        time.sleep(0.5)

if __name__ == "__main__":
    main()
