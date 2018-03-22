import cv2
import numpy as np 

def rotate(image, angle, center ,scale = 1.0):
    (height, width) = image.shape[:2]

    M = cv2.getRotationMatrix2D(center, angle, scale)
    rotated = cv2.warpAffine(image, M, (width, height))

    return rotated

def compute_new_location(height, width):
	new_h = height+1
	new_w = width+1



image = cv2.imread("anka.jpg")
height, width, _ = image.shape
'''
for i in range(height):
	for j in range(width):
compute_new_location(height, width)
'''


rotated_1 = rotate(image, -30, (height/2, width/2))
rotated_2 = rotate(image, -30, (0, 0))

cv2.imshow("rotated1.png",rotated_1)
cv2.imshow("rotated2.png",rotated_2)
cv2.imshow("original.png",image)
cv2.waitKey(0)