from numpy import random,argsort
from pylab import plot,show,clf
from math import sqrt
NumOfPoints = input("\nHow many random data points do you want to generate in [0,1] ?\n")
#NumOfPoints = 100
K = input("Enter the value of K (size of neighbourhood)\n")
#K = 5 
x = random.rand(2,1) # Generates two dimesnsional query point
choice = input("How do you want to generate query point : \n1. Input from keyboard or \n2. Randomly\n")
if choice == 1:
    print "Enter a two dimensional query point :"
    x[0][0] = raw_input()
    x[1][0] = raw_input()
    print "Entered query point is : ","[",x[0][0],",",x[1][0],"]"
else :
    print "Randomly generated query point is : ","[",x[0][0],",",x[1][0],"]"
# Function to calculate euclidian distance bw any two points.
def euclidDist(p,x):
    t1 = p[0]-x[0]
    t2 = p[1]-x[1]
    dist = sqrt(t1*t1 + t2*t2)
    return dist
   
def knn(queryPoint, D, K):
 """ find K nearest neighbours of data among D """
 ndata = D.shape[1]  # To get number of data points(#columns)..ndata is number of data points.
 if K >= ndata :
    K = ndata   
 # Calculating euclidean distances of query point from other points
 sqd = [] # To store all the distances.
 for i in range(0,ndata):
     dataPoint = (D[0][i],D[1][i])
     dist = euclidDist(dataPoint,queryPoint) 
     sqd.append(dist)
 idx = argsort(sqd) # argsort returns the indices which sort the array.
 # return the indices of K nearest neighbours
 neightList= []  # To store the indices of K nearest neighbours.
 for i in range(0,K):
     neightList.append(idx[i])
 return neightList

 

#knn_search test
data = random.rand(2,NumOfPoints) # random dataset
#print data
x01 = [] # To hold the first dimension of class 0
x02 = [] # To hold the second dimension of class 0
x11 = [] # To hold the first dimension of class 1
x12 = [] # To hold the second dimension of class 0

for i in range(0,NumOfPoints):
    if data[0][i] >= data[1][i] :  # x1 >= x2 -> Class 0
        x01.append(data[0][i])
        x02.append(data[1][i])
    else :  # x1 < x2 -> Class 1
        x11.append(data[0][i])
        x12.append(data[1][i])
        
clf()
# performing the search
neig_idx = knn(x,data,K)

# plotting the data and the query point
plot(x01,x02,'bo',x[0,0],x[1,0],'or')  # Plotting points of Class 0 by blue
plot(x11,x12,'ro',x[0,0],x[1,0],'or')  # Plotting points of Class 1 by Red
plot(x[0,0],x[1,0],'go')               # Plotting the query point by green
# highlighting the neighbours by circles
plot(data[0,neig_idx],data[1,neig_idx],'o',markerfacecolor='None',markersize=10,markeredgewidth=1)

c0 = 0
c1 = 0 
for i in neig_idx :
    if data[0][i] > data[1][i] : # This neighbor belongs to class 0 (Blue)
        c0 = c0 + 1
    else:                        # This neighbor belongs to class 1 (Red)
        c1 = c1 + 1
if c0 > c1:
    print "Query point is classified in class = 0 (Blue)"
else :
    print "Query point is classified in class = 1 (Red)"

show()
