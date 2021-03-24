import cv2 as cv #used to process images
import numpy as np
import math as m
import time

########### Main Program #############


#Load Vedio
vidcap=cv.VideoCapture('at_float.m4v')
count=0
success,image=vidcap.read()
iHigh,iWide,iChannel=image.shape

# Define Parameters
wide=int(iWide/4)
intensityB=np.zeros((iHigh,wide))
intensityR=np.zeros((iHigh,wide))
Mbr=np.zeros(wide)
wid=int(iWide/8)
pair=np.zeros((2,int(wid))) #0 is roll, 1 is pitch
Llx=np.arange(0,wid)
Rrx=np.arange(wid+1,wide)

#save files
trace=open("horizon trace.txt","w")
attitude=open("horizon attitudes.txt","w")

#process all frame
t0=time.time()
while success:


    # split has array of colors (B,G,R) with index 0,1,2
    b,g,r=np.array(cv.split(image))

    #####blur the image

    #Gaussian Blur
    b = cv.GaussianBlur(b,(13,13),0)
    r = cv.GaussianBlur(r,(13,13),0)

    ###### intensity profile

    #get average of the intensity of the 4 pixels
    t1=time.time()
    for x in range(wide):
        intensityB[:,x]=b[:,x*4:(x+1)*4].mean(axis=1)
        intensityR[:,x]=r[:,x*4:(x+1)*4].mean(axis=1)

    #######plot intensity profile and save to image
    br=abs(intensityB-intensityR)

    ####maximums####

    Mbr=np.argmax(br,axis=0)
    traceTime=time.time()-t0

    ### remove outliers
    Lside= np.where(abs(np.flip(Mbr[wid+1:wide]-np.mean(Mbr)))<3*np.std(Mbr),Mbr[0:wid],False)
    Rside=np.where(abs(np.flip(Mbr[0:wid]-np.mean(Mbr)))<3*np.std(Mbr),Mbr[wid+1:wide],False)

    ly=Lside[Lside!= False]
    ry=Rside[Rside!=False]
    lx=Llx[Lside!=False]
    rx=Rrx[Rside!=False]

    #left point (y,dy,x,dx)
    lp=(np.mean(ly),np.std(ly)/np.sqrt(len(ly)),
          np.mean(lx),np.std(lx)/np.sqrt(len(lx)))
    #right point (y,dy,x,dx)
    rp=(np.mean(ry),np.std(ry)/np.sqrt(len(ry)),
          np.mean(rx),np.std(rx)/np.sqrt(len(rx)))
    #### Calculate attitudes####

    #calculate the actual value
    theta=(lp[0]-rp[0])/((lp[2]-rp[2])*4)
    roll=round(180/3.1415926*np.arctan(theta),5)
    pitch=round(((lp[0]+rp[0])/2-iHigh/2)*63/iHigh,5)
    #calculate uncertainty. 'uroll' is the uncertainty of roll, 'upitch' is the uncertainty of pitch
    dtheta=(((lp[1]-rp[1])/(lp[2]-rp[2]))+((rp[3]-lp[3])/(lp[2]-rp[2])**2))/4

    uroll=round(180/3.1415926*(1/(1+theta**2))*dtheta,5)
    upitch=round(63/2/iHigh*(lp[1]+rp[1]),5)
    attitudeTime=time.time()-t0

    ####save files####

    attitude.write("roll={}+-{},pitch={}+-{},time={}\n".format(roll,uroll,pitch,upitch,attitudeTime))
    trace.write("{}, time={} \n\n".format(Mbr,traceTime))

    #end of while loop
    count+=1
    success,image=vidcap.read()

#save to file
attitude.close()
trace.close()
