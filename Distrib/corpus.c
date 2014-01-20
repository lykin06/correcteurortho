#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "corpus.h"
#include "hash.h"

#define SIZE 50

int init_corpus_from_file(char *filename) {

	/*	test de strtok :	
	char toto[] ="BONJOUR TOTO FOO";
	printf("%s\n",strtok(toto," "));
	printf("%s\n",strtok(NULL," "));
	*/

	FILE *stream;
	int ch;
	int i = 0;
	int sz = SIZE;
	char *buffer = malloc(SIZE);
	
	//	Creation de la hash map
	hash_table_create();
	
	//	Ouverture du fichier en lecture
	stream = fopen(filename, "r"); 
	if(stream == NULL) { 
		Error("Unable to open file");
	}

	// On parcours notre fichier ligne par ligne
	while (((ch = getc(stream)) != EOF) {
		if (ch == "\n") {
			buffer[i] = ch;
			


			/* ajouter les mots de la ligne dans le fichier */
		} else {
			if (i == sz - 1) {
		  		sz = sz + sz/2;
		  		buffer = realloc(buffer, sz);
			}
			buffer[i++] = c;
		}
		
	}
 	printf("%s\n",buffer);
	free(buffer);
	fclose(stream);
}
