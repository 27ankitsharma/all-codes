'''
This program implements single layer perceptron in Python.
It generates 2-dim data using multivariate normal distribution.
Author : Ankit Sharma
Indian Statistical Institute, Kolkata
For any query contact : 27ankitsharma@gmail.com
'''

import numpy as np
import matplotlib.pyplot as plt

class Perceptron:
    def __init__(self):
        self.w = np.random.uniform(low=0.0, high = 1.0,size = 3) # Initializing weight vector randomly
        self.eta = 0.01  # Learning rate
        print "\nInitial random weights are : ",self.w
        
    def Training(self,TrainingData,maxItr):
        itr = 0
        globalErr = 10
        while globalErr != 0 and itr <=maxItr:
            #print "Iteration  = ",itr
            globalErr = 0
            missed = 0
            for point in TrainingData:
                classlabel = point[1]
                # Computing activation by dot product of weight and input feature vector
                activation = self.w[0]*1 + self.w[1]*point[0][0] + self.w[2]*point[0][1]
                signal = self.sign(activation)
                if signal != classlabel : # Missclassification so update weights
                    err = classlabel - signal  # This err can be either 1 or -1
                    missed += 1 
                    globalErr += abs(err)
                    #print "missed now are ",missed
                    self.w[0] = self.w[0] + self.eta*err*1
                    self.w[1] = self.w[1] + self.eta*err*point[0][0]
                    self.w[2] = self.w[2] + self.eta*err*point[0][1]     
            itr += 1
            
        print "\nNo of Iterations taken in convergence = ",itr   
        print "After convergence weights are : ",self.w
        print "Missclassifications in the last epoch are = ",missed
        
                    
    # Method for obtaining sign of activation   
    def sign(self,activation) :
        if activation >  0:  # Input point belongs to class 1
            return 1
        else:
            return 0  # Input point belongs to class 1
            
    def Test(self,TestData):
        confusionMat = np.zeros((2,2))
        for point in TestData:
                actuallabel = point[1]         
                # Computing activation by dot product of weight and input feature vector
                activation = self.w[0]*1 + self.w[1]*point[0][0] + self.w[2]*point[0][1]
                predictedlabel = self.sign(activation)
                if  (actuallabel != predictedlabel) : # Missclassification so update confusion matrix.
                    confusionMat[actuallabel][predictedlabel] += 1   
                else : # Correct classification
                    confusionMat[actuallabel][actuallabel] += 1 
        return confusionMat
        
def generate_points(c1,c2,mean1,mean2,cov1,cov2):
    data1 = np.random.multivariate_normal(mean1,cov1,c1) 
    class0 = [[x,0] for x in data1]
    #print class0
    data2 = np.random.multivariate_normal(mean2,cov2,c2)
    class1 = [[x,1] for x in data2]
    #print class1
    data = np.concatenate((class0,class1),axis = 0) 
    np.random.shuffle(data) 
    return data1,data2,data
    
 
''' Training of Perceptron  '''
maxItr = 100
c0 = 100 # Number of points for class 0
c1 = 100 # Number of points for class 1
mean1 = [0,0]  # Mean for class0 for both dimensions
mean2 = [2,2]  # Mean for class1 for both dimensions
cov1 = [[.4,0],[0,.1]]
cov2 = [[.1,0],[0,.3]]
data1,data2,Trainingdata = generate_points(c0,c1,mean1,mean2,cov1,cov2)
# Plotting training data
plt.figure(0)
plt.title("Training Data Plot")
plt.xlabel("Feature 1")
plt.ylabel("Feature 2")
plt.plot(data1[:,:1],data1[:,1:2],'o',color= 'b')
plt.plot(data2[:,:1],data2[:,1:2],'o',color= 'g')

percept = Perceptron()
percept.Training(Trainingdata,maxItr)
w = percept.w
m = -(w[1] / w[2])  # Calculating slope for line
c = -(w[0] / w[2])  # Calculating intercept on y-axis for line
x = np.array([-4,6])
plt.axis([-5,10,-5,10])
plt.plot(x,m*x+c)  # Plotting line



''' Testing Perceptron  '''
c0 = 50
c1 = 50
data1,data2,Testdata = generate_points(c0,c1,mean1,mean2,cov1,cov2)

# Plotting Test data
plt.figure(1)
plt.xlabel("Feature 1")
plt.ylabel("Feature 2")
plt.plot(data1[:,:1],data1[:,1:2],'o',color= 'b')
plt.plot(data2[:,:1],data2[:,1:2],'o',color= 'g')
plt.axis([-5,10,-5,10])
plt.plot(x,m*x+c)  # Plotting line
plt.title("Test Data Plot")

confusionMatrix = percept.Test(Testdata)
print "\nConfusion matrix over Test data is : ",confusionMatrix
 