### Mengyu Wu

SID: 107207928

Email: mewu0016@colorado.edu

### Submission Contens: Enter /PA3

1. multi-lookup.h
  
    The header file for multi-lookup.c which include declared cariables and methods
        
2. Makefile
    
    Adjusting Makefile in order to let multi-lookup.c are compiled to .o files.
    
3. multi-lookup.c
  
    Implementation of a multi threads safe program to read and write DSN address from each hostname file.

4. performance.txt

    which include the time consuming for multi-lookup.c performance in different number of requester and resolver threads.
    
## To Run
1. Ensure all files in this submission have been placed in their respective file paths.

2. Compile and Run each test program with commands below

      "make PA3"
      "valgrind ./multi-lookup <# requester> <# resolver> <requester log> <resolver log> [ <data file> ...]"
      
3. After test process, check the memory leaks with valgrind
      
4. remove compiled files

       "make clean" to delete all compiled files by multi-lookup.c