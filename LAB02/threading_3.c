#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


int *initial  ; 
pthread_mutex_t temp = PTHREAD_MUTEX_INITIALIZER  ;
int find_ascii(char *arrayOfString) {
    int num = 0; // initially they are 0
    int token = 0  ;
    while(arrayOfString[token] != '\0') {
        num =num + arrayOfString[token]  ;
        token++  ;
    }
    return num  ;
}



void *threading(void *arg){
    char arrayOfString[9999] ;
    int add;
    pthread_mutex_lock(&temp) ;
    
    printf("Enter the name: \n" ) ;
    scanf("%s", arrayOfString) ;
    
    pthread_mutex_unlock(&temp) ;
    add = find_ascii(arrayOfString) ;
    pthread_exit((void*)(intptr_t)add) ;
}

////////
int main() {
    pthread_t array[3] ;
    int value[3] ;
    int x = 0  ;
    for (int y = 0; y < 3; y++){
        pthread_create(&array[y], NULL, threading, NULL) ;
    }
    for (int y = 0; y< 3; y++){
        
        pthread_join(array[y], (void**)&initial) ;
        value[x] = (int)(intptr_t)initial ;
        x++;
    }

   
    int temp_2 = 0;
    if (value[0] == value[1] && value[0] == value[2] && value[1] == value[2]) {
        temp_2 = 1;
    }

    else if (value[0] == value[1] || value[0] == value[2] || value[1] == value[2]) {
        temp_2 = 2;
    }

    else {
        temp_2 = 3;
    }

    
    if (temp_2 == 1 ) {
        printf("Youreka\n");
    }
    else if (temp_2 == 3 ) {
        printf("Hasta La Vista\n");
    }
    else if (temp_2 == 2) {
        printf("Miracle\n"  );
    }
    pthread_mutex_destroy(&temp)  ;
}


