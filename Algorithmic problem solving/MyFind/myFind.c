/*This program implements Unix "Find" command.*/

/*

find
find -abspath 1    // or 0 -  whether you want to print the absolute paths or the relative path 1 -  abs path 0 -  relative
find -name
find -iname
find -mindepth  
find -maxdepth
find -minmaxdepth
find -notname
find -inotname
find <pathname>
find -size 10    // exactly : Bytes!
find -size +10   //
find -size +1M  // or +1K or +1 G     // 
find -size -1M  // or -1K or -1 G
find -regex "xyz*"
find -regex "*xyz"


// handle the file links! - as regular files
// handled the folder lilnks!go to the link! get back! 



*/




/*

	the basic idea of the function to print all the files in a directory!    http://stackoverflow.com/questions/3554120/open-directory-using-c
	
	the function to check whether a file is a regular file or a directory has been taken(read copied) from    http://stackoverflow.com/questions/3554120/open-directory-using-c

*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>



void recurse( char * ) ; 
char * getPWD() ; 
void printAllRegularFiles() ; 
int strCmp (char *, char *); 
int strLen (char * ) ; 
char * stringToLower( char * ) ; 
void recurseWithMaxDepth( char * ) ; 
void recurseWithMinDepth( char * ) ; 
void recurseWithMinMaxDepth( char *  ) ;
int match(char *, char *);



// global variables ; 
int dirPrintFlag = 0 ;  //  0 implies that directory being printed!
int lengthOfCurrentDirPathName ;
int nameOption = 0 ;   // can have 5 values - 0 1 2 3 4
int depthOfRecursion = 0 ;                     // 0 : implies maximum/minimum  depth!
int minDepth = 0 ;
int maxDepth = 0 ;
int level = 0 ; 
long long int fileSize = -1 ;   // -1 for flag not set!  i.e option not being used
int sizeLessMoreEqual = -1 ;
int regexFlag = 0 ;    // regex Not being used : 1 : when its being used
int abspath = 0 ;

char * parentD ;
char * currentD ; 
char * pathName ;
char * truncatedName( char * ) ; 
char * inputFileName ; 

/*
        This function is_regular_file has been taken from the site - 
        http://stackoverflow.com/questions/4553012/checking-if-a-file-is-a-directory-or-just-a-file
*/
int isRegularFile(const char *path)
{
    int flag = 0 ; 
    struct stat path_stat;
    stat(path, &path_stat);
    flag = S_ISREG(path_stat.st_mode);
    return flag ; 
}


