import sys
if len(sys.argv) != 2 :
	print "Please provide input in the following format:\n SourceFilename.py graphInputFile.txt"
	exit()
wf = open("cnf.txt","w")   # Clauses will be written into this file. 

with open(sys.argv[1], "r") as rf:
	
	for line in rf:
		if line[0] == "p":  
			words  = line.split()
			k = int(words[1])  #Reading number of colors from input file
			n = int(words[2])  #Reading number of vertices from input file
			e = int(words[3])  #Reading number of edges from input file
			var  = k * n
			clauses = n + n * ((k * (k-1))/2) + e * k   # Calculating number of possible clauses
			newLine = "p " + "cnf " + str(var) + " " + str(clauses)
			wf.write(newLine)
			      
			newLine = "\n"
			### For type 2 clauses :- One vertex must have at least one color.
			j = 1
			i = 1
			while i <= n*k+1 :  # vertec-color space is mapped into vertex*color space
				if j <= k:
					newLine +=  str(i) + " "        			
					j = j + 1
					i = i + 1	
				else:       			
					wf.write( newLine + "0")
					newLine = "\n" 
					j = 1

	
			# Type 1 :- One vertex can't have two colors. n*kC2
			wf.write("\n")
			col = k
			k = 1
			i = 1
			while i <= n :    # For all vertices
				j = 1
				while j <= col : # For all colors
					k = j+1
					while k <= col : # Again for all colors
						a = "-" + str((i-1)*col + j) # mapping vertex number to vertex*Color space
						b = "-" + str((i-1)*col + k)
						wf.write( a + " "+ b + " 0" + "\n")
						k = k + 1
					j = j + 1
				i = i + 1 

			k = int(words[1])  # Reinitializing number of colors in K	
        	
		###Type 1 :- Two vertices shared by an edge can't have same color.
		elif line[0] == "e":
			words = line.split()
			v1 = int(words[1])
			mappedv1 = (v1-1)*k + 1  #Unmapping vertex number from vertex-Color space to vertex space

			v2 = int(words[2]) 
			mappedv2 = (v2-1)*k + 1

			for i in range(1,k+1):
				wf.write("-" + str(mappedv1+i-1) + " " + "-" + str(mappedv2+i-1) + " 0")
				wf.write("\n")
