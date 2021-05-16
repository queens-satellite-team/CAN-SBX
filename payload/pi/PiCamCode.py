# PAYLOAD CONTROL CODE
# Last updated: Apr 03 2021 by Kate Szabo
# This script executes the main control script for the payload

from picamera import PiCamera
import datetime as dt
import RPi.GPIO as GPIO

# WRITE PIN HIGH TO OBC
# Pin setup
GPIO.setmode(GPIO.BCM)

# Set up one output pin
GPIO.setup(0, GPIO.OUT)
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
    # time.sleep(2)

    camera.annotate_background = picamera.Color('black')
    camera.annotate_text = dt.datetime.now().strftime('%H:%M:%S.%f')

    camera.start_recording(f'{time_str}.h264')
    start = dt.datetime.now()
    while (dt.datetime.now() - start).seconds < video_length:
        camera.annotate_text = dt.datetime.now().strftime('%H:%M:%S.%f')
        camera.wait_recording(0.2)
    camera.stop_recording()

finally:
    camera.close()

# WRITE PIN LOW TO OBC
GPIO.output(0, GPIO.LOW) #Sets pin to 0V
GPIO.cleanup()
