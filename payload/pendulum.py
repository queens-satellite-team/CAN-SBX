#Claire Floras and Grace Jingru Ma, Feb 2021
#Define a function that will take in the length value of the pedulum arm and return the period 
#at which pendulum swings
import numpy as np

#Define variables
g = 9.81 #m/s^2
L = np.arange(9,21,1) #(start, stop, step)
print(L)

#Define function for period
def PFunc(length): #define, name, inputs
    T = 2*np.pi*np.sqrt(length/g)
    return T

print('The range for of the period is:',PFunc(L)) #calling the function