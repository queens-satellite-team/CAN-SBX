

import numpy as np
import math as m
from picamera import PiCamera
from picamera.array import PiRGBArray
import time

# image dimensions (sets as camera resolution)
iHigh = 1088
iWide = 1920

# Open file
testfile = open("test_results30.txt", "w")

# Get start time
t0 = time.time()
testfile.write("Start: {}/n".format(time.asctime(time.gmtime(t0))))

# Connect to pi cam and set up
camera = PiCamera()
camera.resolution = iWide, iHigh
raw_capture = PiRGBArray(camera, size=(iWide, iHigh))  # Check if height and width arguments are in the right order!

# Set framerate to 1fps
camera.framerate = 30  # fps
time.sleep(0.1)
i = 0

# Stream
camera.resolution = (iWide, iHigh)

camera.start_recording('my_video.h264')
camera.wait_recording(60)
camera.stop_recording()
