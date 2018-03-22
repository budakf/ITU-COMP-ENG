import cv2
import numpy as np

webcam = cv2.VideoCapture(0)		# webcam records
_ , image = webcam.read() 			# captures image
#cv2.imshow("Image", image)  		# displays captured image
cv2.imwrite("Icolor.jpg",image) 	# writes image 
image = cv2.imread('Icolor.jpg')	# reads image

blue = image.copy()					# only blue channel
blue[:, :, 1] = 0
blue[:, :, 2] = 0

green = image.copy()				# only green channel
green[:, :, 0] = 0
green[:, :, 2] = 0

red = image.copy()					# only red channel
red[:, :, 0] = 0
red[:, :, 1] = 0

blue_green = image.copy()			# blue and green channels
blue_green[:,:,2] = 0

blue_red = image.copy()				# blue and red channels
blue_red[:,:,1] = 0

green_red = image.copy()			# green and red channels
green_red[:,:,0] = 0

cv2.imshow('Blue', blue)				# finally all images are displayed 
cv2.imshow('Green', green)				# if you press any key, close all image windows
cv2.imshow('Red', red)
cv2.imshow('Blue+Green', blue_green)
cv2.imshow('Blue+Red', blue_red)
cv2.imshow('Green+Red', green_red)

gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)		# converts color image to gray scale image
cv2.imwrite('Igray.png',gray_image)							# write image to disk
#cv2.imshow('gray_image', gray_image)						# shows image
pixels = []
k = 0
rows, columns = gray_image.shape
for i in range(rows):
	for j in range(columns):
		pixels.insert(k,gray_image[i,j])
		k+=1

print('min value: ', min(pixels))											# minimum pixel value
print('max value: ', max(pixels))											# maximum pixel value


rows, columns, _ = image.shape										# gets rows and columns information
crop_img1 = image[0:rows, 0:int(columns/2),:]						# crops image
crop_img1_1 = image[0:int(rows/2), 0:int(columns/2),:]
crop_img1_2 = image[int(rows/2):rows, 0:int(columns/2),:]

crop_img2 = image[0:rows, int(columns/2):columns,:]
crop_img2_1 = image[0:int(rows/2), int(columns/2):columns,:]
crop_img2_2 = image[int(rows/2):rows, int(columns/2):columns,:]

r1 = np.concatenate((crop_img2_2, crop_img2_1), axis=0)				# combine images
r2 = np.concatenate((crop_img1_2, crop_img1_1), axis=0)
r3 = np.concatenate((r1, r2), axis=1)
reverse = np.concatenate((crop_img2, crop_img1), axis=1)

cv2.imshow("reverse",reverse)										#show images
cv2.imshow("different",r3)

rimage=cv2.flip(image,1)
cv2.imshow("right image",rimage)


cv2.waitKey(0)														# if you press any key, close all image windows




