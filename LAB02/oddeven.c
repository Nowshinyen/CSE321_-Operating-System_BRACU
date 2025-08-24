#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    printf(" Odd Numbers: \n");
    
    for (int x = 1; x < argc; x++) {
        int temp = atoi(argv[x]) ;
        
        if (temp % 2 != 0) {
            printf("%d\n", temp) ;
        
        }
    }
    printf(" Even Numbers: \n") ;
    
    for (int x = 1; x < argc; x++ ) {
        int temp = atoi(argv[x] )  ;
        
        if (temp % 2 == 0 ) {
            printf("%d\n", temp )  ;
        }
    }
}

