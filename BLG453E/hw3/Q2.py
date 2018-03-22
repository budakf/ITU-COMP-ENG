import cv2
import numpy as np
import matplotlib.pyplot as plt

file_name = "cameraman1.jpg"
file_name2 = "cameraman2.jpg"

def sift():

	I = cv2.imread(file_name)
	I2 = cv2.imread(file_name2)

	sift = cv2.xfeatures2d.SIFT_create()
	keyPoints1, descriptor1 = sift.detectAndCompute(I, None)
	keyPoints2, descriptor2 = sift.detectAndCompute(I2, None)

	bfMatcher = cv2.BFMatcher()
	matches = bfMatcher.knnMatch(descriptor1,descriptor2, k=2)

	matchPoints = []
	for i,j in matches:
	    if i.distance < 0.80*j.distance:
	        matchPoints.append([i])

	result = cv2.drawMatchesKnn(I, keyPoints1, I2, keyPoints2, matchPoints, 2)
	plt.imshow(result)
	plt.show()

	return keyPoints1, keyPoints2


keyPoints1, keyPoints2 = sift()

I = cv2.imread(file_name, 0)
rows,cols = I.shape


kPoints1 = [k.pt for k in keyPoints1]
kPoints2 = [k.pt for k in keyPoints2]

kPoints1 = np.float32([[c[0],c[1] ]for c in kPoints1])
kPoints2 = np.float32([[c[0],c[1] ]for c in kPoints2])

M = cv2.getAffineTransform(kPoints1[0:3],kPoints2[0:3])

dst = cv2.warpAffine(I,M,(rows,cols))


print(dst)


