/*
 * correct.c	-- Correction d'un mot
 *
 * Copyright © 2013 Erick Gallesio - Polytech'Nice-Sophia <eg@unice.fr>
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date:  6-Jan-2013 07:28 (eg)
 * Last file update:  8-Jan-2013 23:19 (eg)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "correct.h"
#include "hash.h"


int deletions(char* word, char** possibles,int index) {
	int i,j,k;

	// Boucle pour augmenter l'indice de la lettre a supprimer	
	for(i=0; i<strlen(word); ++i) {
		char *new_word = malloc(1000);
		// Boucle pour parcourir le mot
		for(j=0,k=0; j<strlen(word); ++j) {
			if(j==i) {
				continue; // On saute cette lettre
			}
			*(new_word+k)=*(word+j);
			++k;
		}
		// On ajoute le mot cree à la liste et on incremente l'index
		printf("%s\n",new_word);
		possible[index++] = new_word;
	}
	return index;
}

int transpositions(char* word, char** possibles,int index) {
	int i,j,k;
	
	// Boucle pour augmenter l'indice de la lettre a echanger	
	for(i=0; i<(strlen(word)-1); ++i) {
		char *new_word = malloc(1000);
		// Boucle pour parcourir le mot
		for(j=0,k=0; j<strlen(word); ++j) {
			if(j==i) {
				*(new_word+k)=word[j+1];
				++k;
				*(new_word+k)=word[j];
				++k;
				++j; // On augmente l'indice car on a deja ajoute la prochaine lettre
			}
			*(new_word+k)=*(word+j);
			++k;
		}
		// On ajoute le mot cree à la liste et on incremente l'index
		printf("%s\n",new_word);
		possible[index++] = new_word;
	}
	return index;
}

int alterations(char* word, char** possibles,int index) {
	int i,j,k;
	// Boucle pour augmenter l'indice de la lettre a changer	
	for(i=0,k=0; i<(strlen(word)*26); ++i,++k) {
		if(k==strlen(word)) k=0;
		char *new_word = malloc(1000);
		// Boucle pour parcourir le mot
		for(j=0; j<strlen(word); ++j) {
			if(j==k) {
				*(new_word+j)=ALPHABET[i%26];
			}
			*(new_word+j)=*(word+j);
		}
		// On ajoute le mot cree à la liste et on incremente l'index
		printf("%s\n",new_word);
		possible[index++] = new_word;
		++k;
	}
	return index;
}

int inserts(char* word, char** possibles,int index) { 
        int i,j,k;
	//On parcourt tous les emplacements et combinaisons d'insertion possibles
        for (i=0,k=0;i<(strlen(word)+1)*26;i++){
                char * new_word=malloc(1000);

                //On recopie le mot initial dans le nouveau mot jusqu'à atteindre l'indice d'insertion
                for (j=0;j<i/26;j++){
                        *(new_word+j)=word[k];
                        k++;
                }

		//On insère le caractère au bon endroit
                *(new_word+j)=ALPHABET[i%26];
                j++;

                //On recopie le reste du mot initial dans le nouveau mot
                for (;j<(strlen(word)+1);j++){
                        *(new_word+j)=word[k];
                        k++;
                }

		//On le place dans la liste des corrections possibles
                *(posibles+index)=new_word;
                index++;
        }
        return index;
}

char* better_candidate(char* word, char** possibles, int index){
	  int i;
	  ENTRY best,*e;
	  ENTRY entry_possible;
	  for(i=0;i<index;i++){
		 char* possible=*(possibles+i);
		 entry_possible.key=possible;
		 e=hsearch(entry_possible,FIND);
		 if(e==NULL){
			if(e->data>best.data){
				*e=best;
			}
		 }
	  }
	return best.key;
}

void destroy_possibles(char** possibles, int index){
	int i;
	//On supprime chaque élément 1 par 1
	for(i=0;i<index;i++){
		free(*possibles+i);
	}
	//Puis on supprime la liste elle-même
	free(possibles);
}

static char *find_corrections(char *word)
{
  char **possibles = allocate_possibles(strlen(word));
  char *result;
  int index = 0;

  if (possibles == NULL) {
    fprintf(stderr, "cannot allocate the array of possibles");
    exit(EXIT_FAILURE);
  }

  /* construires une liste de mots possibles */
  index = deletions(word, possibles, index);
  index = transpositions(word, possibles, index);
  index = alterations(word, possibles, index);
  index = inserts(word, possibles, index);

  /*choisir le meilleur candidat entre word et les mots possibles */
  result = better_candidate(word, possibles, index);

  /* un peu de ménage avant de renvoyer le meilleur candidat */
  destroy_possibles(possibles, index);
  return result;
}

char *correct_word(char *word)
{
  return hash_table_is_present(word)? word: find_corrections(word);
}
