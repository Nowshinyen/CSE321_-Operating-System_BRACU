#include <stdio.h>   
#include <string.h>
void mail_adress_checker(char mail[]) {
    char latest[] = "@sheba.xyz" ;
    char previous[] = "@kaaj.com" ; 
    char *domain = strstr(mail, "@" ) ;
 
    if (domain != NULL ) {
        int previous_num = 1 ; //initial value
        int latest_num = 1 ;
        
        for (int x = 0;  x < strlen(latest); x++) {
            
            if (domain[x] != latest[x]) {
                latest_num = 0;
                
                break;
            }
        }
        //-------------------------------
        for (int y = 0; y < strlen(previous); y++) {
            
            if (domain[y] != previous[y]) {
                previous_num  = 0 ;
                
                break;
            }
        }
        
        
        if (latest_num) {
            printf("Email address is ok \n") ;
        } else if (previous_num) {
            printf("Email address is outdated\n") ;
        } else {
            printf("Unknown domain present\n") ;
        }
    } else {
        printf("Invalid \n") ;
    }
}
 
int main() {
    char mail_1[] = "fahmid@kaaj.com" ;
    mail_adress_checker(mail_1);
    char mail_2[] = "zaki@sheba.xyz" ; 
    mail_adress_checker(mail_2);
    return 0 ;
}

