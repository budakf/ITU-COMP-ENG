import cv2
import numpy as np
from itertools import chain

N = np.array([[-3,-3,-3],
			  [-3, 0,-3],
			  [ 5, 5, 5]])

W = np.array([[-3,-3, 5],
			  [-3, 0, 5],
			  [-3,-3, 5]])

S = np.array([[ 5, 5, 5],
			  [-3, 0,-3],
			  [-3,-3,-3]])

E = np.array([[ 5,-3,-3],
			  [ 5, 0,-3],
			  [ 5,-3,-3]])

NW = np.array([[-3,-3,-3],
			   [-3, 0, 5],
			   [-3, 5, 5]])

SW = np.array([[-3, 5, 5],
			   [-3, 0, 5],
			   [-3,-3,-3]])

SE = np.array([[ 5, 5,-3],
			   [ 5, 0,-3],
			   [-3,-3,-3]])

NE = np.array([[-3,-3,-3],
			   [ 5, 0,-3],
			   [ 5, 5,-3]])


def conv(file_name,mask):

	kernel_size = 3
	I = cv2.imread(file_name)
	rows, cols, _ = I.shape
	output = I.copy()
	for i in range(rows-kernel_size):
		for j in range(cols-kernel_size):
			win_blue   = I[:,:,0][i:i+kernel_size,j:j+kernel_size]
			win_green = I[:,:,1][i:i+kernel_size,j:j+kernel_size]
			win_red	  = I[:,:,2][i:i+kernel_size,j:j+kernel_size]

			temp = np.sum(np.multiply(win_blue, mask))
			if temp > 255:
				output[:,:,0][i:i+kernel_size,j:j+kernel_size][1][1] = 255
			elif temp < 0:
				output[:,:,0][i:i+kernel_size,j:j+kernel_size][1][1] = 0
			else:
				output[:,:,0][i:i+kernel_size,j:j+kernel_size][1][1] = temp

			temp = np.sum(np.multiply(win_green, mask))
			if temp > 255:
				output[:,:,1][i:i+kernel_size,j:j+kernel_size][1][1] = 255
			elif temp < 0:
				output[:,:,1][i:i+kernel_size,j:j+kernel_size][1][1] = 0
			else:
				output[:,:,1][i:i+kernel_size,j:j+kernel_size][1][1] = temp

			temp = np.sum(np.multiply(win_red, mask))
			if temp > 255:
				output[:,:,2][i:i+kernel_size,j:j+kernel_size][1][1] = 255
			elif temp < 0:
				output[:,:,2][i:i+kernel_size,j:j+kernel_size][1][1] = 0
			else:
				output[:,:,2][i:i+kernel_size,j:j+kernel_size][1][1] = temp

	return output