#This is a change
import RPi.GPIO as GPIO
import time
import board
import neopixel

GPIO.setmode(GPIO.BCM)
GPIO.setup(5, GPIO.IN)
GPIO.setup(6, GPIO.IN)
GPIO.setup(13, GPIO.IN)
GPIO.setup(19, GPIO.IN)
GPIO.setup(26, GPIO.IN)
GPIO.setup(16, GPIO.IN)
GPIO.setup(18, GPIO.OUT)
pixel_pin = board.D18
 
num_pixels = 12
 
ORDER = neopixel.GRB
 
pixels = neopixel.NeoPixel(
    pixel_pin, num_pixels, brightness=0.4, auto_write=False, pixel_order=ORDER
)
 
 
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


 
    
