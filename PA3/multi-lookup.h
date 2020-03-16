#ifndef MULT_LOOKUP_H
#define MULT_LOOKUP_H

#include "util.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <stddef.h>

#define MINARGS 3
#define USAGE "<inputPath> <outputPath>"
#define INPUTFS "%1024s" //max length for string in 1024 characters

#define MAX_IINPUT_FILES 10
#define MAX_RESOLVER_THREADS 10
#define MAX_REQUESTER_THREADS 5
#define MAX_NAME_LENGTH 1025
#define MAX_LP_LENGTH INET6_ADDRSTRLEN

//Structs
    struct thread_data{
        char *ptr_to_fileArray;
    };
    struct mutexes {
        pthread_mutex_t lock[MAX_RESOLVER_THREADS + MAX_REQUESTER_THREADS];
        pthread_mutex_t sharedBufferLock;
        pthread_mutex_t serviceLock;
        pthread_mutex_t resultsLock;
        pthread_mutex_t GlobalFileLock;  
    };
    struct various_variables {
        char sharedBuffer[2000][20];
        char results[20];
        char serviced[20];
        int GlobalFileCounter;
        int bufferIndex;
    };
    struct globals {
        struct thread_data *array;
        struct various_variables var;
        struct mutexes mutex;
    };


void *requester(void *);
void *resolver();

#endif


