# Acknowledgement : OpenCV tutorial - http://docs.opencv.org/master/d1/db7/tutorial_py_histogram_begins.html#gsc.tab=0
import cv2,numpy as np
from matplotlib import pyplot as plt

img = cv2.imread('1.jpg',0)
print img.shape
cv2.imshow('Image Before Histogram Equalization',img)

hist,bins = np.histogram(img.flatten(),256,[0,256])
#print "hist = ",hist
#print "bins = ",bins
p1 = plt.figure(1)
plt.axis(0,255)
plt.title("Histogram of Input Image Before Applying Equalization")
plt.hist(img.flatten(),255,[0,255])   # img.ravel()
p1.show()

normalHist=[]
a = np.array(hist,dtype=float)
equalHist = np.zeros(256,dtype=float)
height, width = img.shape
total = height*width
normalHist = a/total
equalHist = normalHist.cumsum()
equalHist_m = np.ma.masked_equal(equalHist,0)  # Masking zero intinsity value pixels

#equalHist_m = equalHist_m*255
equalHist_m = (equalHist_m - equalHist_m.min())*255/(equalHist_m.max()-equalHist_m.min())
equalHist = np.ma.filled(equalHist_m,0).astype('uint8')
print "img = ",img
print "equalHist = ",equalHist
equalImage = equalHist[img]
print "equalImage = ",equalImage

cv2.imwrite('EqualizedImage.jpg',equalImage)
cv2.imread('EqualizeImage.jpg',0)
cv2.imshow('Image After Histogram Equalization',equalImage)
p2 = plt.figure(2)
plt.axis(0,255)
plt.title("Histogram of Input Image After Applying Equalization")
plt.hist(equalImage.ravel(),255,[0,255])
p2.show()
