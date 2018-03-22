import cv2
import numpy as np
import math
import matplotlib.pyplot as plt

file_name = "Fig2wirebond_mask.jpg"
file_name2 = "Fig3bottles.jpg"

kernel_size = 3
sigma = 10		#0.5 1 3 
t = 30


def non_maximum(Edges, Magnitude, gy, t):
	rows, cols = Edges.shape
	for i in range(rows):
		for j in range(cols):
			if Magnitude[i,j] > t:
				if ((j+1) < cols) and ((j-1) > 0) and ((i+1) < rows) and ((i-1) > 0):
					if ( gy[i][j] > 337.5 or gy[i][j] < 22.5) or (gy[i][j] > 157.5 and gy[i][j] < 202.5):
						if Magnitude[i][j] > Magnitude[i][j + 1] and Magnitude[i][j] > Magnitude[i][j - 1]:
							Edges[i][j] = 255
					elif (gy[i][j] > 22.5 and gy[i][j] < 67.5) or (gy[i][j] > 202.5 and gy[i][j] < 247.5):
						if Magnitude[i][j] > Magnitude[i - 1][j + 1] and Magnitude[i][j] > Magnitude[i + 1][j - 1]:
							Edges[i][j] = 255
					elif (gy[i][j] > 67.5 and gy[i][j] < 112.5) or (gy[i][j] > 247.5 and gy[i][j] < 292.5):
						if Magnitude[i][j] > Magnitude[i - 1][j] and Magnitude[i][j] > Magnitude[i + 1][j]:
							Edges[i][j] = 255
					elif (gy[i][j] > 112.5 and gy[i][j] < 157.5) or (gy[i][j] > 292.5 and gy[i][j] < 337.5):
						if Magnitude[i][j] > Magnitude[i - 1][j - 1] and Magnitude[i][j] > Magnitude[i + 1][j + 1]:
							Edges[i][j] = 255


	return Edges

def gradient(J):

	rows, cols = J.shape
	gx = np.zeros(J.shape)
	gy = gx
	for i in range(rows):
		for j in range(cols):
			if i+1 < rows and i-1 >= 0:
				gx[i,j] = (int(J[i+1,j]) - int(J[i-1,j])) / 2
			if j+1 < cols and j-1 >= 0:
				gy[i,j] = (int(J[i,j+1]) - int(J[i,j-1])) / 2

	return gx,gy

def canny(file_name,sigma,t):
	I = cv2.imread(file_name,0)
	rows, cols = I.shape
	J = cv2.GaussianBlur(I,(5,5),sigma)
	gx, gy = gradient(J)  		
	Magnitude = np.ones(J.shape)
	alpha = np.ones(J.shape)
	Edges = np.zeros(I.shape)
	for i in range(rows):
		for j in range(cols):
			Magnitude[i,j] 	= math.sqrt((gx[i,j]**2) + (gy[i,j]**2))
			alpha[i,j]  = math.atan2(gy[i,j],gx[i,j])

	Edges = non_maximum(Edges, Magnitude, gy, t)
	return Edges,Magnitude,alpha


def threshold(Magnitude):
	_,threshold1 = cv2.threshold(Magnitude,127,255,cv2.THRESH_BINARY)
	cv2.imshow("threshold1", threshold1)


def function():
	Edges, Magnitude, alpha = canny(file_name, sigma, t)
	cv2.imwrite("sigma:"+str(sigma)+"_"+file_name[:-4]+"_Edges.jpg",Edges)
	cv2.imwrite("sigma:"+str(sigma)+"_"+file_name[:-4]+"_Magnitude.jpg",Magnitude)
	cv2.imwrite("sigma:"+str(sigma)+"_"+file_name[:-4]+"_Alpha.jpg",alpha)

	Edges, Magnitude, alpha = canny(file_name2, sigma, t)
	cv2.imwrite("sigma:"+str(sigma)+"_t:"+str(t)+"_"+file_name2[:-4]+"_Edges.jpg",Edges)
	cv2.imwrite("sigma:"+str(sigma)+"_t:"+str(t)+"_"+file_name2[:-4]+"_Magnitude.jpg",Magnitude)
	cv2.imwrite("sigma:"+str(sigma)+"_t:"+str(t)+"_"+file_name2[:-4]+"_Alpha.jpg",alpha)

def function2(p_file_name):
	I = cv2.imread(p_file_name,0)
	rows, cols = I.shape
	gx, gy = gradient(I)
	Magnitude = np.ones(I.shape)

	for i in range(rows):
		for j in range(cols):
			Magnitude[i,j] 	= math.sqrt((gx[i,j]**2) + (gy[i,j]**2))

	threshold(Magnitude)



def callBuiltinCannyEdgeDetection(p_file_name):
	I = cv2.imread(p_file_name,0)
	edges = cv2.Canny(I,100,200)
	cv2.imshow("CannyEdgeDetection", edges)


function()

function2(file_name)
callBuiltinCannyEdgeDetection(file_name)
cv2.waitKey(0)

print("To skip this image, use ENTER key")

function2(file_name2)
callBuiltinCannyEdgeDetection(file_name2)
cv2.waitKey(0)

print("To skip this image, use ENTER key")


print("Other images are saved to folder")
















'''
y, x = np.mgrid[0:cols:500j, 0:rows:500j]
skip = (slice(None, None, 1), slice(None, None, 1))

fig, ax = plt.subplots()
im = ax.imshow(I, extent=[x.min(), x.max(), y.min(), y.max()])
ax.quiver(x[skip], y[skip], gx[skip], gy[skip])

ax.set(aspect=1, title='Quiver Plot')
plt.show()




plt.close("all")
plt.figure()
plt.suptitle("Image, and it gradient along each axis")
ax = plt.subplot("131")
ax.axis("off")
ax.imshow(J)
ax.set_title("image")

ax = plt.subplot("132")
ax.axis("off")
ax.imshow(gx)
ax.set_title("gx")

ax = plt.subplot("133")
ax.axis("off")
ax.imshow(gy)
ax.set_title("gy")
plt.show()
'''