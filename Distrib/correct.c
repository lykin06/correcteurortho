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
	int i,j,k,l=1;
	int length = strlen(word);
	//printf("deletions (%d mots):\n",length);

	// Boucle pour augmenter l'indice de la lettre a supprimer	
	for(i=0; i<length; ++i) {
		char *new_word = malloc(1000);
		// Boucle pour parcourir le mot
		for(j=0,k=0; j<length; ++j) {
			if(j==i) {
				continue; // On saute cette lettre
			}
			*(new_word+k)=*(word+j);
			++k;
		}
		// On ajoute le mot cree à la liste et on incremente l'index
		//printf("%d. %s\n",l,new_word);
		++l;
		possibles[index++] = new_word;
	}
	return index;
}

int transpositions(char* word, char** possibles,int index) {
	int i,j,k,l=1;
	int length = strlen(word);
	//printf("transpositions (%d mots):\n", length-1);
	// Boucle pour augmenter l'indice de la lettre a echanger	
	for(i=0; i<(length-1); ++i) {
		char *new_word = malloc(1000);
		// Boucle pour parcourir le mot
		for(j=0,k=0; j<length; ++j) {
			if(j==i) {
				*(new_word+k)=word[j+1];
				++k;
				*(new_word+k)=word[j];
				++k;
				++j; // On augmente l'indice car on a deja ajoute la prochaine lettre
				continue;
			}
			*(new_word+k)=*(word+j);
			++k;
		}
		// On ajoute le mot cree à la liste et on incremente l'index
		//printf("%d. %s\n",l,new_word);
		++l;
		possibles[index++] = new_word;
	}
	return index;
}

int alterations(char* word, char** possibles,int index) {	
	int i,j,k,l=1;
	int length = strlen(word);
	//printf("alterations (%d mots):\n", 26*length);

	// Boucle pour augmenter l'indice de la lettre a changer	
	for(i=0,k=0; i<(length*26); ++i) {
		if(i==(26*(k+1))) {
			++k;
		}

		char *new_word = malloc(1000);
		// Boucle pour parcourir le mot
		for(j=0; j<length; ++j) {
			if(j==k) {
				int lettre = i%26;
				*(new_word+k)=ALPHABET[lettre];
				continue;
			}
			*(new_word+j)=*(word+j);
		}
		// On ajoute le mot cree à la liste et on incremente l'index
		//printf("%d. %s\n",l,new_word);
		++l;
		possibles[index++] = new_word;
	}
	return index;
}

int inserts(char* word, char** possibles,int index) { 
	int i,j,k=0,l=1,m;
	int length = strlen(word);
	//printf("inserts (%d mots):\n", 26*(length+1));

	//On parcourt tous les emplacements et combinaisons d'insertion possibles
        for (i=0;i<(length+1)*26;i++){
			if(i==(26*(k+1))) {
				++k;
			}

            char * new_word=malloc(1000);
			// Boucle pour parcourir le mot
			for(j=0,m=0; j<(length+1); ++j) {
				if(j==k) {
					int lettre = i%26;
					*(new_word+j)=ALPHABET[lettre];
					continue;
				}
				*(new_word+j)=*(word+m);
				++m;
			}	

			//On le place dans la liste des corrections possibles
			//printf("%d. %s\n",l,new_word);
			++l;
            possibles[index++] = new_word;
        }
        return index;
}

char* better_candidate(char* word, char** possibles, int index){
	int i, data, best=0;
	char* best_candidate = word;
	
	// On parcourt toutes les corrections
	for(i=0; i<index; ++i){
		// Pointeur sur la ieme correction
		char *candidate=*(possibles+i);
		//printf("%s\n",candidate);

		// On regarde s'il est dans la table
		data = hash_table_search(candidate);

		if(data > best) {
			best = data;
			best_candidate = candidate;
		}
	}
		
	return best_candidate;
}

/*
	CETTE METHODE NE MARCHE PAS
*/
void destroy_possibles(char** possibles, int index){
	/*int i;
	//On supprime chaque élément 1 par 1
	for(i=0;i<index;i++){
		free(**(possibles+i));
	}
	//Puis on supprime la liste elle-même
	free(*possibles);*/
}

char** allocate_possibles(int length_word) {
	/*
		calcule du nombre de candidats:
		deletions : 		length_word				1*length_word
		transpositions : 	length_word-1 			2*length_word-1
		alterations : 		26*length_word 			28*length_word-1
		inserts :			26*length_word+26		54*length_word+25
	*/
	int nb_candidates = 54*length_word+25;
	int i;
	
	// Allocation de la liste:
	char** possibles=malloc(nb_candidates);
	for(i=0; i<nb_candidates; ++i) {
		*(possibles+i)=malloc(length_word+1);
	}

	return possibles;
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
