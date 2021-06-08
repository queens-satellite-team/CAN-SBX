import time
#### init #####
def init():
    print("init all connections")

##### LED indicator ####
def LEDindicator():
    print("run the LED function")

###### Read from ADCS #####
def readFromADCS():
    print("reading form EPS")


##### Read from EPS #####
def readFromEPS():
    print ("reading from EPS")

##### Send infomation to Comms #####
def sendToComms():
    print("send infomation to comms")


def main():
    init()
    while(1):
        print("Hello World!")
            #call LED indicator
            #get ADCS info
            #get EPD info
            #send info to COMMS
        LEDindicator()
        readFromADCS()
        readFromEPS()
        sendToComms()
        

if __name__ == "__main__":
    main()
