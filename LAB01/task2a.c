#include <stdio.h>
int main() {
    float number_1, number_2,answer ;
    printf("Enter your 1st number:") ;
    scanf("%f", &number_1);
    
    printf("Enter your 2nd number:") ;
    scanf("%f", &number_2) ;
    
    
    if (number_1 > number_2) {
        answer = number_1 - number_2;
        printf("Final answer: %.2f\n", answer) ;
    }
    else if (number_1 < number_2) {
        answer = number_1 + number_2;
        printf("Final answer: %.2f\n", answer) ;
    }
    
    else if (number_1 == number_2) { 
        answer = number_1 * number_2;
        printf("Final answer: %.2f\n", answer) ;
    }
 
    return 0 ;

}


