#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[] ) {
    int temp [argc-1] ;
    int change ;
    for (int x = 1; x < argc; x++) {
        temp[x - 1] = atoi(argv[x] ) ;

    }
    int count = argc - 1;
    for (int x = 0; x < count - 1; x++) {
        
        for (int y = 0; y < count - x - 1; y++) {
            
            if (temp[y] < temp[y + 1] ) {
                change = temp[y] ;
                temp[y]  = temp[y + 1] ;
                
                temp[y + 1] = change  ;
            }
        }
    }
    printf("Sorted in descending Orders:\n") ;
    for (int x = 0; x < count;  x++) {
        printf("%d\n" , temp[x] )  ;
    }
}

