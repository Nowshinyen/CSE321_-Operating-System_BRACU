#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int  main(int argc , char *argv[] )  {
    FILE *pointer = fopen(argv[1] , "a+") ;
    char empty_string[9999] ;  //array
    while (1)  {
        
        printf("enter a string: ") ;
        fgets(empty_string, sizeof(empty_string ), stdin) ;  
        if (strcmp(empty_string, "-1\n") == 0)  {
            break ;
        }
        fprintf(pointer, "%s\n", empty_string) ;
    }
    fclose(pointer) ;
}


