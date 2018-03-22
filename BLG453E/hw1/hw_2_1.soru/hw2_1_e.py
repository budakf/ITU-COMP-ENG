import cv2
import numpy as np 
from math import sqrt


def load_display(file_name):
	exposed = cv2.imread(file_name)
	cv2.imshow("underexposed image",exposed)
	cv2.waitKey(0)
	return exposed

def standard_deviation(channel, channel_mean):
	rows = channel.shape[0]
	cols = channel.shape[1]
	size = channel.size
	sum = 0
	for i in range(rows):
		for j in range(cols):
			sum+=(channel[i,j] - channel_mean)**2

	s = sqrt(sum/size)
	return s

def calculate_mean_and_standard_deviation(expose, size):
	blue,green,red 	= cv2.split(expose)

	mean_of_blue 	= np.sum(blue)/size
	mean_of_green 	= np.sum(green)/size
	mean_of_red 	= np.sum(red)/size

	print("mean_of_blue:", mean_of_blue)
	print("mean_of_green:", mean_of_green)
	print("mean_of_red:", mean_of_red)

	s_blue 	= standard_deviation(blue, mean_of_blue)
	s_green = standard_deviation(green, mean_of_green)
	s_red	= standard_deviation(red, mean_of_red)
	
	print("standard_deviation_blue:", s_blue)
	print("standard_deviation_green:", s_green)
	print("standard_deviation_red:", s_red)


file_name = "new_brigthness_image.jpg"

new_brigthness    = load_display(file_name)
size 	  = (new_brigthness.size)/3 
calculate_mean_and_standard_deviation(new_brigthness,size)
