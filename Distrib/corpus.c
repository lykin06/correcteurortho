#include <stdio.h>
#include <string.h>
#include "corpus.h"
#include "hash.h"

#define SIZE 1000

int init_corpus_from_file(char *filename) {

	/*	test de strtok :	
	char toto[] ="BONJOUR TOTO FOO";
	printf("%s\n",strtok(toto," "));
	printf("%s\n",strtok(NULL," "));
	*/

	char buffer[SIZE];
	char *word;
	
	//	Creation de la hash map
	hash_table_create();
	
	//	Ouverture du fichier en lecture
	FILE *stream = fopen(filename, "r");
	if(stream == NULL) { 
		printf("Unable to open file");
		return 0;
	}

	// On parcours notre fichier ligne par ligne
	while ( ( fgets(buffer,SIZE,stream) ) !=NULL) {
		// On decoupe la ligne mot par mot avec strtok
		word = strtok(buffer,SEPARATORS);
		while(word) {
			if(word != '\0' || word != NULL) {
				hash_table_add(word);
			}
			word = strtok(NULL,SEPARATORS);	
		}
		
	}
	fclose(stream);
	return 1;
}
