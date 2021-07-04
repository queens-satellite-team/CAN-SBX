#!/usr/bin/python3

"""
author: sean tedesco
email:  17sart@queensu.ca
date:   July 1st, 2021

RASPERRY PI PIN OUTS
    GPIO2 (PIN3) -> SDA
    GPIO3 (PIN5) -> SCL
    GND   (PIN9) -> Ground (not sure if this is necessecary, but still a good practice)
    
TO DO:
    - look into using argeparse package for proper parsing
    - look into developing an "I2C manager" class for the OBC
        - related we could make a "manager class" for each of the comms protocols used
    - support different data types (only working with <str> currently)
    
- please reach out for any and all questions - 
"""

import smbus
import time
import re

bus = smbus.SMBus(1)

#slave address, must match the address on the ardiuno
address_1 = 0x04

def print_list(l):
    if l == ' ' or l is None:
        print()
    else:
        for c in l:
            print(c, end='')
        print()

def write_single(value):
    bus.write_byte(address_1, value)
    return -1

def do_write(data):
    data_list = list(data)
    for i in data_list: 
        write_single(int(ord(i)))
        time.sleep(0.001)

    write_single(int(0x0A))       
        
def read_single():
    number = bus.read_byte_data(address_1, 1)
    return chr(number)
    
def read_multi(count):
    rx = []
    for i in range(count):
        rx.append(read_single())
    return rx

def do_read(data):
    request_num = int(data)
    if request_num != 0 or not None:
        rx_data = read_multi(request_num)
    else:
        raise ValueError("error: expected number of rx bytes!")
    print_list(rx_data)
    
while True:
    #receive user input 
    user_input = input("read [-r -#] or write [-w -this is a message]: ")
    parsed_input = re.split('-', user_input)
    if len(parsed_input) != 3:
        raise ValueError("error: invalid number of arguements")
    
    #parse the input into flag and data
    flag = parsed_input[1].strip()
    data = parsed_input[2].strip()
    
    #perform the approiate response depending on the flag
    if flag == 'r':
        do_read(data)
    elif flag == 'w':
        do_write(data)
    else:
        print('unexpected flag: {}'.format(flag))

 