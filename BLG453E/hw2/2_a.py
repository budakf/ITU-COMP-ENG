import cv2
import numpy as np
from itertools import chain
from mymodule1 import *
from mymodule2 import *

file_name = "StairsBuildingsN.png"


outputN  = conv(file_name,N)
showFunction("Direction: N ", file_name, outputN)
#writeFunction("Direction: N ", file_name, outputN)

outputW  = conv(file_name,W)
showFunction("Direction: W ", file_name, outputW)
#writeFunction("Direction: W ", file_name, outputW)

outputS  = conv(file_name,S)
showFunction("Direction: S ", file_name, outputS)
#writeFunction("Direction: S ", file_name, outputS)

outputE  = conv(file_name,E)
showFunction("Direction: E ", file_name, outputE)
#writeFunction("Direction: E ", file_name, outputE)

outputNW = conv(file_name,NW)
showFunction("Direction: NW ", file_name, outputNW)
#writeFunction("Direction: NW ", file_name, outputNW)

outputSW = conv(file_name,SW)
showFunction("Direction: SW ", file_name, outputSW)
#writeFunction("Direction: SW ", file_name, outputSW)

outputNE = conv(file_name,NE)
showFunction("Direction: NE ", file_name, outputNE)
#writeFunction("Direction: NE ", file_name, outputNE)

outputSE = conv(file_name,SE)
showFunction("Direction: SE ", file_name, outputSE)
#writeFunction("Direction: SE ", file_name, outputSE)