/*This function accepts a filename( more specifically - a directory name! and changes the current working directory to that directory!  )
        
*/
int main( int argc, char * argv[] ) 
{
    	char * currentPathName ; 
        if ( argc == 1 ){
        	printf(".\n") ;
		currentPathName = getPWD() ; 
 	    lengthOfCurrentDirPathName = strLen(currentPathName) ;  
		recurse(".") ;
        }
        else if ( argc == 2 ) {   //path
        	int error = chdir(argv[1]) ;
        	//chdir(argv[1]) ; 
        	
        	if ( error == 0 ) {
        		currentPathName = getPWD() ; 
        		lengthOfCurrentDirPathName = strLen(currentPathName) ;  
			recurse(".") ;   //in this particular case - no exception handling has been done!
        	}
        	else 
        		printf("Syntax Error..\n") ; 	
        }
        
        else if( argc == 3 ){
        		 

        		if ( !strCmp(argv[1],"-name") ){
        		
        			nameOption = 1 ; 
        			inputFileName = argv[2] ; 
        			currentPathName = getPWD() ; 
		        	lengthOfCurrentDirPathName = strLen(currentPathName) ; 
		        	dirPrintFlag = 1 ;  
        			recurse(".") ;
        			
        		}
        		else if ( !strCmp(argv[1],"-iname") ){
        		
        			nameOption = 2 ; 
        			inputFileName = argv[2] ; 
        			currentPathName = getPWD() ; 
		        	lengthOfCurrentDirPathName = strLen(currentPathName) ; 
		        	dirPrintFlag = 1 ; 		        	 
        			recurse(".") ;
        		}
        		else if ( !strCmp(argv[1],"-notname") ){
        			
        			nameOption = 3 ; 
        			inputFileName = argv[2] ; 
        			currentPathName = getPWD() ; 
		        	lengthOfCurrentDirPathName = strLen(currentPathName) ;  
		        	dirPrintFlag = 1 ; 		        	
        			recurse(".") ;
        		}
        		else if ( !strCmp(argv[1],"-inotname") ){
        			
        			nameOption = 4 ; 
        			inputFileName = argv[2] ; 
        			currentPathName = getPWD() ; 
		        	lengthOfCurrentDirPathName = strLen(currentPathName) ; 
		        	dirPrintFlag = 1 ; 		        	 
        			recurse(".") ;
        		}
        		else if ( !strCmp(argv[1],"-maxdepth") ) {
        			
        			depthOfRecursion = atoi(argv[2]) ; 
        			if (depthOfRecursion == 0)
        				printf(".\n") ;  
        			else{
        				currentPathName = getPWD() ; 
			        	lengthOfCurrentDirPathName = strLen(currentPathName) ;  
			        	dirPrintFlag = 1 ; 			        	
			        	recurseWithMaxDepth(".") ;
        			    }
        		}
        		else if ( !strCmp(argv[1],"-mindepth") ) {
        			
        			depthOfRecursion = atoi(argv[2]) ; 
        			if (depthOfRecursion == 0)
        				printf(".\n") ;  
        			else{
        				currentPathName = getPWD() ; 
			        	lengthOfCurrentDirPathName = strLen(currentPathName) ; 
			        	dirPrintFlag = 1 ;  
			        	recurseWithMinDepth(".") ;
        			    }
        		}
        		else if ( !strCmp(argv[1],"-regex") ){
        			
        			
        			inputFileName = argv[2] ; 
        			currentPathName = getPWD() ; 
		        	lengthOfCurrentDirPathName = strLen(currentPathName) ; 
		        	dirPrintFlag = 1 ; 	
		        	regexFlag = 1 ;         	 
        			recurse(".") ;
        		}
        		else if ( !strCmp(argv[1],"-abspath") ){
        		
        			
        			abspath = atoi(argv[2]) ;   // 1 for printing the absolute path
        			currentPathName = getPWD() ; 
		        	lengthOfCurrentDirPathName = strLen(currentPathName) ; 
		        	dirPrintFlag = 1 ;  
        			recurse(".") ;
        			
        		} 
        		
        		else if ( !strCmp(argv[1],"-size") ) {
        			//determining the type of size Mb Kb or Bytes...no symbol implies bytes
        			char * temp  = argv[2] ; 
        			int l = strLen(temp) ; 
        			
        			
        			switch( temp[0] ) {
        				case '+' : 	 
        						sizeLessMoreEqual = 1 ;   // more than
        						break ; 

					case '-' :   	//manipulating the first character - replacing it with zero!  
        						temp[0] = '+' ; 
							sizeLessMoreEqual = 2 ;  //size less than
							break ;
							
					case '0' :	
        				case '1' :
        				case '2' :
        				case '3' : 
        				case '4' :
        				case '5' :
        				case '6' :
        				case '7' :
        				case '8' :
        			        case '9' :       
        			        		 sizeLessMoreEqual = 0 ;  // size exactly equal
        			        		 
        			        		 break ; 
        			        		 			        					default :  printf("Invalid argument for size \n") ;		
        						
        			}
        			
        			
        			switch(temp[l-1]){
        				case 'B' : 
        				case 'b' :      temp[l-1] = '\0' ;  // truncating the size of the input 
		        				fileSize = atoi(temp) ; 
			        			currentPathName = getPWD() ; 
						        lengthOfCurrentDirPathName = strLen(currentPathName) ; 
		        				dirPrintFlag = 1 ; 		         
						        recurse(".") ;
						        break;
        					
        				case '0' :
        				case '1' :
        				case '2' :
        				case '3' : 
        				case '4' :
        				case '5' :
        				case '6' :
        				case '7' :
        				case '8' :
        				case '9' : 	fileSize = atoi(temp) ; 
			        			currentPathName = getPWD() ; 
						        lengthOfCurrentDirPathName = strLen(currentPathName) ; 
		        				dirPrintFlag = 1 ; 		         
						        recurse(".") ;
						        break; 
						        
						        
						        
					case 'K' :
					case 'k' :	temp[l-1] = '\0' ;  // truncating the size of the input 
							fileSize = atoi(temp) * 1024 ; 
			        			currentPathName = getPWD() ; 
						        lengthOfCurrentDirPathName = strLen(currentPathName) ; 
		        				dirPrintFlag = 1 ; 			         
						        recurse(".") ;
						        break;     
						        
					case 'M' :	// assuming that integer is 4 bytes! and it is sufficient to hold the sizes of files which are in MBs or GB's
					case 'm' :	
							temp[l-1] = '\0' ;  // truncating the size of the input 
							fileSize = atoi(temp) * 1024 * 1024; 
			        			currentPathName = getPWD() ; 
						        lengthOfCurrentDirPathName = strLen(currentPathName) ; 
		        				dirPrintFlag = 1 ; 			         
						        recurse(".") ;
						        break;  
					
					
						        
		 			case 'G' :	// assuming that integer is 4 bytes! and it is sufficient to hold the sizes of files which are in MBs or GB's
					case 'g' :	
							temp[l-1] = '\0' ;
							fileSize = atoi(temp) * ( long long int )1024 * 1024 * 1024; 
						
			        			currentPathName = getPWD() ; 
						        lengthOfCurrentDirPathName = strLen(currentPathName) ; 
		        				dirPrintFlag = 1 ; 			         
						        recurse(".") ;
						        break;  
						        
					default :  printf("Invalid argument for size \n") ; 						        
						        	         
						        
        			}
        			
        			
        			
        			
        			
        			
        		}       		
        		else
        			printf("Syntax Error!  : '%s' \n",argv[1]) ; 
 	
         }
         else if ( argc == 4 ){
         		if ( !strCmp(argv[1],"-minmaxdepth") ) {
        			
        			minDepth = atoi(argv[2]) ; 
        			maxDepth = atoi(argv[3]) ; 
        			 
        			if (minDepth == 0)
        				printf(".\n") ; 
        				 
        			currentPathName = getPWD() ; 
			        lengthOfCurrentDirPathName = strLen(currentPathName) ;  
		        	dirPrintFlag = 1 ; 			        
			        recurseWithMinMaxDepth(".") ;
        			
        		}
        		else 
        			printf("Syntax Error!  : '%s' \n",argv[1]) ;         		 
         }
              
        getch();
        return 0;

}



