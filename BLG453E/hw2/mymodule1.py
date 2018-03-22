import cv2
import numpy as np
from itertools import chain

def mean_filter(file_name):

	img = cv2.imread(file_name,0)
	rows , cols = img.shape
	kernel_size = 3
	output = img.copy()
	for i in range(rows-kernel_size):
		for j in range(cols-kernel_size):
			window = (img[i:i+kernel_size,j:j+kernel_size])
			window = list(chain.from_iterable(window))
			mean_value = sum(window)/len(window)
			output[i:i+kernel_size,j:j+kernel_size][1][1] = mean_value

	return output

def median_filter(file_name):

	img = cv2.imread(file_name,0)
	rows , cols = img.shape
	kernel_size = 3
	output = img.copy()
	for i in range(rows-kernel_size):
		for j in range(cols-kernel_size):
			window = (img[i:i+kernel_size,j:j+kernel_size])
			window = list(chain.from_iterable(window))
			window.sort()
			output[i:i+kernel_size,j:j+kernel_size][1][1] = window[4]

	return output


def mean_median_filter(file_name, alpha):

	img = cv2.imread(file_name,0)
	rows , cols = img.shape
	kernel_size = 3
	output = img.copy()
	for i in range(rows-kernel_size):
		for j in range(cols-kernel_size):
			window = (img[i:i+kernel_size,j:j+kernel_size])
			window = list(chain.from_iterable(window))
			mean_value = sum(window)/len(window)

			window = (img[i:i+kernel_size,j:j+kernel_size])
			window = list(chain.from_iterable(window))
			window.sort()
			median_value = window[4]
			
			mean_median_value = (alpha * mean_value) + (median_value * (1 - alpha))
			output[i:i+kernel_size,j:j+kernel_size][1][1] = mean_median_value

	return output


def showFunction(label, file_name, output):
	cv2.imshow(label +"_"+ file_name, output)
	cv2.waitKey(0)

def writeFunction(label, file_name, output):
	cv2.imwrite(label +"_"+ file_name, output)