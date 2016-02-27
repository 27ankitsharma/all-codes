import math
def createDict (filename):
		wordCount = 0.0
		mydict = {}
		with open(filename,'r') as f:
			for line in f:
				wordList = line.split()
				for word in wordList:
					wordCount += 1 
					word = ''.join(i for i in word if i.isalpha())
					word = word.lower()
					if mydict.has_key(word):
						mydict[word] += 1
					else :
						mydict[word] = 1
		for key in mydict :
			mydict[key] = mydict[key]/wordCount
		return mydict,wordCount

def max2(a,b,c):
	max = a
	if ( b > max):
		max = b
		if c > max:
			max = c
		
	else :
		if c > max:
			max = c
	return max
	
print "Wait ! while training is in progress..."
engDict , engCount= createDict("eng_news_2013_10K-sentences.txt")  # Creating dictionary from corpus for English
print "For English is done.."
finnDict, finnCount = createDict("fin_wikipedia_2012_10K-sentences.txt") # Creating dictionary from corpus for Finnish
print "For Finnish is done.."
italDict,italCount = createDict("ita_web_2011_10K-sentences.txt") # Creating dictionary from corpus for Italian
print "For Italian is done.."
print "Training is finished !"

cpEng  = engCount/(engCount + finnCount + italCount)   # Class probability of English
cpFinn = finnCount/(engCount + finnCount + italCount) # Class probability of Finnish
cpItal = italCount/(engCount + finnCount + italCount) # Class probability of Italian

choice = 'y'		
while (choice != 'n') :		
	sentence = raw_input("Now Enter the sentence :")
	wordList = sentence.lower().split()
	p1 = 0   # Initializing probabilities with 0 
	p2 = 0
	p3 = 0
	
	for word in wordList :
		if engDict.has_key(word):
			p1 += math.log10 ( 1 + (engDict[word] * cpEng))
			
		if finnDict.has_key(word):
			p2 += math.log10 ( 1 + (finnDict[word] * cpFinn))
			
		if italDict.has_key(word):
			p3 += math.log10 ( 1+ (italDict[word] * cpItal))
				
	print "Probability of inputr sentence being in English : ",p1/(p1+p2+p3)
	print "Probability of input sentence being in Finnish : ",p2/(p1+p2+p3)
	print "Probability of input sentence being in Italain  : ",p3/(p1+p2+p3)
	
	maxCount = max2(p1,p2,p3)
	if maxCount == p1:
		print "\nYour input sentence is most likely to be in English."
	elif maxCount == p2:
		print "\nYour input sentence is most likely to be in Finnish."
	else :
		print "\nYour input sentence is most likely to be in Italian."
	
	choice = raw_input("\nDo you want to continue ? Press any character to continue otherwise 'n' to exit.")
	if choice == 'n' :
		exit()
	

