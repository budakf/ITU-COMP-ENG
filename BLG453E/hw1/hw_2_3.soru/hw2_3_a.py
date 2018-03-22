import cv2
import numpy as np 
import matplotlib.pyplot as plt
import plotly.plotly as py


normal = cv2.imread("cameraman.jpg")
affine = cv2.imread("cameramanAffine.jpg")

rows,cols,ch = normal.shape

normal_eyes = [251,125]			# determine appropriate point mappings
normal_dirsek = [67,215]		# (corresponding points) between each pair of images.
normal_palto = [46,380]
normal_camera = [337,155]
normal_tri_pod = [409,507]

affine_eyes = [212,134]
affine_dirsek = [114,192]
affine_palto = [155,351]
affine_camera  = [277,169]
affine_tri_pod = [439,498]

points1 = [[251,125],[67,215],[46,380],[337,155],[409,507]]
points2 = [[212,134],[114,192],[155,351],[277,169],[439,498]]

liste = []
for i in range(rows):
	for j in range(cols):
		liste.append([i,j])

normal_array = np.transpose(np.array(liste))

transform_matrix, res, rank, s = np.linalg.lstsq(points1, points2)

x = np.resize(normal_array,(2,2))
x = np.dot(transform_matrix, x)

print(normal_array)
print(transform_matrix)
cv2.imshow("we",x);
cv2.waitKey(0);