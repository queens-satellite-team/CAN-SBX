# QSET HORIZON PAYLOAD CONTROL CODE
# Last updated: July 17 2021 by Kate Szabo kate.szabo@queensu.ca
# This script executes the main control script for the payload for CAN-SBX 2021

import time
import picamera
import datetime as dt
import RPi.GPIO as GPIO
import signal
import os
from pathlib import Path

def handler(sig, frame):
    print("Signal!")
    open('/home/pi/payload_watchdog/temp.dog','a')
    signal.alarm(5)

signal.signal(signal.SIGALRM,handler)
signal.alarm(5)
# WRITE PIN HIGH TO OBC
# Pin setup
GPIO.setmode(GPIO.BCM)
pin_out = 17

# Set up one output pin
GPIO.setup(pin_out, GPIO.OUT)
t_high = dt.datetime.now()
run_timestamp = t_high.strftime('%Y%m%d%H%M%S%f')  # Records timestamp of pin high to sync with OBC
GPIO.output(pin_out, GPIO.HIGH) #Sets pin to 3.3v
os.mkdir(f"/home/pi/CAN-SBX/payload/videos/{run_timestamp}/")

# image dimensions (sets as camera resolution)
iHigh = 1080
iWide = 1920

# Get start time

video_length = 60  # Video length in seconds (3600 = 1 hour)
num_videos = 240  # Number of videos. Note, last video will be corrupted if Pi is powered off before time is up.

# Connect to pi cam and set up
with picamera.PiCamera() as camera:
    camera.resolution = iWide, iHigh
    camera.framerate = 30  # fps
    # time.sleep(2)

    camera.annotate_background = picamera.Color('black')

    for n in range(num_videos):
        t0 = dt.datetime.now()
        file_name = t0.strftime('%Y%m%d%H%M%S')
        file_path = f"/home/pi/CAN-SBX/payload/videos/{run_timestamp}/{file_name}"
        camera.annotate_text = t0.strftime('%H:%M:%S.%f')

        camera.start_recording(f'{file_path}.h264')
        start = dt.datetime.now()
        print("Started")
        while (dt.datetime.now() - start).seconds < video_length:
            camera.annotate_text = dt.datetime.now().strftime('%H:%M:%S.%f')
            camera.wait_recording(0.2)
        camera.stop_recording()
    camera.close()

# WRITE PIN LOW TO OBC
GPIO.output(pin_out, GPIO.LOW) #Sets pin to 0V
GPIO.cleanup()
