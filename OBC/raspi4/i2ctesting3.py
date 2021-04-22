#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Raspberry Pi to Arduino I2C Communication
#i2cdetect -y 1
#library
import sys
import smbus2 as smbus#,smbus2
import time
# Slave Addresses
I2C_SLAVE_ADDRESS = 11 #0x0b ou 11
I2C_SLAVE2_ADDRESS = 12
I2C_SLAVE3_ADDRESS = 13
# This function converts a string to an array of bytes.
def ConvertStringsToBytes(src):
  converted = []
  for b in src:
    converted.append(ord(b))
  return converted

def ConvertBytesToStrings(src):
    converted=[]
    for a in src:
        converted.append(chr(a))
    return converted

def main(args):
    # Create the I2C bus
    I2Cbus = smbus.SMBus(1)
    with smbus.SMBus(1) as I2Cbus:
        slaveSelect = input("Which Arduino (1-3): ")
        
        if slaveSelect == "1":
            slaveAddress = I2C_SLAVE_ADDRESS
        elif slaveSelect == "2":
            slaveAddress = I2C_SLAVE2_ADDRESS
        elif slaveSelect == "3":
            slaveAddress = I2C_SLAVE3_ADDRESS
        else:
            # quit if you messed up
            print(slaveSelect== "1")
            print(type(slaveSelect))
            print("no slave selected")
            quit()
            
        cmd = input("Enter command: ")
        while (cmd!="quit"):
            if cmd=="quit":
                break
            BytesToSend = ConvertStringsToBytes(cmd)
            print("Sent " + str(slaveAddress) + " the " + str(cmd) + " command.")
            print(BytesToSend )
            I2Cbus.write_i2c_block_data(slaveAddress, 0x00, BytesToSend)
            time.sleep(0.5)
            
           
            length=len(cmd)
            print("returned from slave: ")
            while length>0:
                try:
                    data=I2Cbus.read_i2c_block_data(slaveAddress,0x00,1)
                    #print("recieve from slave:")
                    print(data)
                    length-=1
                    
                except:
                    print("remote i/o error")
                    time.sleep(1)
                    length-=1
                
            cmd = input("Enter command: ")
            
    return 0
if __name__ == '__main__':
     try:
        main(sys.argv)
     except KeyboardInterrupt:
        print("program was stopped manually")
     input()