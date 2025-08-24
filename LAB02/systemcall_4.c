#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

////// 
void function_for_sort(int *array, int count) {
    int change;
    for (int x = 0; x < count - 1; x++ ) {
        
        for (int y = 0; y< count - x - 1; y++ ) {
            
            if (array[y] < array[y + 1] ) {
                change = array[y] ;
                
                array[y] = array[y + 1] ;
                array[y+ 1] = change;
            }
        }
    }
    printf("Sorted in descending Order:\n") ;
    
    for (int x = 0; x < count; x++) {
        printf("%d\n", array[x]) ;
    }
}

/////
void odd_even_function(int *array, int count) {
    printf(" odd Numbers are:\n");
    
    for (int x = 0; x < count; x++) {
        
        if (array[x] % 2 != 0) {
            printf("%d\n", array[x]) ;
        }
    }

    printf(" even Numbers are:\n") ;
    
    for (int x = 0; x < count; x++) {
        
        if (array[x] % 2 == 0) {
            printf("%d\n", array[x]) ;
        }
    }
}

///////////////

int main(int argc, char *argv[]) {
    int temp[argc - 1];
    int count= argc - 1;
    for (int x = 1; x < argc; x++) {
        temp[x - 1] = atoi(argv[x] ) ;
    }
    pid_t fork_a = fork() ;
    
    if (fork_a == 0 )  {
        function_for_sort(temp, count)  ;
        return 0;
    }
    
    else {  
        wait(NULL);
        odd_even_function(temp, count ) ;
    }
}

