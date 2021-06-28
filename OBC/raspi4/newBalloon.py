import time
import RPi.GPIO as GPIO
import time
import board
import neopixel

#### init #####
def initLED():
    print("initializing the LED indicator...")
    #GPIO pins that each subsystem connects to on the pi
    global payload1Pin 
    payload1Pin = 13

    global payload2Pin
    payload2Pin = 19

    global adcsPin
    adcsPin = 16

    global commsPin
    commsPin = 26

    global epsPin
    epsPin = 5

    #led numbers for each subsystem
    
    
    global statusLed
    statusLed = 0

    global payload1Led
    payload1Led = 2

    global payload2Led 
    payload2Led = 4

    global adcsLed
    adcsLed = 6

    global commsLed 
    commsLed = 8

    global epsLed
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
    
    ORDER = neopixel.GRB
    
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
        pixels[payload1Led]=(76,0,153) #  purple
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
        pixels[commsLed]=(204,204,0)  #  blue
        pixels.show()

#eps
    if GPIO.input(epsPin):
        pixels[epsLed]=(0,0,0)
        pixels.show()
    else:
        pixels[epsLed]=(255,128,0)    #  yellow
        pixels.show()

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
    initLED()
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
