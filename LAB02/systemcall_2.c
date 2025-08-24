#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(){

    pid_t no_one ;
    pid_t no_two ;
    no_one = fork(); //create child
    if (no_one < 0) {
        return 1;
    }
    else if (no_one == 0) {
        no_two = fork() ;

        if (no_two < 0) {
            return 1 ;
        }
        else if (no_two ==  0) {
            printf("I am Grandchild\n") ;
        }
        else {
            wait(NULL);
            printf("I am Child\n") ;
        }
    }


    else {
        wait(NULL) ;
        printf("I am Parent\n") ;
    }
    return 0;
}



