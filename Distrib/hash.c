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
	if (word) return 0;

	e.key = word;
	ep = hsearch(e, FIND);

	//hash.c:24:18: attention : transtypage d'un pointeur vers un entier de taille différente [-Wpointer-to-int-cast]
	//int i = ep ? 0: (int) ep->data;
	int *i = (int *) ep->data;

	return i;
//(ep ? (int)(ep->data) : 0);
//(ep ? ep->key : "NULL", ep ? (int)(ep->data) : 0);
//(ep->key == "NULL" ? 0: (int)(ep->data));
}

int hash_table_search(char *word) {
	int data = hash_table_is_present(word);
	if(data==0) {
		printf("%s n'est pas present dans la table.\n", word);
		return 0;
	}
	printf("%s est present %d fois.\n", word, data);
	return data;
}

void hash_table_add(char *word) {
	e.key = word;
	int i = hash_table_is_present(word);

	//hash.c:47:9: attention : assignment makes pointer from integer without a cast [enabled by default]
	e.data = i + 1;

	if(i) {
		hsearch(e, ENTER);
	}
}