/*
	This function takes as input a directory name(in the current directory) and prints all the files present in that directory recursively
*/
void recurse( char * name ) 
{
 	struct dirent *pDirent;
    DIR *pDir;
	char *pathName ;
	
	 
        chdir(name);       // this is the C equivalent of cd shell command ! 
        
    
        
        // STEP I - Let us print all the regular files in the directory!
        
        printAllRegularFiles() ; 
        
        
        pDir = opendir (".");
        if(pDir == NULL) {
            printf("Cannot open directory '%s'\n", ".");
            return ;
        }      
              

        // Now lets take care of the Directories!  
        while((pDirent = readdir(pDir)) != NULL) {
         	if( isRegularFile(pDirent -> d_name) || ( pDirent -> d_name[0] == '.') ) {
		   // do nothing! - this has been handled already
		        
		}
	        else{
		    truncatedName( getPWD() ) ; 
		    if ( dirPrintFlag ==0 ) 
	            	printf("%s/%s\n",truncatedName(getPWD()) , pDirent->d_name) ; 
	            pathName = getPWD()  ;     
	            recurse(pDirent->d_name); 
	            

		     chdir(pathName) ;    // this will take care of the Folder Links!

                     
                }    
		        
        }
       
        closedir (pDir);
        
}



/*
	Controlled path recursion
*/
void recurseWithMaxDepth( char * name ) 
{
 	struct dirent *pDirent;
        DIR *pDir;
	
	
	level ++ ; 
	 		
	 
        chdir(name);       // this is the C equivalent of cd shell command ! 
        
    
        
        
        if ( level > depthOfRecursion )
		return ; 
        printAllRegularFiles() ; 
        
        pDir = opendir (".");
        if(pDir == NULL) {
            printf("Cannot open directory '%s'\n", ".");
            return ;
        }      
              
               
        // Now lets take care of the Directories!  
        while((pDirent = readdir(pDir)) != NULL) {
         	if( isRegularFile(pDirent -> d_name) || ( pDirent -> d_name[0] == '.') ) {
		   // do nothing! - this has been handled already
		        
		}
	        else{
      	            truncatedName( getPWD() ) ;
      	            if ( dirPrintFlag ==0 )  
	            	printf("%s/%s\n",truncatedName(getPWD()) , pDirent->d_name) ;    
	            recurseWithMaxDepth(pDirent->d_name); 
	            level -- ; 
                    chdir("..") ;
                                         
                }    
		        
        }
       
        closedir (pDir);
        
}


