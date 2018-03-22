import cv2
import numpy as np 
import matplotlib.pyplot as plt
import plotly.plotly as py

def zeros_dictionary(dictionary):
	for i in range(256):
		dictionary[i] = 0
	return dictionary

def pdf(dictionary, size):
	for i in range(256):
		dictionary[i]/=size

	return dictionary

def find_frequency(channel, dictionary):
	dictt = zeros_dictionary(dictionary)
	rows  = channel.shape[0]
	cols  = channel.shape[1]
	size  = channel.size
	for i in range(rows):
		for j in range(cols):
			dictt[ channel[i,j] ]+=1

	return pdf(dictt, size)

def pdf_plot_hist(listee,name):
	plt.hist(listee[0])
	plt.title(name+" histograms of the underexposed image BLUE")
	plt.show()
	plt.hist(listee[1])
	plt.title(name+" histograms of the underexposed image GREEN")
	plt.show()
	plt.hist(listee[2])
	plt.title(name+" histograms of the underexposed image RED")
	plt.show()


file_name 			= "underexposed.jpg"
exposed 			= cv2.imread(file_name)

blue, green, red 	= cv2.split(exposed)

blue_dict 		= {}
green_dict 		= {}
red_dict		= {}

blue_dict		= find_frequency(blue, blue_dict)
green_dict		= find_frequency(green, green_dict)
red_dict		= find_frequency(red, red_dict)

blue_array 		= np.asarray(list(blue_dict.values()))
green_array		= np.asarray(list(green_dict.values()) )
red_array		= np.asarray(list(red_dict.values()) )


listee 	= []

name = "PDF"
listee.append(blue_array)
listee.append(green_array)
listee.append(red_array)
pdf_plot_hist(listee,name)

blue_array = np.cumsum(blue_array)
green_array = np.cumsum(green_array)
red_array = np.cumsum(red_array)


print(blue_array)
print(green_array)
print(red_array)

name = "CDF"
listee1 = []
listee1.append(blue_array)
listee1.append(green_array)
listee1.append(red_array)
pdf_plot_hist(listee1,name)