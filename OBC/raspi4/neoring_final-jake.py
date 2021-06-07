# all colours were taken from from here: https://www.rapidtables.com/web/color/RGB_Color.html

import RPi.GPIO as GPIO
import time
import board
import neopixel

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
 
pixels = neopixel.NeoPixel(
    pixel_pin, num_pixels, brightness=0.4, auto_write=False, pixel_order=ORDER
)

#Turn all the leds off when the code runs for the first time
for i in range(12):
    pixels[i] = (0,0,0)
    pixels.show()
 
while 1:
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
       