/*
	Printing based on Controlled Depth
*/
void recurseWithMinDepth( char * name ) 
{
 	struct dirent *pDirent;
        DIR *pDir;
	
	
	level ++ ; 
	 		
	 
        chdir(name);       // this is the C equivalent of cd shell command ! 
        
    
       
        if ( level >= depthOfRecursion )
		printAllRegularFiles() ; 
        
        pDir = opendir (".");
        if(pDir == NULL) {
            printf("Cannot open directory '%s'\n", ".");
            return ;
        }      
              
               
        // Now lets take care of the Directories!  
        while((pDirent = readdir(pDir)) != NULL) {
         	if( isRegularFile(pDirent -> d_name) || ( pDirent -> d_name[0] == '.') ) {
		   // do nothing! - this has been handled already
		        
		}
	        else{
                    truncatedName( getPWD() ) ; 
                    if ( dirPrintFlag ==0 ) 
	            	printf("%s/%s\n",truncatedName(getPWD()) , pDirent->d_name) ;    
	            recurseWithMinDepth(pDirent->d_name); 
	            level -- ; 
                    chdir("..") ;
                                         
                }    
		        
        }
       
        closedir (pDir);
        
}



/*
	Recursion till the maxDepth and print after min depth
*/
void recurseWithMinMaxDepth( char * name ) 
{
 	struct dirent *pDirent;
        DIR *pDir;
	
	
	level ++ ; 
	 		
	 
        chdir(name);       // this is the C equivalent of cd shell command ! 
        
    
	if( level > maxDepth )
	       return ;       

        if ( level >= minDepth )
		printAllRegularFiles() ; 
        
        pDir = opendir (".");
        if(pDir == NULL) {
            printf("Cannot open directory '%s'\n", ".");
            return ;
        }      
              
               
        // Now lets take care of the Directories!  
        while((pDirent = readdir(pDir)) != NULL) {
         	if( isRegularFile(pDirent -> d_name) || ( pDirent -> d_name[0] == '.') ) {
		   // do nothing! - this has been handled already
		        
		}
	        else{
                    truncatedName( getPWD() ) ; 
	            if ( dirPrintFlag ==0 ) 
	            	printf("%s/%s\n",truncatedName(getPWD()) , pDirent->d_name) ;    
	            recurseWithMinMaxDepth(pDirent->d_name); 
	            level -- ; 
                    chdir("..") ;
                                         
                }    
		        
        }
       
        closedir (pDir);
        
}


/*
        Function to print the path to the current directory 
*/
char * getPWD(){
	char * pwd = calloc(sizeof(char),1000) ;
	getcwd(pwd, 1000) ;
	//printf("Current working dir: %s\n", pwd);	
	return pwd ;
}


