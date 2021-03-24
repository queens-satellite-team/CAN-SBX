# PAYLOAD CONTROL CODE
# Last updated: March 16 2021 by Kate Szabo
# This script executes the main control loop for the payload

import cv2 as cv  # used to process images
import numpy as np
import math as m
from picamera import PiCamera
from picamera.array import PiRGBArray
import time

# image dimensions (sets as camera resolution)
iHigh = 1088
iWide = 1920

# init parameters
wide = int(iWide / 4)
intensityB = np.zeros((iHigh, wide))
intensityR = np.zeros((iHigh, wide))
Mbr = np.zeros(wide)
wid = int(iWide / 8)
pair = np.zeros((2, int(wid)))  # 0 is roll, 1 is pitch

# Get start time
t0 = time.time()


# FUNCTIONS

def calc_attitude(image):
    # calculate attitude values for one frame

    # split has array of colors (B,G,R) with index 0,1,2
    b, g, r = np.array(cv.split(image))

    ##### blur the image

    # Gaussian Blur
    b = cv.GaussianBlur(b, (13, 13), 0)
    r = cv.GaussianBlur(r, (13, 13), 0)

    ###### intensity profile

    # get average of the intensity of the 4 pixels
    t1 = time.time()
    for x in range(wide):
        intensityB[:, x] = b[:, x * 4:(x + 1) * 4].mean(axis=1)
        intensityR[:, x] = r[:, x * 4:(x + 1) * 4].mean(axis=1)

    #######plot intensity profile and save to image
    br = abs(intensityB - intensityR)

    ####maximums####

    Mbr = np.argmax(br, axis=0)
    trace_time = time.time() - t0

    #### Calculate attitudes####
    # calculate the roll:
    for i in range(wid):
        dy = Mbr[i] - Mbr[-(i + 1)]
        dmy = Mbr[i] + Mbr[-(i + 1)]
        pair[0, i] = 180 / 3.1415926 * np.arctan(dy / ((wid - i) * 4))
        pair[1, i] = (dmy / 2 - iHigh / 2) * 63 / iHigh

    # remove outliers
    cleanRoll = pair[0, abs(pair[0] - np.mean(pair[0])) < 2 * np.std(pair[0])]
    cleanPitch = pair[1, abs(pair[1] - np.mean(pair[1])) < 2 * np.std(pair[1])]

    roll = np.mean(cleanRoll)
    stdRoll = np.std(cleanRoll) / m.sqrt(len(cleanRoll))
    pitch = np.mean(cleanPitch)
    stdPitch = np.std(cleanPitch) / m.sqrt(len(cleanPitch))
    attitudeTime = time.time() - t0

    return roll, stdRoll, pitch, stdPitch, attitudeTime


# Connect to pi cam and set up
camera = PiCamera()
try:
    camera.resolution = iWide, iHigh
    raw_capture = PiRGBArray(camera, size=(iWide, iHigh))  # Check if height and width arguments are in the right order!

    # Open file
    attitude = open("horizon_attitudes.txt", "w")

    # Set framerate to 1fps
    camera.framerate = 1  # fps
    time.sleep(0.1)
    i = 0

    # Stream
    for frame in camera.capture_continuous(raw_capture, format='bgr', use_video_port=True): # figure out how to do this for a certain amount of time
        i = i + 1
        image = frame.array
        roll, stdRoll, pitch, stdPitch, attitudeTime = calc_attitude(image)
        attitude.write("roll= {}+-{},pitch={}+-{},time={}\n".format(roll, stdRoll, pitch, stdPitch, attitudeTime))
    
        raw_capture.truncate(0)
        # if horizon detected well enough
        # break
        if i >= 10:
            break
    pass
finally:
    camera.close()
