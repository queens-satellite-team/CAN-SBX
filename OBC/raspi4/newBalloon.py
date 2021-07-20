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
program_start_time = time.time()
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

    #Subsystem GPIO status check
    global payload1status
    global payload2status
    global epsstatus
    global adcsstatus
    global commsstatus
    
    payload1status = 0
    payload2status = 0
    epsstatus = 0
    adcsstatus = 0
    commsstatus = 0
    
     #GPIO pins that each subsystem connects to on the pi
    payload1Pin = 25
    payload2Pin = 16
    adcsPin = 13
    commsPin = 20
    epsPin = 21

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
    if ((int(time.time()) - int(program_start_time)) % 3 == 0):    
        print("run the LED function")
        if GPIO.input(payload1Pin) and GPIO.input(payload2Pin) and GPIO.input(epsPin) and GPIO.input(adcsPin) and GPIO.input(commsPin):
            pixels[statusLed] = (0, 255, 0)  # green
            pixels.show()
            
            
        else :
            pixels[statusLed] = (0, 0, 0)

    #payload
        payload1stat = GPIO.input(payload1Pin)
        print(payload1stat)
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
            pixels[adcsLed]=(255,128,0) # yellow
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
            pixels[epsLed]=(255,0,0)    #  red
            pixels.show()
    else:
        for i in range(12):
            pixels[i] = (0,0,0)
            pixels.show()

def ClockMatching():
    
    global payload1status
    global payload2status
    global epsstatus
    global adcsstatus
    global commsstatus
    
    if payload1status == 0 and GPIO.input(payload1Pin):
        writeString(stm_address, "<Payload 1 turned on ")
        writeTime(stm_address)
        writeString(stm_address, " after the OBC turned on>")
        payload1status = 1
        
    if payload2status == 0 and GPIO.input(payload2Pin):
        writeString(stm_address, "<Payload 2 turned on ")
        writeTime(stm_address)
        writeString(stm_address, " after the OBC turned on>")
        payload2status = 1
        
    if epsstatus == 0 and GPIO.input(epsPin):
        writeNumber(stm_address, '<')
        writeString(stm_address, "EPS turned on ")
        writeTime(stm_address)
        writeString(stm_address, " after the OBC turned on>")
        epsstatus = 1
        
    if adcsstatus == 0 and GPIO.input(adcsPin):
        writeNumber(stm_address, '<')
        writeString(stm_address, "ADCS turned on ")
        writeTime(stm_address)
        writeString(stm_address, " after the OBC turned on>")
        adcsstatus = 1
        
    if commsstatus == 0 and GPIO.input(commsPin):
        writeNumber(stm_address, '<')
        writeString(stm_address, "Comms turned on ")
        writeTime(stm_address)
        writeString(stm_address, " after the OBC turned on>")
        commsstatus = 1
     
    if payload1status == 1 and not GPIO.input(payload1Pin):
        writeString(stm_address, "<Payload 1 turned off ")
        writeTime(stm_address)
        writeString(stm_address, " after the OBC turned on>")
        payload1status = 0
        
    if payload2status == 1 and not GPIO.input(payload2Pin):
        writeString(stm_address, "<Payload 2 turned off ")
        writeTime(stm_address)
        writeString(stm_address, " after the OBC turned on>")
        payload2status = 0
        
    if epsstatus == 1 and not GPIO.input(epsPin):
        writeNumber(stm_address, '<')
        writeString(stm_address, "EPS turned off ")
        writeTime(stm_address)
        writeString(stm_address, " after the OBC turned on>")
        epsstatus = 0
        
    if adcsstatus == 1 and not GPIO.input(adcsPin):
        writeNumber(stm_address, '<')
        writeString(stm_address, "ADCS turned off ")
        writeTime(stm_address)
        writeString(stm_address, " after the OBC turned on>")
        adcsstatus = 0
        
    if commsstatus == 1 and not GPIO.input(commsPin):
        writeNumber(stm_address, '<')
        writeString(stm_address, "Comms turned off ")
        writeTime(stm_address)
        writeString(stm_address, " after the OBC turned on>")
        commsstatus = 0   
        