/*
        Function to print all the names of the regular files in a directory except the "." and the ".."
        
        The basic idea had been taken from the link below
        http://stackoverflow.com/questions/3554120/open-directory-using-c
        
*/
void printAllRegularFiles(char * name)
{
        //getPWD() ; 

 	struct dirent *pDirent;
        DIR * pDir;
        char *str1, *str2 ; 
        pDir = opendir(".");

        if (pDir == NULL) { 
            printf("Cannot open directory '%s'\n", name);
            return ;
        }
        
        while((pDirent = readdir(pDir)) != NULL) {
         	if( isRegularFile(pDirent -> d_name ) ){
         	           pathName = getPWD();
         	           
         	           if ( abspath == 0 )	
         	           	pathName = truncatedName( pathName )  ; 
         	          // printf("Name Option %d",nameOption) ; 
         	           if ( nameOption == 0 && fileSize == -1 && regexFlag == 0  )
	         	        printf("%s/%s\n", pathName,pDirent->d_name) ; 
	         	   if ( nameOption == 1 ){   
	         	   	    
	         	   	if ( strCmp( pDirent->d_name, inputFileName ) == 0 ){
	         	   		printf("%s/%s\n", (pathName),pDirent->d_name) ; 	
	         	   	} 
	         	   }
	         	   if ( nameOption == 2 ){   
	         	    	str1 = stringToLower(pDirent->d_name) ;     
	         	   	str2= stringToLower(inputFileName) ;
	         	   	if ( strCmp( pDirent->d_name, inputFileName ) == 0 ){
	         	   		printf("%s/%s\n", (pathName),pDirent->d_name) ; 	
	         	   	} 
	         	   }
	         	   if ( nameOption == 3 ){   
	         	   	    
	         	   	if ( strCmp( pDirent->d_name, inputFileName ) != 0 ){
	         	   		printf("%s/%s\n", (pathName),pDirent->d_name) ; 	
	         	   	} 
	         	   }
	         	   if ( nameOption == 4 ){   
	         	    	str1 = stringToLower(pDirent->d_name) ;     
	         	   	str2= stringToLower(inputFileName) ;
	         	   	if ( strCmp( pDirent->d_name, inputFileName ) != 0 ){
	         	   		printf("%s/%s\n", (pathName),pDirent->d_name) ; 	
	         	   	} 
	         	   }
	         	   if ( regexFlag == 1 ){   
	         	   	 
	         	   	if ( match( inputFileName, pDirent->d_name ) ){
	         	   		printf("%s/%s\n", (pathName),pDirent->d_name) ; 	
	         	   	} 
	         	   }
	         	   
	         	   //reading the file size if required
	         	   if ( fileSize != -1 ){
	         	   
	         	   	FILE * fp ;
	         	   	long long int size;
	         	   	fp = fopen(pDirent->d_name,"r") ; 
	         	   	fseek(fp, 0L, SEEK_END);
	         	   
	         	   	size = ftell(fp) ; 
	         	   	fclose(fp) ;
	         	   	
	         	   
	         	   
	         	   	// switching based on the file Size less than or equal to
	         	   	switch(sizeLessMoreEqual){	
	         	   		case 0 :    // exactly equal
	         	   				if ( size == fileSize )
	         	   					printf("%s/%s\n", pathName,pDirent->d_name) ;
	         	   				break ; 
	         	   			
	         	  	 	case 1 :    // size more than  : i.e ' + ' argument
	         	  	 			if ( size > fileSize )
	         	  	 				printf("%s/%s\n", pathName,pDirent->d_name) ; 
	         	 	  			break ; 
	         	   			
	         	 	  	case 2 :    // size less than  : i.e ' - ' argument
	         	 	  			if ( size < fileSize )
	         	 	  				printf("%s/%s\n", pathName,pDirent->d_name) ; 
	         	 	  			break ; 	         	   				         	   			
	         	   	}
	         	   } 
	         	   	
	         	   		
	         	   			
		}       
        }
       
        closedir (pDir);
}



/*
        Function to compare two strings! -  returns 1 if the strings are the same, else returns 0 - Case sensitive!  
*/
int strCmp (char *str1, char *str2) {
  for ( ; *str1 == *str2; str1++, str2++)
    if (*str1 == '\0')
      return 0;
  return *str1 - *str2;
}


/*
	Function to return the length  of a string!  
*/
int strLen (char *str) {
  int count;
  for (count = 0; *str != '\0'; str++)
    count++;
  return count;
}

/*
	Function to return the truncated name of the path
*/
char * truncatedName( char * completeName ) {
	char * truncated ;
	int len,i ; 
	
	len = strLen(completeName) ; 
	truncated = calloc(sizeof(char), (len - lengthOfCurrentDirPathName) + 1) ; 
	truncated[0] = '.' ;
	 
	for(i = lengthOfCurrentDirPathName; i<len ; i++)	{
		truncated[i-lengthOfCurrentDirPathName+1] = completeName[i]; 
	}
	return truncated ;
}


/*
	Function to accept a string and return the same string with all the characters in lower case!
*/
char * stringToLower( char * uppercase){
	int i = 0 ; 
	for( i = 0 ; uppercase[i] != '\0'; i++){
		if ( uppercase[i] <= 'Z' && uppercase[i] >= 'A' ) {
			uppercase[i] = uppercase[i] + 32 ; 
		}
	} 
	return uppercase ;
} 


/*
	Returns 1 if the string and the regex match!
	otherwise 0
	only two kinds of regex are accepted as of now!!  a* and *a
*/
int match(char *regex, char *string ){
	//printf("%s  %s \n",regex,string) ; 
	int i = 0, l,j ; 
	l = strLen(regex) ;
	j = strLen(string) -1;
	if (regex[ l - 1 ] == '*'){
		for(i=0; regex[i] != '*'; i++){
			if ( regex[i] != string[i] )
				return 0 ;
		return 1 ; 		
		}
	}
	
	else if (regex[ 0 ] == '*'){
		for(i=l-1; regex[i] != '*' ; i--,j--){
			
			
			//printf(" i %c  j %c\n",regex[l-j],string[i]) ; 
			if ( regex[i] != string[j] ){
//				printf("%c%c\n",regex[l-j] ,string[i]) ; 
				return 0 ;
					
			}
		
		}
		return 1 ; 		
	}
	else
		printf("Syntax Error\n. Only xyz* and *xyz are allowed") ; 
		
}

