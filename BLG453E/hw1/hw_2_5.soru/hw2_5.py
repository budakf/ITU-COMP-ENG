import cv2
import numpy as np
from math import sqrt 
image = cv2.imread("swirl.jpg")

'''
gx = cv2.Sobel(image, cv2.CV_32F, 1, 0)
gy = cv2.Sobel(image, cv2.CV_32F, 0, 1)
weight, angle = cv2.cartToPolar(gx, gy)

print(weight[100])
print(angle[100])

sum_angle  = np.sum(angle)
sum_weight = np.sum(weight)

print(sum_angle)
print(sum_weight)
'''
rows, cols, ch = image.shape
swirl = image.copy()
swirl_y = int(rows/2)
swirl_x = int(cols/2)

for k in range(ch):
	for y in range(rows):
		for x in range(cols):
			pixel_x 	= x - swirl_x
			pixel_y 	= y - swirl_y
			pixel_dist 	= sqrt(pixel_x**2 + pixel_y**2)
			



