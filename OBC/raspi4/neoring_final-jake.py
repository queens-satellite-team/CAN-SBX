
import RPi.GPIO as GPIO
import time
import board
import neopixel

#GPIO pins for each subsystem on the pi
comms = 26
eps = 5
adcs = 16
payload1 = 13
payload2 = 19

GPIO.setmode(GPIO.BCM)
GPIO.setup(eps, GPIO.IN)
GPIO.setup(payload1, GPIO.IN)
GPIO.setup(payload2, GPIO.IN)
GPIO.setup(comms, GPIO.IN)
GPIO.setup(adcs, GPIO.IN)
GPIO.setup(18, GPIO.OUT) #emma - what is this one for?
pixel_pin = board.D18
 
num_pixels = 12
 
ORDER = neopixel.GRB
 
pixels = neopixel.NeoPixel(
    pixel_pin, num_pixels, brightness=0.4, auto_write=False, pixel_order=ORDER
)

#Turn all the leds off 
for i in range(12):
    pixels[i] = (0,0,0)
    pixels.show()
 
pixels[0]=(0,255,0)
pixels.show()
 
while 1:
#power
    if GPIO.input(5):
        pixels[2]=(255,0,0)
        pixels.show()
        time.sleep(1)
    else:
        pixels[2]=(0,0,0)
        pixels.show()
        time.sleep(1)

    if GPIO.input(6):
        pixels[3]=(255,0,0)
        pixels.show()
        time.sleep(1)
    else:
        pixels[3]=(0,0,0)
        pixels.show()
        time.sleep(1)
    
#payload
    if GPIO.input(13):
        pixels[5]=(255,255,0)
        pixels.show()
        time.sleep(1)
    else:
        pixels[5]=(0,0,0)
        pixels.show()
        time.sleep(1)
    
    if GPIO.input(19):
        pixels[6]=(255,255,0)
        pixels.show()
        time.sleep(1)
    else:
        pixels[6]=(0,0,0)
        pixels.show()
        time.sleep(1)
    
#comms
    if GPIO.input(26):
        pixels[8]=(0,0,255)
        pixels.show()
        time.sleep(1)
    else:
        pixels[8]=(0,0,0)
        pixels.show
        time.sleep(1)
    
#ADCS
    if GPIO.input(16):
        pixels[10]=(255,0,255)
        pixels.show()
        time.sleep(1)
    else:
        pixels[10]=(0,0,0)
        pixels.show()
        time.sleep(1)


 
    
