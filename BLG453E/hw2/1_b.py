import cv2
import numpy as np
from itertools import chain
from mymodule1 import *

file_name1 =  "cameramanN1.jpg"
file_name2 =  "cameramanN2.jpg"
file_name3 =  "cameramanN3.jpg"

output1 = median_filter(file_name1)
output2 = median_filter(file_name2)
output3 = median_filter(file_name3)

showFunction("median_filter", file_name1, output1)
showFunction("median_filter", file_name2, output2)
showFunction("median_filter", file_name3, output3)

#writeFunction("median_filter", file_name1, output1)
#writeFunction("median_filter", file_name2, output2)
#writeFunction("median_filter", file_name3, output3)

