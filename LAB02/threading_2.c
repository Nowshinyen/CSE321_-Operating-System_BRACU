#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void* threading(void* args ) ;
int count = 0;


int main() {
	for (int a = 0; a < 5; a++) {
    	pthread_t thread ;
    	
        pthread_create(&thread, NULL, threading, NULL);
    	
        pthread_join(thread, NULL);
    	count++ ;
	}
}


void* threading(void* args  ) {
	int threadCount = 5;
	
    for (int a = 1; a <= 5; a++) {
    	printf("Thread %d prints %d\n", count, (count * threadCount) + a ) ;
	}
}