#Timeout function. Will return FALSE if 'timeout' seconds have passed. Must be given the current time with time.time()
def Timeout(current_time, timeout):
    if time.time() > current_time + timeout:
        time_marker = 0;
        return Fals<e
    else:
        return True
    

#Writing character to I2C bus @ specific address
def writeNumber(address, value):
    try:
        bus.write_byte(address, ord(value))
    except:
        print("Device with address:", address, "is not connected!")
        pass
    return -1

#Writing string to I2C bus @ specific address
def writeString(address, word):
    try:
        for character in word:
            bus.write_byte(address, ord(character))
    except:
        print("STM Not Connected!")
        pass
    return -1

def writeTime(address):
    current_time = time.time() - program_start_time
    minutes = int(current_time/60)
    seconds = int(current_time % 60)
    milliseconds = int(((current_time-int(current_time))*1000))
    writeString(address, str(minutes))
    writeNumber(address, 'm')   
    writeString(address, str(seconds))
    writeNumber(address, 's')
    writeString(address, str(milliseconds))
    writeString(address, 'ms')
    writeNumber(address, ',')
    writeNumber(address, ' ')

#Read from I2c bus @ specific address
def readNumber():
    number = bus.read_byte_data(address, 1)
    return number

#Initializes the Orientation function by running through all the initial, irrelevant serial data
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
               
#Used to print data received from the EPS to the python terminal.
def print_list(l):
    if l == ' ' or l is None:
        print()
    else:
        for c in l:
            print(c, end='')
        print()

#Requests a single byte from the EPS
def read_single_EPS():
    try:
        number = bus.read_byte_data(arduino_address, 1)
        return chr(number)
    except:
        print("EPS not connected!")
        pass
 
#Requests bytes from EPS until a '>' character is found indicating that the information transfer is complete.  
def read_multi_EPS():
        rx = []
        i = 0
        if read_single_EPS() == '<':
            rx.append(read_single_EPS())
            current_time = time.time()
            while rx[i] != '>' and Timeout(current_time, 1):
                rx.append(read_single_EPS())
                i = i + 1
            return rx

#Transmits 'data' from OBC to comms. Note that start characters ('<') and end characters ('>') are required as well.
def OBC_to_COMMS(data):
    data_list=list(data)
    for i in data_list:
        #Sends to the Slaves
        if i is None:
            writeNumber(stm_address, '~')
            print ("Could not write value to STM!")
        else:
            writeNumber(stm_address, i)
            time.sleep(.001)

#When data is ready to be sent to comms PreData is called to get and display the time of data transfer.
def PreData():
    writeNumber(stm_address, '<')
    writeString(stm_address, "Time: ")
    writeTime(stm_address)
 
#Transmits EPS data to COMMS 
def EPSTransmit():
        rx_data = read_multi_EPS()
        if rx_data is not None:
            print_list(rx_data)
            PreData()
            writeString(stm_address, "EPS Data: ")
            OBC_to_COMMS(rx_data)
            writeNumber(stm_address, '>')

#Transmits ADCS data to COMMS
def ADCSTransmit():
     if __name__ == '__main__':
        #with serial.Serial("/dev/ttyACM0", 115200, timeout=1) as arduino:
        if arduino.isOpen():
            time.sleep(0.3)
            if  arduino.in_waiting > 0:
                input=arduino.in_waiting
                answer=arduino.read(input).decode('utf-8').rstrip()
                print(answer)
                writeNumber(stm_address, '<')
                PreData()
                writeString(stm_address, "Orientation Data: ")
                OBC_to_COMMS(answer)
                writeNumber(stm_address, '>')
                arduino.flushInput()
            time.sleep(0.1)
        else:
            print("no data!")
        arduino.flushInput()



####################################################################
########################## MAIN PROGRAM ############################
####################################################################

def main():
    
######################### INITIALIZATION ###########################
    print("Hello World!")
    LEDInit()
    OrientationInit()

########################### MAIN LOOP ##############################
    
    while(1):
        #check which systems are connected 
        ClockMatching()
        #call LED indicator
        LEDindicator()
        #Transmit data from ADCS to Comms
        #ADCSTransmit()
        #Transmit data from EPS to Comms
        #EPSTransmit()
        time.sleep(0.2)

if __name__ == "__main__":
    main()
