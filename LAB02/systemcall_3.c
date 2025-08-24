#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main() {
    int value ;
    int temp ;
    value = 1 ;
    int fork_a =  fork() ;   ///create fork a
    if (fork_a<0) {
    printf("error" ) ;
    
    return 1;
    }	
    
    else if (fork_a > 0) {
        value = value+1  ;
        
        
        if (getpid() % 2 != 0) {
           value=value+1 ;
           int child_1 = fork() ;
        
        wait(&temp ) ;  
        }   //////
    }else{
    value+=1 ;
    int fork_b = fork() ; ///// create  fork b
    
    if (fork_b<0) {
    printf("error" ) ;
    return 1 ;
    }	
    
    
    
    else if (fork_b > 0) {
        value = value+1 ;
        
        
        if (getpid() % 2 !=  0){
            value=value+1  ;            
            int child_2=  fork();
        wait(&temp) ;
        }  //////
    
    }else {
    value = value+1 ;
    int fork_c = fork() ;  ///// create fork c
    
    
    if (fork_c<0){
    printf("error") ;
    return 1 ;
    }	
    
    else if (fork_c > 0){
        value = value+1 ;
        
        
        if (getpid() % 2 != 0){
            value = value+1 ;            
            int child_3= fork() ;
        wait(&temp);
        }
    }
    else{printf("total processes without Parent: %d\n", value) ;
        printf("total processes with Parent: %d\n", value+1 ) ;
       }  
    }
    }  
       return 0 ;
}





