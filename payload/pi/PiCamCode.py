# PAYLOAD CONTROL CODE
# Last updated: Apr 03 2021 by Kate Szabo
# This script executes the main control script for the payload

from picamera import PiCamera
import time
import RPi.GPIO as GPIO

# WRITE PIN HIGH TO OBC
# Pin setup
GPIO.setmode(GPIO.Board)

# Set up one output pin
GPIO.setup(0, GPIO.out)
GPIO.output(0, GPIO.HIGH) #Sets pin to 3.3v

# image dimensions (sets as camera resolution)
iHigh = 1080
iWide = 1920

# Get start time

video_length = 10  # Video length in seconds

# Connect to pi cam and set up
camera = PiCamera()
try:
    camera.resolution = iWide, iHigh
    camera.framerate = 30  # fps
    time.sleep(2)

    t0 = time.time()
    time_str = time.strftime("%Y%m%d%H%M%S", time.localtime(t0))

    camera.start_recording(f'time_str.h264')
    camera.wait_recording(video_length)
    camera.stop_recording()

finally:
    camera.close()

# WRITE PIN LOW TO OBC
GPIO.output(0, GPIO.LOW) #Sets pin to 0V


