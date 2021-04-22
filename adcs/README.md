# CAN-SBX: ADCS DIRECTORY
This directory contains all the software for the CAN-SBX experiment.
To find documentation on the initial (pre-integration) development of this software refer to the Space Engineering Team adcs repository (most recent development done in the master-no-rtos directory under the balloon-dev branch).

# CONTENT

## sbx-adcs/sbx-adcs.ino

Arduino script to continually read data from a BNO055, MPU6050, and GPS and save readings to an onboard SD card. Future development will troubleshoot the GPS and add support for the in-development photodiode matrix on the SBX payload.
