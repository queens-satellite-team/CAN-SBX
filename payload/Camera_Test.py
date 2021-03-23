

import numpy as np
import math as m
from picamera import PiCamera
from picamera.array import PiRGBArray
import time

# image dimensions (sets as camera resolution)
iHigh = 1088
iWide = 1920

# Open file
testfile = open("test_results.txt", "w")

# Get start time
t0 = time.time()
testfile.write("Start: {}".format(time.asctime(time.gmtime(t0))))

# Connect to pi cam and set up
camera = PiCamera()
camera.resolution = iWide, iHigh
raw_capture = PiRGBArray(camera, size=(iWide, iHigh))  # Check if height and width arguments are in the right order!

# Set framerate to 1fps
camera.framerate = 20  # fps
time.sleep(0.1)
i = 0

# Stream
for frame in camera.capture_continuous(raw_capture, format='bgr',
                                       use_video_port=True):  # figure out how to do this for a certain amount of time
    i = i + 1
    image = frame.array

    testfile.write("Saving value {} at time {}\n".format(i, time.asctime(time.gmtime(time.time()))))

    raw_capture.truncate(0)
    # if horizon detected well enough
    # break
    if i >= 10:
        break
