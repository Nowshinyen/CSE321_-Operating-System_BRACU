#include <stdio.h>
#include <string.h>
 int  palindrome_checker(char *str ) {

    char *last =str + strlen(str) - 1 ;
    char *first =str;
    
    while (last > first)  {
        
        if (*last != *first)  {
            return 0 ; 
        }
        last-- ;
        first++ ;
        
    }
    return 1 ; 
}
 
int main() {
    char str[1000] ;
 
    printf("enter a string to check palindrome: ") ;
    scanf("%s", str) ;
    if (palindrome_checker(str)) {
        printf("Palindrome\n") ;
    
    } else {
        printf("Not Palindrome\n") ;
    }
    return 0 ;
}

