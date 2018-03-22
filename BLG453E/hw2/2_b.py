import cv2
import numpy as np
from itertools import chain
from operator import itemgetter
from mymodule1 import *
from mymodule2 import *

file_name = "StairsBuildingsN.png"
all_magnitude = []

outputN  = conv(file_name,N)
outputW  = conv(file_name,W)
outputS  = conv(file_name,S)
outputE  = conv(file_name,E)
outputNW = conv(file_name,NW)
outputSW = conv(file_name,SW)
outputNE = conv(file_name,NE)
outputSE = conv(file_name,SE)

all_magnitude.append( (outputN,  np.sum(outputN)  ,"North") )
all_magnitude.append( (outputW,  np.sum(outputW)  ,"West")  )
all_magnitude.append( (outputS,  np.sum(outputS)  ,"South") )
all_magnitude.append( (outputE,  np.sum(outputE)  ,"East")  )
all_magnitude.append( (outputNW, np.sum(outputNW) ,"NorthWest"))
all_magnitude.append( (outputSW, np.sum(outputSW) ,"SouthWest"))
all_magnitude.append( (outputNE, np.sum(outputNE) ,"NorthEast"))
all_magnitude.append( (outputSE, np.sum(outputSE) ,"SouthEast"))

Jmag, magnitude, direction = max(all_magnitude,key=itemgetter(1))[:]

print("Direction:", direction)

_, threshold_image = cv2.threshold(Jmag, 0, 255, cv2.THRESH_BINARY)

cv2.imshow("Jmag",Jmag)
cv2.imshow("Threshold_Jmag",threshold_image)
cv2.waitKey(0)

#cv2.imwrite("Jmag.jpg", Jmag)
#cv2.imwrite("Threshold_Jmag.jpg", threshold_image)


