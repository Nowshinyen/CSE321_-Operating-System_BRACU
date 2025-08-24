#include <stdio.h>
#include <pthread.h>
#define counter 5


void* thread_function(void* arg) {
    int number= *((int*) arg);
    
    printf ("Thread-%d Running\n ", number) ; 
    printf ("Thread-%d Closed\n" , number) ;
    return NULL ;
}
////////
int main() {
    pthread_t threads[counter ]  ;
    int temp[counter]  ;
    for (int a = 0; a < counter; a++)  {
        
        
        temp[a] = a+ 1  ;
        pthread_create(&threads[a], NULL, thread_function, (void*) &temp[a]) ;
        pthread_join(threads[a], NULL)  ;
    }

    return 0;
}


