from math import sqrt 
import operator,pickle,sys
def readFile(f):
    tmpUser = -15
    user_movie = {} 
    movieCount = 0
    ratedMovies = {}
    sumOfRatingsPerUser = 71568 * [0]  #71568
    sumOfRating = 0   # So that we can calculate average rating easily for each user.
    for line in f.xreadlines():
        strList = line.split("::")
        userNo = int(strList[0])
        movieId = int(strList[1])
        rating = float(strList[2])
        print "user,movie : ",userNo,movieId
        if user_movie.has_key(userNo):  # Same user
            movieCount += 1
            ratedMovies[movieId] = rating
            sumOfRating = sumOfRating + rating
            sumOfRatingsPerUser[userNo] = sumOfRating           
            user_movie[userNo] = ratedMovies      
        else : # Different user(first time occurring)
            if movieCount != 0 :
                sumOfRatingsPerUser[tmpUser] = sumOfRatingsPerUser[tmpUser]/movieCount
            movieCount = 1 
            ratedMovies = {}
            sumOfRating = rating
            sumOfRatingsPerUser[userNo] = sumOfRating
            ratedMovies[movieId] = rating
            user_movie[userNo] = ratedMovies
            tmpUser = userNo
    return user_movie,sumOfRatingsPerUser
      
def similarity(u1,u2,rm1,rm2,avgOfRatingsPerUser):
        #print "rm1=",rm1
        #n1 = len(rm1.keys())
        avg1 = avgOfRatingsPerUser[u1]
       
        #n2 = len(rm2.keys())
        avg2 = avgOfRatingsPerUser[u2]
        numerator = 0
        den1 = 0
        den2 = 0
        sim = 0
        for movie in rm1 :
            if rm2.has_key(movie):
                numerator += (rm1[movie]-avg1) * (rm2[movie] - avg2)               
        for movie in rm1 :
            tmp = rm1[movie]-avg1
            den1 += tmp*tmp        
        for movie in rm2 :
            tmp = rm2[movie]-avg2
            den2 += tmp*tmp
        #print "user1=",u1,"user2=",u2, # "den1 = ",den1,"den2 = ",den2
        #print "sumOfRatingsPerUser[u1]=",sumOfRatingsPerUser[u1],
        
        #print "avg1=",avg1,"avg2=",avg2
        if den1==0 or den2 == 0 :
            sim = 1
            '''print "For u1 and u2=",u1,u2
            print "From sim==1,den1,den2",den1,den2
            sys.stdin.read(1) '''
            return sim

        sim = numerator / sqrt(den1 * den2)
        #sys.stdin.read(1) 
        return sim
    
# Function to sort the similar user to a particular user in decreasing order
# and then returning top K similar users.
def sortBySimilarity(similarusersDict,K):
    sortedByValue = sorted(similarusersDict.items(),key=operator.itemgetter(1),reverse=True)
    topKSimilarUsersList = sortedByValue[:K]
    return topKSimilarUsersList
  
def predictRating(targetUser,targetMovie,user_Movie,topKSimilarUsers,avgRatingPerUser):
    neighOfTargetUser = topKSimilarUsers
    numerator = 0
    denominator = 0
    print "TargetUser = ",targetUser,
    print ", TargetMovie = ",targetMovie
    #print "avgRatingPerUser[targetUser] = ",avgRatingPerUser[targetUser]
    for neigh in neighOfTargetUser :
        nghbor = neigh[0]
        denominator += abs(neigh[1]) 
        nghborMovieList = user_Movie[nghbor]
        if nghborMovieList.has_key(targetMovie):
            ratingForTargetMovie = nghborMovieList[targetMovie]
            avgRatingofNghbr = avgRatingPerUser[nghbor]
            diff = ratingForTargetMovie - avgRatingofNghbr
            print "diff=",diff,
            sim = neigh[1]
            numerator += sim * diff
    if(denominator == 0):
        tmp = avgRatingPerUser[targetUser]
        #print "denominator = 0"
        return tmp
    print "numerator,denominator=",numerator, denominator,
    tmp = numerator / denominator
    print "tmp=",tmp
    sys.stdin.read(1) 
    predictedRating = avgRatingPerUser[targetUser] +tmp
    return  predictedRating
    
def writeIntoFile(f_predicted,TargetUser,TargetMovieId,predictedRating,timestamp) :
     userNo = strList[0]
     movieId = strList[1]
     predictedRating = predictedRating.__str__()
     tmp = userNo + "::"+ movieId + "::" + predictedRating +"::" + timestamp 
     #print tmp,"is written."
     #print "Predicted for user,movie :",TargetUser,TargetMovieId
     f_predicted.write(tmp)
 
   
#f1 = open("movie_ratings_incomplete.dat",'r')
#f1 = open("Training.dat",'r')
print "1 is in progress...."
#tup = readFile(f1)


file_Name = "testfile"

'''fileObject = open(file_Name,'wb') 
print "Object is being pickled.."
pickle.dump(tup,fileObject)   
fileObject.close() 
print "Pickeling is done.." '''

print "Object is being loaded.."
fileObject = open(file_Name,'r')  
tup = pickle.load(fileObject)
print "Object has been loaded..."

user_Movie = tup[0]
avgRatingsPerUser = tup[1]
print "1 is done."

f2 = open("movie_ratings_blanks.dat",'r') 
#f2 = open("Test.dat",'r')  
f_predicted = open("Output.dat",'w')  # Output file
similarusersDict = {}
K = 5
print "Wait while predicted ratings are being written...."
PrevUser = -10 # Any arbitrary number which is not a valid userId
for line in f2.xreadlines():
        strList = line.split("::")
        TargetUser = int(strList[0])
        TargetMovieId = int(strList[1])
        timestamp = strList[3]
        #print "For user,Movie",TargetUser,TargetMovieId
        #avgRatingPerUser = sumOfRatingsPerUser
        topKsimilarUsers = []
        if(PrevUser != TargetUser) : # New Target user
            PrevUser = TargetUser
            targetUserMovieVector = user_Movie[TargetUser] 
            for user in user_Movie :
                 otherUserMovievector  = user_Movie[user]
                 sim= similarity(TargetUser,user,targetUserMovieVector,otherUserMovievector,avgRatingsPerUser)
                 similarusersDict[user] = sim
                 
            topKsimilarUsers = sortBySimilarity(similarusersDict,K)
            predictedRating = predictRating(TargetUser,TargetMovieId,user_Movie,topKsimilarUsers,avgRatingsPerUser)
            writeIntoFile(f_predicted,TargetUser,TargetMovieId,predictedRating,timestamp)        
        else : # Target user is same but target movie is different.
            predictedRating = predictRating(TargetUser,TargetMovieId,user_Movie,topKsimilarUsers,avgRatingsPerUser)
            writeIntoFile(f_predicted,TargetUser,TargetMovieId,predictedRating,timestamp)
        
        
'''
1. Denominator is zero : When a user has given same rating to all the rated movies..(r-ravg)
'''
