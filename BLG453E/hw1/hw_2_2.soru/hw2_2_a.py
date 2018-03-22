import cv2
import numpy as np 
import matplotlib.pyplot as plt
import plotly.plotly as py

def zeros_dictionary(dictionary):
	for i in range(256):
		dictionary[i] = 0
	return dictionary


def find_frequency(channel, dictionary):
	dictt = zeros_dictionary(dictionary)
	rows  = channel.shape[0]
	cols  = channel.shape[1]
	for i in range(rows):
		for j in range(cols):
			dictt[ channel[i,j] ]+=1

	return dictt

def pdf_plot_hist(listee, name):
	plt.hist(listee[0])
	plt.title("histograms of the "+name + " image BLUE")
	plt.show()
	plt.hist(listee[1])
	plt.title("histograms of the "+name + " image GREEN")
	plt.show()
	plt.hist(listee[2])
	plt.title("histograms of the "+name + " image RED")
	plt.show()


def color_x(file_name):
	
	color_x 			= cv2.imread(file_name)

	blue, green, red 	= cv2.split(color_x)
	size				= color_x.size/3
	
	blue_dict 		= {}
	green_dict 		= {}
	red_dict		= {}

	blue_dict		= find_frequency(blue, blue_dict)
	green_dict		= find_frequency(green, green_dict)
	red_dict		= find_frequency(red, red_dict)

	blue_array 		= np.asarray(list(blue_dict.values()))
	green_array		= np.asarray(list(green_dict.values()) )
	red_array		= np.asarray(list(red_dict.values()) )


#	blue_array = np.cumsum(blue_array)			## Probability Distribution Function
#	green_array = np.cumsum(green_array)
#	red_array = np.cumsum(red_array)

	blue_array		= blue_array/size
	green_array		= green_array/size
	red_array		= red_array/size

	'''print(blue_array)
		print(green_array)
		print(red_array)
	'''

	listee = []
	listee.append(blue_array)
	listee.append(green_array)
	listee.append(red_array)
	return listee
	

file_name_1			= "color1.png"
file_name_2			= "color2.png"


l1 = color_x(file_name_1)
l2 = color_x(file_name_2)

pdf_plot_hist(l1 , "color1")
pdf_plot_hist(l2 , "color2")
