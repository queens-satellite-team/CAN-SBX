import serial,time
from serial import Serial
if __name__ == '__main__':
    
    print('Running. Press CTRL-C to exit.')
    with serial.Serial("/dev/ttyACM0", 115200, timeout=1) as arduino:
        time.sleep(0.1) #wait for serial to open
        if arduino.isOpen():
            print("{} connected!".format(arduino.port))
        
            if  arduino.inWaiting()>0: 
                answer=arduino.readline()
                print(answer)
                arduino.flushInput() #remove data after reading
        
