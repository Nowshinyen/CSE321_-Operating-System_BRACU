#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
/*
This program provides a possible solution using mutex and semaphore.
use 5 Farmers and 5 ShopOwners to demonstrate the solution.
*/
#define MaxCrops 5 // Maximum crops a Farmer can produce or a Shpoowner can take
#define warehouseSize 5 // Size of the warehouse
sem_t empty;
sem_t full;
int in = 0;
int out = 0;
char crops[warehouseSize]={'R','W','P','S','M'}; //indicating room for different crops
char warehouse[warehouseSize]={'N','N','N','N','N'}; //initially all the room is empty
pthread_mutex_t mutex;


void *Farmer(void *far)
{   
   /*
   1.Farmer harvest crops and put them in particular room. For example, room 0 for Rice(R).
   2.use mutex and semaphore for critical section.
   3.print which farmer is keeping which crops in which room inside the critical section.
   4.print the whole warehouse buffer outside of the critical section
   */

   //...................................................................
   for (int x= 0; x < MaxCrops; x++)  // loop runs 5 times
   {
      sem_wait(&empty) ;
      // use semaphore to check  there is space available in  warehouse
      //empty semaphore count the number of empty slots
      pthread_mutex_lock(&mutex) ;
      /// pthread_mutex_lock is used for, one and only 1 thread can access a shared resource at a time
      //doesnt allow other threads as farmer is inserting crop
      warehouse[in] = crops[in] ;  //inserting Crop in Warehouse
        
      printf(" Farmer %d:  insert crops %c at %d\n" , *(int *)far , warehouse[in] , in ) ;
      in = (in + 1) % warehouseSize ;  // updates 'in' index to  the next position in  warehouse
        
      pthread_mutex_unlock(&mutex)  ;   // unlocked the mutex 
      sem_post(&full)  ; // there is now  1 more crop in warehouse
   }

   printf(" Farmer %d:", *(int *)far) ;  // Current state of warehouse 
   
   for (int x = 0 ; x < warehouseSize ; x++  )
   {   // crops are currently stored,  rooms that are still empty
      printf(" %c ", warehouse[x] )  ;
   }
    printf("\n") ;

   //...................................................................

    
}
void *ShopOwner(void *sho)
{   
/*
   1.Shop owner takes crops and makes that particular room empty.
   2.use mutex and semaphore for critical section.
   3.print which shop owner is taking which crops from which room inside the critical section.
   4.print the whole warehouse buffer outside of the critical section
   */

  //...................................................................
  for (int y = 0; y < MaxCrops; y++ )  // loop runs 5 times
   {
      sem_wait(&full ) ;
      // check if  crops available in  warehouse
      // full semaphore counts  number of crops present
      pthread_mutex_lock(&mutex) ;
      /// pthread_mutex_lock is used for, one and only 1 thread can access a shared resource at a time
      //shop owner is removing  crop .so doesnt allow other threads
      char temp = warehouse[out] ;
      //crop that is  removed will stored in temp
      
      printf(" Shop Owner %d: Remove crops %c from %d\n", *((int *)sho), temp , out);
      warehouse[out] = 'N' ;  //crop was removed thats why N
        
      out = (out + 1) % warehouseSize ;  //update out index to next position in  warehouse
      pthread_mutex_unlock(&mutex) ;   // unlocked the mutex 
      // allow other threads to access  warehouse
        
      sem_post(&empty);  //means  there is now 1 more empty space in  warehouse
   }
   printf(" ShopOwner%d:", *((int *)sho)) ;  //Print the current state of warehouse 
    
   for (int y = 0; y < warehouseSize; y++)
   {
      printf("%c", warehouse[y]) ;
   }
   printf("\n") ;





  //...................................................................
}
int main()
{   
   /*initializing thread,mutex,semaphore
    */
   pthread_t Far[5],Sho[5];
   pthread_mutex_init(&mutex, NULL);
   sem_init(&empty,0,warehouseSize);//when the warehouse is full thread will wait
   sem_init(&full,0,0);//when the warehouse is empty thread will wait


   int a[5] = {1,2,3,4,5}; //Just used for numbering the Farmer and ShopOwner


    /*create 5 thread for Farmer 5 thread for ShopOwner
    -------------------------------------------------
    -------------------------------------------------
    */

   //...................................................................
   for (int m = 0; m < warehouseSize; m++)   // number of threads to be  created
   {
      pthread_create(&Far[m], NULL, (void *)Farmer, &a[m]) ;
        //pthread_create  is used for creating  new thread
        //&Far[m] thread id will be stored for farmer
        //&a[i]  Pass the farmers id to thread


      pthread_create(&Sho[m], NULL, (void *)ShopOwner, &a[m]) ;
        //pthread_create  is used for creating  new thread
        //&Sho[m] thread id will be stored for  shop owner
        // &a[m]  Pass the shop owners id  to thread

   }
  
   for (int m = 0; m < warehouseSize; m++ )
   {
      pthread_join(Far[m], NULL) ;
        //wait for a thread to finish its execution
        // Far[m]  thread id of  farmer
        // not returning any value thats why null 

      pthread_join(Sho[m], NULL) ;
        //wait for a thread to finish its execution
        // Sho[i]  thread id of  shop owner
        // not returning any value thats why null 


   }

   //...................................................................
    
    
    //  Closing or destroying mutex and semaphore
   pthread_mutex_destroy(&mutex);
   sem_destroy(&empty);
   sem_destroy(&full);
    


   return 0;
    
}


