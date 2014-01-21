#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>
#include "hash.h"

ENTRY e, *ep;

void hash_table_create(void){
	hcreate(HASH_TABLE_SIZE);
}

void hash_table_destroy(void) {
	hdestroy();
}

int hash_table_is_present(char *word) {
	e.key = word;
	ep = hsearch(e, FIND);

	// On a pas trouvé l'entrée
	if(ep == NULL) {
		return 0;
	}
	return 1;
}

int hash_table_search(char *word) {
	if(hash_table_is_present(word) == 1) {
		return (int) ep->data;
	}
	return 0;
}

void hash_table_add(char *word) {

	char* lower=malloc(sizeof(word));
	int i;
	for(i=0;*(word+i);++i){
		if(*(word+i)>='A' && *(word+i)<='Z'){
			char letter=*(word+i);
			*(lower+i)=letter+'a'-'A';
		}
		else{
			*(lower+i)=*(word+i);
		}
	}

	e.key=lower;
	ep=hsearch(e,FIND);
	if (ep==NULL) {
		ENTRY newEntry;
		newEntry.key=lower;
		newEntry.data=1;
		hsearch(newEntry,ENTER);
	} else {
		ep->data++;
	}
}
