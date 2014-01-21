#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "corpus.h"
#include "correct.h"

// chemin du fichier /home/user/Documents/prog C/TD6/correcteurortho/Distrib/Data/Iliad.txt

int main(int argc, char* argv[]){

	//init_corpus_from_file("./Data/Iliad.txt");

	/* test de hash.c */
	hash_table_create();
	hash_table_add("test");
	hash_table_search("test");
	hash_table_add("test");
	hash_table_search("test");
	hash_table_destroy();
	
	return 0;
}
