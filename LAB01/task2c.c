#include <stdio.h>
#include <string.h>
void password_checker(const char *word ) {
    //initial values
    int special_character  = 0 ;  
    int digit = 0 ;
    int lowercase = 0 ; 
    int uppercase = 0 ;


    for (int x = 0; word[x] != '\0'; x++ ) {
        
        if (word[x] == '_' || word[x] == '$' || word[x] == '#' || word[x] == '@') {
        	special_character = 1;
        	}
        
        if (word[x] >= '0' && word[x] <= '9'){ 
        	digit = 1 ;
        	}    

        if (word[x] >= 'a' && word[x] <= 'z'){ 
        	lowercase = 1 ;
        	}
        
        if (word[x] >= 'A' && word[x] <= 'Z'){ 
        	 uppercase = 1 ;
        	}   
    
        }
        if (special_character && digit && lowercase &&  uppercase  ) {
          printf("OK \n") ; 
    
    } else {
        if (! special_character)  printf("Special character missing\n");
        if (! digit)  printf("Digit missing\n");
        if (! lowercase)  printf("Lowercase character missing\n" );
        if (! uppercase)  printf("Uppercase character missing\n" );
       
    }
}
int main() {
    char word[1000];
    printf("Enter your password: ");
    scanf("%s",word);
    password_checker(word);
    return 0;
}

