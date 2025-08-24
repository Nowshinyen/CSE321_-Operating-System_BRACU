#include <stdio.h>


int main() {
    int num1 ;
    int num2 ;
    int total = 0 ; //initialy 0

    printf("Give any Range:\n") ;
    scanf("%d %d",  &num1 , &num2) ;
    printf("\n" ) ;
    printf("\n" ) ;
    printf("perfect numbers between the range:\n" ) ;

    
    for (int a = num1; a <= num2;  a++) {
        total = 0 ;
        
        for (int b = 1; b < a;  b++) {
            
            if (a % b == 0 ) {
                total = total+ b ;
            }
        }

        if  (total == a ) {
            printf("%d\n", a) ;
        }
    }
}


