#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
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

	return (ep ? (int)(ep->data) : 0);
//(ep ? ep->key : "NULL", ep ? (int)(ep->data) : 0);
//(ep->key == "NULL" ? 0: (int)(ep->data));
}

int hash_table_search(char *word) {
	int data = hash_table_is_present(word);
	if(data) {
		printf("%s n'est pas present dans la table.\n", word);
		return 0;
	}
	printf("%s est present %d fois.\n", word, data);
	return data;
}

void hash_table_add(char *word) {
	e.key = word;
	int i = hash_table_is_present(word);
	e.data = ++i;

	if(i) {
		hsearch(e, ENTER);
	}
}
