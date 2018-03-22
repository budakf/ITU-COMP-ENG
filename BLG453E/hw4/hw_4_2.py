import numpy as np 
import cv2
import math

def calculateDiff(new, old):
	return (new[0] - old[0]  + new[1] - old[1]) < 0.1


def updateCentroids(centroids, cluster1, cluster2):
	newFirst = newSecond = 0
	for i in cluster1:
		newFirst += i[2]
	newFirst /= len(cluster1)+1

	for i in cluster2:
		newSecond += i[2]
	newSecond /= len(cluster2)+1

	new = [newFirst,newSecond]
	return calculateDiff(new, centroids),  new


def kMeans(I, centroids):
	rows, cols = I.shape
	cluster1 = []
	cluster2 = []
	diff = False
	while not diff:
		first  = centroids[0]
		second = centroids[1]
		for i in range(rows):
			for j in range(cols):
				distanceFromFirst  = abs(I[i,j]  - first)
				distanceFromSecond = abs(I[i,j]  - second)
				if(distanceFromFirst < distanceFromSecond ):
					cluster1.append([i,j,I[i,j]])
				else:
					cluster2.append([i,j,I[i,j]])

		diff, centroids = updateCentroids(centroids, cluster1, cluster2)

	for i in cluster1:
		I[i[0],i[1]] = 150

	for i in cluster2:
		I[i[0],i[1]] = 255
		
	return I

Image = cv2.imread("mr.jpg")
I = cv2.cvtColor(Image,cv2.COLOR_BGR2GRAY)

_, threshold = cv2.threshold(I,50,255,cv2.THRESH_BINARY)
kernel = np.ones((3,3),np.uint8)
mask = cv2.erode(threshold,kernel,iterations = 7)

k = 2
centroids = [150, 255]	#initial_centroids
kmeans = kMeans(I,centroids)
res = cv2.bitwise_and(kmeans, kmeans, mask = mask)

erode    = cv2.erode(res,kernel,iterations = 3)
dilate   = cv2.dilate(erode,kernel,iterations = 1)
boundary = res - dilate
boundary[boundary == 150] = 0
boundary[boundary == 105] = 255

i,j = np.where( boundary == 255)

Image [np.where( boundary == 255)] = [255,0,0]

'''
cv2.imwrite("Mask.jpg", mask)
cv2.imwrite("Kmeans.jpg", res)
cv2.imwrite("BoundaryOfTumor.jpg", boundary)
cv2.imwrite("ResultImage.jpg", Image)
'''

cv2.imshow("mask",mask)
cv2.imshow("kmeans",res)
cv2.imshow("boundaryOfTumor",boundary)
cv2.imshow("Result Image",Image)
cv2.waitKey(0)

