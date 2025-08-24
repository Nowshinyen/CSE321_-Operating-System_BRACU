#include <stdio.h>   
#include <unistd.h>
#include <string.h>

#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>


struct shared {    
    char sel[100] ;  //array to save  user's selection   a  ,w  , c
    
    int b ;   // will use for balance 
} ;
int main() {


    int file_1[2] ;  //array  to store read or write 
    char msg_b[20] ;
    struct shared *common_data ; //  use as pointer in shared memory
    int common_id ;  // store shared memory id
    common_id = shmget(IPC_PRIVATE, sizeof(struct shared), IPC_CREAT | 0666) ;
    // shmget is used for creating , access a shared memory segment
    /// IPC_PRIVATE  create  new shared memory segment, private 
    // IPC_CREAT | 0666 create new shared memory segment. it has read,write permissions for everyone 0666
    if (common_id < 0) {  // if shmget failss
        perror("Error") ;
    }

    common_data = (struct shared *) shmat (common_id, NULL, 0) ;
    
    if (common_data == (struct shared *)-1) {  // if return value  -1 means error 
        perror("Error") ;
    }
    common_data->b = 1000 ;   // starting balance 
    
    if (pipe(file_1) == -1) {
        perror("Error") ; // if pipe failss
        exit(1) ;
    }

    printf("Provide Your Input From Given Options: \n") ; 
    printf("1. Type a to Add Money \n2. Type w to Withdraw Money\n3. Type c to Check Balance\n") ;
    
    scanf("%c", common_data->sel);
    printf("Your selection: %s\n", common_data->sel) ;
    
    char user_choose= *(common_data->sel) ;  //stores in  user_chooose

    //..............................................................................
    pid_t child_pid = fork()  ;  // Creates new child process
    
    if (child_pid == -1) {
        perror("Error") ;
    }  

    if (child_pid == 0) {      // child process 
        int taka ;
        /////////////////////
        if (user_choose =='a' ){  //amount added
                printf("Enter amount to be added:\n") ;
                scanf("%d", &taka) ;

                if (taka > 0) {  //taka is greater than 0 it will add to the balance
                    common_data->b += taka ;
                    printf("Balance added successfully\n Updated balance after addition:\n%d\n", common_data->b) ;
                
                } else {  
                    printf("Adding failed, Invalid amount\n") ;
                }
        }
        /////////////////////
        else if(user_choose=='c'){   // shows current balance 
                
                printf("Your current balance is:\n%d\n", common_data->b) ;      
        }
        /////////////////////
        else if(user_choose=='w'){    // withdraw amount 
                printf("Enter amount to be withdrawn:\n") ;
                scanf("%d", &taka) ;  // store in tk

                if (taka > 0 && taka <= common_data->b) {  
                    //check tk is greater than 0 and less than or equal to the balance
                    common_data->b -= taka ;
                    printf("Balance withdrawn successfully\nUpdated balance after withdrawal:\n%d\n", common_data->b) ;
                
                } else {
                    printf("Withdrawal failed, Invalid amount\n") ;
                }
        }
        /////////////////////
        else{ 
                printf("Invalid selection\n" ) ;  //for invalid input
        }
        write(file_1[1], "Thank you for using", 20) ;  // sends message in parent process
        close(file_1[0]) ;
        
        close(file_1[1]) ;
        exit(0) ; //end child processs
    } 
    //.........................................................................................
    else {   
        wait(NULL) ; //parent process waits for  child to finish
        
        close(file_1[1]) ;  
        
        read(file_1[0], msg_b, sizeof(msg_b)) ;  //read  message from  child process 
        printf("%s\n",msg_b) ;
        close(file_1[0]) ;  
        
        shmdt((void *) common_data) ;
        shmctl(common_id, IPC_RMID, NULL) ; //Marks the shared memory segment 
    }
    return 0  ;  // successful execution
}

