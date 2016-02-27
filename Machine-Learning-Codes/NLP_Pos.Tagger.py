import codecs
from nltk.tag import CRFTagger,HiddenMarkovModelTrainer,HiddenMarkovModelTagger,TnT
Training_Data = "train-htb-ver0.5.gold.utf8.conll"
Test_Data = "devel-htb-ver0.5.gold.utf8.conll"

# Function to convert input corpus to list (list (tuple(str,str))) format.
def corpusRead(corpusName):
    fptr = open(corpusName,'r')   # Opening corpus file  
    out = codecs.open("output.txt", "w") 
    ListOfSentences = []
    listOfWords = []
    contents = fptr.read().splitlines()
    for line in contents:
        line = line.split()
        if(line != []):
            t1 = unicode(line[1],'utf-8')
            t2 = unicode(line[3],'utf-8')
            tple = (t1,t2)
            out.write(line[1]+','+line[3]+'\n') # Writing word and tag pair in a text file.
            listOfWords.append(tple)
        else:
            ListOfSentences.append(listOfWords)
            listOfWords = []     # Emptying listOfWords 
    ListOfSentences.append(listOfWords)
    return ListOfSentences
    
#Function to convert input sentence into list (list (tuple(str,str))) format
def converter(text):
    requiredFormat = []
    #delm = '।'
    #delm = unicode(delm,"utf-8")
    listOfSentences = text.split('.')
    #print listOfSentences
    for line in listOfSentences :
        wordsPerLine = line.split()
        wordsPerLine = [unicode(word,'utf-8') for word in wordsPerLine]
        for word in wordsPerLine :
            requiredFormat.append(word)
    #print "\nrequiredFormat = ",requiredFormat
    return requiredFormat


print "\nReading training corpus...."
ListOfSentences_Training = corpusRead(Training_Data)
print "Reading test corpus...."  
ListOfSentences_Test = corpusRead(Test_Data)




#CRF Training
ct = CRFTagger()
print "CRF Training starts..."
ct.train(ListOfSentences_Training,'model.crf.tagger')
print "CRF Training is done."

print "Testing starts"
print "Accuracy of CRF is = ",ct.evaluate(ListOfSentences_Test) * 100
#Tagging by CRF Tagger
ch = 'y'
while (ch != 'n'):
    text = raw_input("Enter the text to be tagged : \n")
    text = converter(text)
    print ct.tag_sents(text)
    print "\nDo you want to continue ?"
    ch = raw_input()
 



#HMM Training

print "HMM Training using HiddenMarkovModelTrainer() starts.."
hmmTrain1 = HiddenMarkovModelTrainer().train_supervised(ListOfSentences_Training)
print "Training is completed.\n"

print "Testing starts now.."
hmmTrain1.test(ListOfSentences_Test)
print "Testing is completed.."

print "\nTrainging by HiddenMarkovModelTagger() starts now.."
hmmTrain2 = HiddenMarkovModelTagger.train(ListOfSentences_Training)
print "Training is completed.\n"
print "Testing starts now.."
hmmTrain2.test(ListOfSentences_Test)
print "Testing is completed.."



ch = 'y'
while (ch != 'n'):
    text = raw_input("Enter the text to be tagged : \n")
    text = converter(text)
    print hmmTrain2.tag(text) 
    print "\nDo you want to continue ?"
    ch = raw_input()
    


#TNT Training

tnt = TnT(unk=None, Trained=False, N=100, C=False)
print "TNT training starts.."
tnt.train(ListOfSentences_Training)
print "TNT training is done."
print "TNT testing starts.."
print tnt.evaluate(ListOfSentences_Test)
print "TNT Testing is done."  
ch = 'y'
while (ch != 'n'):
    text = raw_input("Enter the text to be tagged : \n")
    text = converter(text)
    print tnt.tagdata(text) 
    print "\nDo you want to continue ?"
    ch = raw_input()




