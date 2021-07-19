# QSET HORIZON PAYLOAD INTEGRATION README
## Components 
* Raspberry Pi Zero WH
* 32GB MicroSD card
* Pi0 ribbon cable
* Raspberry Pi HQ Camera
* 6mm Wide-Angle c-mount lens

## Build steps
1. Attach lenses to cameras, connect to Pi's with ribbon cable
2. Use USB breakout to connect mouse and keyboard, connect mini-HDMI
3. Connect Pi to power. It will take a while to boot up.
4. Connect to internet, clone and pull CAN-SBX GitHub repository. 
5. Set up pi to automatically run camera code on startup following the instructions for the first method [here](https://www.dexterindustries.com/howto/run-a-program-on-your-raspberry-pi-at-startup/).
Set the path to "/home/pi/CAN-SBX/Payload/PiCamCode.py".
6. Ensure that the cameras are enabled in the raspi-config menu.
7. Focus the camera lenses. Use "raspivid -t 0" to show the camera preview. Turn the camera lenses until they are focused as far away as possible. Exit the preview with Ctrl+C.
## User instructions
1. Ensure all components securely connected
2. Connect Pi0's to power. Everything is automated, they will begin capturing video immediately upon boot. The code that is run is "PiCamCode.py" in the payload folder.