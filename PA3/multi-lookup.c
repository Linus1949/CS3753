#include "multi-lookup.h"

void *requester(void *thdread){
  // process id
  pid_t tid = syscall(SYS_gettid);
  struct globals *requester = thdread;
  printf("Thread <%d> serviced 1 files\n", tid);


  for(int i = 0; i < requester->var.GlobalFileCounter; i++) {
    // if thread currently doesn't for(int i = 0; i < have lock, it now will
    // attempts to acquire ownership of the mutex specified without blocking the calling thread
    if(!pthread_mutex_trylock(&requester->mutex.lock[i])){
      char file_tobe_serviced[20];
      //copy each input file name
      strcpy(file_tobe_serviced, (requester->array->ptr_to_fileArray + (i*20)));
       //read input file 
      FILE* inputFile = fopen(file_tobe_serviced, "r");
      // Bogus Input File Path
      if(!inputFile) {  
        perror("Given a bad input path\n");
      }
      char hostName[MAX_NAME_LENGTH];
      // fgets(dest, n-1 characters to be read, src stream)
      while(fgets(hostName, sizeof(hostName)+1, inputFile)){
        // fetch host and store them in buffer
        // intialize as 0 character
        hostName[strlen(hostName)-1] = '\0';
        strcpy(requester->var.sharedBuffer[requester->var.bufferIndex], hostName);
        //next line in buffer
        requester->var.bufferIndex++; 
      }
      fclose(inputFile);
      pthread_mutex_destroy(&requester->mutex.lock[i]);
    }
  }

  	//lock the service mutex before servicing
    pthread_mutex_lock(&requester->mutex.serviceLock); 
    // appending to serviced file
    FILE *files = fopen(requester->var.serviced, "a"); // serviced texts
    // handle error
    if(files == NULL) {
    	printf("couldn't open serviced.txt\n");
        exit(1);
    }
    //append each thread
    fprintf(files, "Thread <%d> serviced 1 files\n", tid);
    fclose(fopen(requester->var.serviced, "w"));
    //unlock service lock
    pthread_mutex_unlock(&requester->mutex.serviceLock);
}


void *resolver(void *thdread){
	struct globals *resolver = thdread;
	//check the shared buffer is locked
	if(!pthread_mutex_trylock(&resolver->mutex.sharedBufferLock)) {
		//check the shared buffer is locked
		for(int i = 0; i < resolver->var.bufferIndex; i++){
			char hostname[MAX_NAME_LENGTH];
			char ip[MAX_LP_LENGTH];
			//copy the host name from the shared buffer
			strcpy(hostname, resolver->var.sharedBuffer[i]);
			//print hostname separated
			printf("%s, ", hostname);
			//set host name status
			int status = 0;
			//Bogus hostname 
			if(dnslookup(hostname, ip, sizeof(ip)) == UTIL_FAILURE){
				fprintf(stderr, "Error: DNS lookup failed on hostname: %s\n", hostname);
				//set the status
				status = 1;
				printf("\n");
			}
			else{
				//print the ip
				printf("%s\n", ip);
			}
			//locking results lock
			pthread_mutex_lock(&resolver->mutex.resultsLock); 
			// appending newly found ip
				FILE *res_file = fopen(resolver->var.results, "a");
				//Bogus output file path
				if(res_file == NULL) {
					printf("Given a bad output file path\n");
					exit(1);
				}
				//status is good
				if(!status){
					//if not valid hostname
					fprintf(res_file, "%s, %s\n", hostname, ip);
				}
				//status is bad, just print host
				else {
					fprintf(res_file, "%s\n", hostname);

				}
				fclose(fopen(resolver->var.results, "w"));
			//unlock the results locker
			pthread_mutex_unlock(&resolver->mutex.resultsLock);
		}
	pthread_mutex_destroy(&resolver->mutex.sharedBufferLock);
	}
}


int main(int argc, char *argv[]){
	//delcare timer
	//struct timeval begin, end;
	//gettimeofday(&begin, NULL)​;
	struct timeval begin;
	struct timeval  end;
	gettimeofday(&begin, NULL);

	//instance global struct
	struct globals gv;
	gv.var.bufferIndex = 0;

	//set the results and services files
	strcpy(gv.var.results, argv[3]);
	strcpy(gv.var.serviced, argv[4]);

	//create requestor pool
	int numReqthreads = strtol(argv[1], NULL, 10);
	pthread_t reqThreads[numReqthreads];
	struct thread_data thread_data_array[numReqthreads];
	//array for requestor threads
	gv.array = thread_data_array;

	//create resolver pool
	int numResthreads = strtol(argv[2], NULL, 10);
	pthread_t resThreads[numResthreads];
	//create files array
	char files[20][20];

	//set the number of files
	int filesCount = argc - 5;
	gv.var.GlobalFileCounter = filesCount;

	// copying the contents of each input file to files array
	for(int i = 0; i < filesCount; i++){
		strcpy(files[i], argv[i+5]);
	}


	//initialze mutex 
	pthread_mutex_init(&gv.mutex.resultsLock, NULL);
	pthread_mutex_init(&gv.mutex.serviceLock, NULL);
	pthread_mutex_init(&gv.mutex.sharedBufferLock, NULL);
	pthread_mutex_init(&gv.mutex.GlobalFileLock, NULL);
	for (int i=0; i<(MAX_RESOLVER_THREADS + MAX_REQUESTER_THREADS);i++){
		pthread_mutex_init(&gv.mutex.lock[i], NULL);
	}

	//populating thread data and input files to be serviced
	for(int i=0; i<numReqthreads; i++){
		thread_data_array[i].ptr_to_fileArray = &files;
	}

	//initialze requestor threads
	for(int i=0; i<numReqthreads; i++){
		// create thread (thread, attr, start routing, arg)
		pthread_create(&reqThreads[i], NULL, requester, &gv);
		pthread_join(reqThreads[i], NULL);
	}

	//initialze resolver threads
	for(int i=0; i<numResthreads; i++){
		// create thread (thread, attr, start routing, arg)
		pthread_create(&resThreads[i], NULL, resolver, &gv);
		pthread_join(resThreads[i], NULL);
	}

	//destory mutex
	pthread_mutex_destroy(&gv.mutex.resultsLock);
	pthread_mutex_destroy(&gv.mutex.serviceLock);
	pthread_mutex_destroy(&gv.mutex.resultsLock);

	//gettimeofday(&end, NULL)​;
	gettimeofday(&end, NULL);
	printf("Number of requester thread = %d\n", numReqthreads);
	printf("Number of resolver thread = %d\n", numResthreads);
	printf("Total run time:%f\n", (end.tv_sec - begin.tv_sec)*1000000.0 + 
            ((end.tv_usec - begin.tv_usec)));
    return 0;
}
