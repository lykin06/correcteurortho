#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "correct.h"
#include "corpus.h"
#include "hash.h"

void hash_table_create(void){
	
	char toto[] ="BONJOUR TOTO FOO";
	printf("%s\n",strtok(toto," "));
	printf("%s\n",strtok(NULL," "));


}
