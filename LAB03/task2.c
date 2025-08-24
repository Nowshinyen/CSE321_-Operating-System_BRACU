
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>



struct msg{
  long int type ;  //type of message
  
  char txt[6] ;
} ;   

 
int main(){
        char user_workspace[6] ;  //Store workspace name
        char txt[100] ; // store strings
        int msg_id ;  // store id
        
        
        pid_t login, otp, p_id ;  
		// track all parent and child process
        struct msg store_message ;
        msg_id=msgget((key_t)12 , 0666|IPC_CREAT) ;
		//0666 means permissions for read & write by user, group, and others
        //IPC_CREAT create  message queue
        printf("Please enter the workspace name:\n") ;
        scanf("%s", user_workspace) ;
        int temp =strcmp(user_workspace, "cse321" ) ; //workspace name
	
        if(temp == 0 ){
		login = fork() ;  //create new process
		
        if (login == 0) {
		  msgrcv(msg_id,(void *)&store_message,sizeof(store_message.txt),1,IPC_NOWAIT) ;
		  
		  printf("OTP generator received workspace name from log in: %s\n\n", store_message.txt) ;
		  otp = getpid() ;  //for generating OTP
		  
		  sprintf(txt, "%d", otp) ;  //sprintf() converts OTP to a string
		  store_message.type=9 ;
		  strcpy(store_message.txt,txt) ;
		  
          msgsnd(msg_id,(void *)&store_message,sizeof(store_message.txt),0) ;
		  printf("OTP sent to log in from OTP generator: %s\n", txt) ;
		
		    p_id = fork() ;  //child of OTP generator
		    if (p_id == 0) {
			  //receiving, Sending OTP in mail proccess
		      msgrcv(msg_id,(void *)&store_message,sizeof(store_message.txt),7,IPC_NOWAIT) ;
		      printf("Mail received OTP from OTP generator: %s\n", store_message.txt) ;
		      
              store_message.type=8 ;
		      msgsnd(msg_id,(void *)&store_message,sizeof(store_message.txt),0) ;
		      printf("OTP sent to log in from mail: %s\n", store_message.txt) ;

		    } else {  //Sending OTP from OTP generator to mail
		      store_message.type=7 ;
		      
              strcpy(store_message.txt,txt) ;
		      msgsnd(msg_id,(void *)&store_message,sizeof(store_message.txt),0) ;
		      
			  printf("OTP sent to mail from OTP generator: %s\n", txt) ;
		      wait(NULL) ;  //wait for child to finish
		    }
		}
		else {
		    store_message.type=1 ;
			//parent send workspace name to OTP generator 
		    strcpy(store_message.txt,user_workspace) ;
		    msgsnd(msg_id,(void *)&store_message,sizeof(store_message.txt),0) ;
		    printf("Workspace name sent to otp generator from log in: %s\n\n", user_workspace) ;
		    
            wait(NULL) ;  //waiting for OTP generator to done
		    msgrcv(msg_id,(void *)&store_message,sizeof(store_message.txt),9,IPC_NOWAIT) ;
			//msgrcv read  OTP send by  OTP generator
		    char* otpGen = (char*)malloc(sizeof(store_message.txt) + 1) ;
		    strncpy(otpGen, store_message.txt, sizeof(store_message.txt)) ;
		    
            printf("Log in received OTP from OTP generator: %s\n", store_message.txt) ;
		    msgrcv(msg_id,(void *)&store_message,sizeof(store_message.txt),8,IPC_NOWAIT) ;
            //msgrcv read OTP from mail
		    
			char* otpMail = (char*)malloc(sizeof(store_message.txt) + 1) ;
		    strncpy(otpMail, store_message.txt, sizeof(store_message.txt)) ;
		    
            printf("Log in received OTP from mail: %s\n", store_message.txt) ;
		    if (strcmp(otpGen, otpMail) == 0) {
			  //Comparing  OTP from  OTP generator and mail	
		      
              printf("OTP Verified\n") ;
		    } 
		    
            else {
		        printf("OTP Incorrect\n") ;
		    }
		    
		  }
	}
	else {
          printf("Invalid workspace name\n") ;  // workspace name isnt cse321
          
          return 0 ;
          }

  return 0 ;
  
}

