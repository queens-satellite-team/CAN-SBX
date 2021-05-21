### THIS DOCUMENT IS NOT DONE YET
# Summary 
THis document outlines everything that needs to get done in order to integrate the OBC with the rest of the other subsystems

# Hardware
- Raspberry pi 4 **x1**
- HDMI cord for Raspberry pi 4 **x1**
- Raspberry pi charging cord **x1**
- pi can v1 **x1**
- 15 way ribbon cabble **x1**
- LED ring **x1**
- Gps **x1** (Cal has this at the moment)
- male to male jumper wires **x15**
- conformal coating **x1**

# General OBC integration
- [ ] Set up the balloon.py script to run when the pi is turned on with the master switch to do so follow the steps for the first option in [this link](https://www.dexterindustries.com/howto/run-a-program-on-your-ra

# OBC to ADCS integration
- [ ] connect pin ##### on the Arduino to pin ##### on the Pi 

## GPS to ADCS Integration
### steps  
1. - [ ]  Solder 4 pieses of solid core to the GND, 3.3V, SDA and SCL (legth to be determined by the mech team)
2. - [ ]  Connect 4 wires to the ADCS arduino GND->GND,  3.3V->3.3V,  SDA->SDA, SCL->SCL
3. - [ ]  Integrate the code from the file INSET THE NAME OF THE FILE to ADCS arduino script
- [ ] connect pin ##### on the Arduino to pin ##### on the Pi using one of the male to male jumper wires.
- [ ] Down load the following libratries:
     - SparkFun_I2C_GPS_Arduino_Library.h


# OBC to Power Integration
- [ ] connect pin ##### on the Arduino to pin ##### on the Pi using one of the male to male jumper wires.

 
# OBC to  Payload Integration
- [ ] Set up the the two pi0's scripts to  run when the pi is turned on with the master switch to do so follow the steps for the first option in [this link](https://www.dexterindustries.com/howto/run-a-program-on-your-raspberry-pi-at-startup/)
- [ ] connect pin ##### on the Arduino to pin ##### on the Pi using one of the male to male jumper wires.
- [ ] connect pin ##### on the Arduino to pin ##### on the Pi using one of the male to male jumper wires.


# OBC to Comms Integration
- [ ] connect pin ##### on the Arduino to pin ##### on the Pi using one of the male to male jumper wires.
