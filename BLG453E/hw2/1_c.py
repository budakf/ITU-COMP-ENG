import cv2
import numpy as np
from itertools import chain
from mymodule1 import *

file_name1 =  "cameramanN1.jpg"
file_name2 =  "cameramanN2.jpg"
file_name3 =  "cameramanN3.jpg"

alpha1 = 0.9
alpha2 = 0.1
alpha3 = 0.5

output1 = mean_median_filter(file_name1, alpha1)	# second parameter is alpha
output2 = mean_median_filter(file_name2, alpha2)
output3 = mean_median_filter(file_name3, alpha3)

showFunction("alpha: " + str(alpha1)+ "_mean_median_filter", file_name1, output1)
showFunction("alpha: " + str(alpha2)+ "_mean_median_filter", file_name2, output2)
showFunction("alpha: " + str(alpha3)+ "_mean_median_filter", file_name3, output3)


#writeFunction("alpha: " + str(alpha1)+ "_mean_median_filter", file_name1, output1)
#writeFunction("alpha: " + str(alpha2)+ "_mean_median_filter", file_name2, output2)
#writeFunction("alpha: " + str(alpha3)+ "_mean_median_filter", file_name3, output3)