# This program implements Principal Component Analysis on 4 satellite Images and finds 4 principal components.
#import matplotlib.pyplot as plt
import numpy as np
import Image as img

band1 = img.open("band1.gif")
band1Arr = np.array(band1)
band1Arr = band1Arr.flatten()


band2 = img.open("band2.gif")
band2Arr = np.array(band2)
band2Arr = band2Arr.flatten()

band3 = img.open("band3.gif")
band3Arr = np.array(band3)
band3Arr = band3Arr.flatten()

band4 = img.open("band4.gif")
band4Arr = np.array(band4)
band4Arr = band4Arr.flatten()

size = band1Arr.size

mixArray = np.zeros(shape=(size,4))

for i in range(size):
        mixArray[i][0] = band1Arr[i]
        mixArray[i][1] = band2Arr[i]
        mixArray[i][2] = band3Arr[i]
        mixArray[i][3] = band4Arr[i]
#print mixArray
def getNormalized(mixArray):
    m1,m2,m3,m4 = np.mean(mixArray,axis=0)
    #print m1,m2,m3,m4
    l = mixArray.shape
    for i in range(l[0]):
        mixArray[i][0] = mixArray[i][0] - m1
        mixArray[i][1] = mixArray[i][1]-  m2
        mixArray[i][2] = mixArray[i][2] - m3
        mixArray[i][3] = mixArray[i][3] - m4
    return mixArray

normalizedArray = getNormalized(mixArray)

transposed = np.transpose(normalizedArray)
scatterMat = np.dot(transposed,normalizedArray)
covMatrix = scatterMat/normalizedArray.shape[0]
#print covMatrix
values,vectors = np.linalg.eig(covMatrix)
print "\nEignevalues : ",values
print "\nEignevectors : ",vectors
Indices = np.argsort(values)
princEv1 = vectors[Indices[3]]
princEv2 = vectors[Indices[2]]
princEv3 = vectors[Indices[1]]
princEv4 = vectors[Indices[0]]    

def getImageBack(normalizedArray,princEv,name):
    projected = np.dot(normalizedArray,princEv)
    #print projected1
    minimum = np.amin(projected)
    #print minimum,maximum
    projected = projected + abs(minimum)
    minimum = np.amin(projected)   
    #print minimum,maximum
    projected = projected.reshape(512,512)
    im = img.fromarray(projected)
    if im != 'RGB':
        im = im.convert('RGB')
    im.save(name)
getImageBack(normalizedArray,princEv1,"Output\p.gif")
getImageBack(normalizedArray,princEv2,"Output\q.gif")
getImageBack(normalizedArray,princEv3,"Output\s.gif")
getImageBack(normalizedArray,princEv4,"Output\u.gif") 

'''
getImageBack(normalizedArray,princEv1,"Output\A-First.gif")
getImageBack(normalizedArray,princEv2,"Output\B-Second.gif")
getImageBack(normalizedArray,princEv3,"Output\C-Third.gif")
getImageBack(normalizedArray,princEv4,"Output\D-Fourth.gif") '''
print "\nCompleted.See the output directory."
    
    
    
    
    
    
    
    
    
    
    
    
    
    
