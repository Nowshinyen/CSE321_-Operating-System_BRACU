#include <stdio.h>
void erase_multiple_spaces(const char *sourceFile , const char *destinationFile) {
	FILE *input = fopen (sourceFile, "r") ;
	FILE *output = fopen (destinationFile, "w") ;
	char character ;
	int count = 0 ; //initial value 
 
	while ((character = fgetc(input)) != EOF ) {
    	if (character != ' ' && character != '\n' && character != '\t') {
        	if (!count && ftell(output) > 0 ) {
                fputc(' ', output) ;
        	}
        	fputc(character, output) ;
        	count = 1 ;
    	
        } else {
        	
        	count = 0 ;
    	}
	}
	fclose(input);
	fclose(output);
}
 
int main() {
	const char *sourceFile = "input_2b.txt" ;
	const char *destinationFile = "output_2b.txt" ;
    erase_multiple_spaces(sourceFile, destinationFile);
	return 0;
}

