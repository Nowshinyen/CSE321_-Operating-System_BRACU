#include <pthread.h>   
#include <stdio.h>
#include <string.h>
#define MAX 10 //producers and consumers can produce and consume upto MAX
#define BUFLEN 6
#define NUMTHREAD 2      /* number of threads */
void * consumer(int *id);
void * producer(int *id);

char buffer[BUFLEN+1];
char source[BUFLEN+1]; //from this array producer will store it's production into buffer
int pCount = 0;
int cCount = 0;
int buflen;

//initializing pthread mutex and condition variables
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty  = PTHREAD_COND_INITIALIZER;
pthread_cond_t full  = PTHREAD_COND_INITIALIZER;
int thread_id[NUMTHREAD]  = {0,1};
int i = 0; 
int j = 0;

int main()
{
    int i;
    /* define the type to be pthread */
    pthread_t thread[NUMTHREAD];

    strcpy(source,"abcdef");
    buflen = strlen(source);
    /* create 2 threads*/
    /* create one consumer and one producer */
    /* define the properties of multi threads for both threads  */
    //Write Code Here
    //.......................................................................................................................

    pthread_create ( &thread[0] , NULL , (void *)producer , &thread_id[0] ) ; //here i have created thread for producer 
    //pthread_create  is used for creating  new thread
    // &thread[0] for storing thread id of producer , &thread_id[0] for passing  0 to the producer function
    pthread_create ( &thread[1] , NULL , (void *)consumer , &thread_id[1] ) ;  //here i have created thread for consumer 
    //&thread[1] for storing thread id of consumer , &thread_id[1] for passing 1 to the consumer function
    
    pthread_join (thread[0], NULL) ;
    //pthread_join is used for thread to terminate
    //waiting for  producer thread  to done his work 
    // don't need any return value thats why null 
    pthread_join (thread[1], NULL) ;
    //waiting for consumer thread  to done his work 
    // don't need any return value thats why null 

    //.................................................................................................
    return 0;
}


void * producer(int *id)
{
	/*
1. Producer stores the values in the buffer (Here copies values from source[] to buffer[]).
2. Use mutex and thread communication (wait(), sleep() etc.) for the critical section.
3. Print which produ4. Producer can produce up cer is storing which values using which thread inside the critical section.
to MAX
*/
//Write code here

//.................................................................................................
while (i < MAX )  // loop runs until the producer has produced 10 item 
    {
        pthread_mutex_lock( &count_mutex ) ; //  locked count_mutex
         // pthread_mutex_lock is used for,one and only 1 thread can access a shared resource at a time
        int temp1_idx = (pCount + 1 ) % BUFLEN ; // calculates next position
        
        while (temp1_idx == cCount)  //check if buffer is full or not 
        //when  buffer is full the producer wait
        {

            pthread_cond_wait(&nonEmpty, &count_mutex) ; // pthread_cond_wait used for a thread wait
        }

        int x = pCount % BUFLEN ;   //calculates the current position in the circular buffer  
        buffer[pCount] =  source[x] ;  //stores it in buffer at position pCount
        
        printf("%d produced %c by Thread %d\n " , i , buffer[pCount] , *id ) ;

        pCount = (pCount + 1) % BUFLEN ;  //pCount go to the next position in the buffer circular way 
        
        pthread_cond_signal(&full) ;  //pthread_cond_signal is used for notify other thread  to continue their execution
        // as it used for informing the consumer, buffer is not empty 
        pthread_mutex_unlock(&count_mutex) ; // unlocked the mutex,  allow the consumer thread to access  
        
        i++  ;
    }

//.................................................................................................
}

void * consumer(int *id)
{
   	/*
1. Consumer takes out the value from the buffer and makes it empty.
2. Use mutex and thread communication (wait(), sleep() etc.) for critical section
3. Print which consumer is taking which values using which thread inside the critical section.
4. Consumer can consume up to MAX
*/
//Write code here

//.................................................................................................
while (j < MAX)  // loop runs until the consumer has consumed  10 items
    {
        pthread_mutex_lock(&count_mutex) ;  //  locked the count_mutex
        /// pthread_mutex_lock is used for, one and only 1 thread can access a shared resource at a time
        while (pCount == cCount)  //checks if the buffer is empty 
        //if  buffer is empty consumer wait until producer give something 
        {

            pthread_cond_wait(&full, &count_mutex) ;  // pthread_cond_wait used for a thread wait until condition satisfied
            //no  thread can access  shared data when the consumer is waiting
        }

        printf("%d consumed %c by Thread %d\n ", j, buffer[cCount], *id) ;
        
        cCount = (cCount + 1) % BUFLEN ; // cCount  forward to  next position in  buffer
        pthread_cond_signal(&nonEmpty) ;  //pthread_cond_signal is used for notify other thread  to continue their execution
        // tells producer there re space for producer to give more items
        
        pthread_mutex_unlock(&count_mutex ) ;  // unlocked the mutex 
        // allow the producer thread to access
        j++  ;
    }

//.................................................................................................
}


