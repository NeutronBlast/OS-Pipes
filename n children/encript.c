#include <string.h>
#include "encript.h"


int removeSpace(char * vector, int length){

    // To keep track of non-space character count 
    int count = 0; 

    // Traverse the given string. If current character 
    // is not space, then place it at index 'count++' 
    for (int i = 0; vector[i]; i++) 
        if (vector[i] != ' ') 
            vector[count++] = vector[i]; // here count is 
                                   // incremented 
    vector[count] = '\0'; 
    return strlen(vector);
 
}

void encriptarM(char message[], int inicio, int fin){
	for (inicio=inicio; inicio<=fin; inicio++){
		
		if(message[inicio]=='m' || message[inicio]=='M'){
			message[inicio]=48;	
		}
		
		if(message[inicio]=='u' || message[inicio]=='U'){
			message[inicio]=49;	
		}	
		
		if(message[inicio]=='r' || message[inicio]=='R'){
			message[inicio]=50;	
		}
		
		if(message[inicio]=='c' || message[inicio]=='C'){
			message[inicio]=51;	
		}
		
		if(message[inicio]=='i' || message[inicio]=='I'){
			message[inicio]=52;	
		}
		
		if(message[inicio]=='e' || message[inicio]=='E'){
			message[inicio]=53;	
		}
		
		if(message[inicio]=='l' || message[inicio]=='L'){
			message[inicio]=54;	
		}
		
		if(message[inicio]=='a' || message[inicio]=='A'){
			message[inicio]=55;	
		}
		
		if(message[inicio]=='g' || message[inicio]=='G'){
			message[inicio]=56;	
		}
		
		if(message[inicio]=='o' || message[inicio]=='O'){
			message[inicio]=57;	
		}
	}
	
}




void encriptar(char message[], int inicio, int fin){
	char ch;	
	for(inicio=inicio; inicio<=fin; inicio++){
		ch = message[inicio];
		
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + 2;
			
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}
			
			message[inicio] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + 2;
			
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			
			message[inicio] = ch;
		}
	}	
}
