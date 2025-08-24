#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
	
	pid_t childPid, grandChildPid_1 , grandChildPid_2 , grandChildPid_3  ;
    int value =  1 ;  //initial 1
	childPid = fork() ;
      
	if (childPid == 0) {
		value++ ;
		printf("%d. Child Process ID: %d\n", value, getpid() ) ; 
		
		grandChildPid_1 = fork();
		value++;
		
        if (grandChildPid_1 == 0){
			printf("%d. Grand Child Process ID: %d\n", value, getpid()) ;
			return 0;
		}
		
		grandChildPid_2 = fork();
		value++;
		
        if (grandChildPid_2 == 0){
			printf("%d. Grand Child Process ID: %d\n", value, getpid()) ;
			return 0;
		}
		
		grandChildPid_3 = fork() ;
		value++;
		
        if (grandChildPid_3 == 0){
			printf("%d. Grand Child Process ID: %d\n", value, getpid()) ;
			return 0 ;
		}
	}
	else{
		printf("%d. Parent Process ID: %d\n", value, getpid() ) ;
		
        wait(NULL) ;
	}
}

