/*
David Schmetterling
Section 02
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "mystringPartA.h"


String *make_string(){
	char b;
	int i,size=0;
	String *createString = (String *) malloc (sizeof(String));
	createString->chars = (char *) malloc (sizeof(char));  //problem, only created space for struct not the dynamic array in struct
	b = getchar();
//	puts("hyyyh");
	while(b != '\n'){		
		*((createString->chars)+size) = b;  //remember at this point size = 0
		b = getchar();
		size++;
		createString->chars = (char *) realloc(createString->chars, size+1);
    }
	*((createString->chars)+size) = '\0';  //end of string marker so no need to return the size directly
	//new->len = strlen(new->chars);
	return createString;
}
