import cv2
import numpy as np 
import matplotlib.pyplot as plt
import plotly.plotly as py
from PIL import Image

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

def pdf_plot_hist(listee):
	plt.hist(listee[0])
	plt.title("histograms of the underexposed image BLUE")
	plt.show()
	plt.hist(listee[1])
	plt.title("histograms of the underexposed image GREEN")
	plt.show()
	plt.hist(listee[2])
	plt.title("histograms of the underexposed image RED")
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

blue_array = np.cumsum(blue_array)
green_array = np.cumsum(green_array)
red_array = np.cumsum(red_array)

b = np.uint8(255 * blue_array)
g = np.uint8(255 * green_array)
r = np.uint8(255 * red_array)

rows, cols, _ = exposed.shape
new_image = np.zeros_like(exposed)

for i in range(rows):
	for j in range(cols):
		new_image[i, j, 0] = b[exposed[i, j, 0]]
		new_image[i, j, 1] = g[exposed[i, j, 1]]
		new_image[i, j, 2] = r[exposed[i, j, 2]]


cv2.imwrite("new_brigthness_image.jpg",new_image)

blue, green, red 	= cv2.split(new_image)

blue_dict 		= 	find_frequency(blue, {})
blue_array 		=   np.asarray(list(blue_dict.values()))

green_dict 		= 	find_frequency(green, {})
green_array 	=   np.asarray(list(green_dict.values()))

red_dict 		= 	find_frequency(red, {})
red_array 		=   np.asarray(list(red_dict.values()))


plt.plot()
plt.imshow(new_image)
plt.title('Brightness Equalized Image')
plt.show()



listee1 = []
listee1.append(blue_array)
listee1.append(green_array)
listee1.append(red_array)
pdf_plot_hist(listee1)






