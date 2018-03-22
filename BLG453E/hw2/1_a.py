import cv2
import numpy as np
from itertools import chain
from mymodule1 import *

file_name1 =  "cameramanN1.jpg"
file_name2 =  "cameramanN2.jpg"
file_name3 =  "cameramanN3.jpg"

output1 = mean_filter(file_name1)
output2 = mean_filter(file_name2)
output3 = mean_filter(file_name3)

showFunction("mean_filter", file_name1, output1)
showFunction("mean_filter", file_name2, output2)
showFunction("mean_filter", file_name3, output3)

#writeFunction("mean_filter", file_name1, output1)
#writeFunction("mean_filter", file_name2, output2)
#writeFunction("mean_filter", file_name3, output3)