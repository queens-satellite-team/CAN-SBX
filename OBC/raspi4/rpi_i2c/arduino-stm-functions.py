

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
address = 0x04
global LinePos
LinePos = 0

def writeNumber(value):
    bus.write_byte(address, value)
    return -1


def readNumber():
    number = bus.read_byte_data(address, 1)
    return number

def OrientationInit():
        print('Running. Press CTRL-C to exit.')
        answer=arduino.readline().decode('utf-8').rstrip()
        arduino.flush()
        while answer != 'MPU Initialized':
            if arduino.isOpen():
                if  arduino.in_waiting > 0:
                    answer=arduino.readline().decode('utf-8').rstrip()
                    #answer=arduino.readline().decode('utf-8').rstrip()
                    print(answer)
        arduino.flush()
                           
                            
                           

def OrientationTransmit():
                        if arduino.isOpen():
                            if  arduino.in_waiting > 0:
                                answer=arduino.readline().decode('utf-8').rstrip()
                                print(answer)
                                data_list=list(answer)
                                writeNumber(ord('<'))
                                for i in data_list:
                                    #Sends to the Slaves 
                                    writeNumber(int(ord(i)))
                                    time.sleep(.01)
                                writeNumber(ord('>'))
                            time.sleep(0.1)
                        else:
                            print("no data!")
                        arduino.flush()
                        
        
if __name__ == '__main__':
    with serial.Serial("/dev/ttyACM0", 115200, timeout=1) as arduino:
        time.sleep(1) #wait for serial to open
        answer=arduino.readline().decode('utf-8').rstrip()
        arduino.flush()
        OrientationInit()
        while ('true'):    
            OrientationTransmit()
print("Finished!")
            
