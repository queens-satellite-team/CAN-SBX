# PAYLOAD CONTROL CODE
# Last updated: Apr 03 2021 by Kate Szabo
# This script executes the main control script for the payload

from picamera import PiCamera
import time

# WRITE PIN HIGH TO OBC

# image dimensions (sets as camera resolution)
iHigh = 1080
iWide = 1920

# Get start time

video_length = 3600  # Video length in seconds

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
