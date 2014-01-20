correcteurortho
===============
1 Introduction

Dans cette feuille nous allons construire un correcteur orthographique. Notre correcteur sera
capable de corriger des mots comportant une seule erreur (un caractere oublié, un caractere en
trop, une inversion de lettre, ...).
Avant de commencer, voyons comment le programme est organise. Tout d’abord, pour eviter de
gerer les problemes d’accents et d’encodage qui en decoulent, nous nous limiterons a ecrire un
correcteur pour l’anglais. Le principe de fonctionnement est assez simple: etant donne un mot,
nous essayons de choisir la correction orthographique la plus probable pour ce mot (la ”correction”
peut-etre le mot d’origine). Il n’existe aucun moyen de savoir avec certitude le mot le plus probable
(par exemple, si on a le mot “larges”, celui-ci doit il etre remplace par “larger” ou “largest”?). Par
consequent nous allons utiliser un mecanisme probabiliste pour déterminer le mot de remplacement
qui semble le plus judicieux. Nous allons donc construire une liste de toutes les corrections possibles
pour ce mot et choisir parmi celles-ci la correction qui a la plus forte probabilite.
Considerons le mot mal orthographie m = ”thei”, et les deux corrections possibles c1 = ”the”
(l’utilisateur a tape une lettre en trop) et c2 = ”they” (l’utilisateur a tape une lettre a la place
d’une autre). Ici, notre programme choisira de remplacer m par c1 , car le mot “the” est plus
employe en anglais que “they”.

2 Principes
2.1 Corpus
La premiere tache consiste a se construire une table contenant des mots (anglais ici) et a leur
associer un poids en fonction de leur frequence dans la langue. Il existe de telles tables toutes
faites, mais nous allons ici la creer nous meme a partir d’un texte d’un volume conséquent. Pour
cela, nous allons prendre l’Illiade d’Homere et construire une table qui associera pour chaque
mot son nombre d’apparitions dans le texte. Cela constituera notre corpus sur lequel nous nous
baserons pour nos corrections orthographiques.
Pour la realisation de cette partie nous utiliserons les primitives Posix hcreate, hsearch et
hdestroy qui permettent de gerer des tables de hachage (tables dont l’acces est generalement tres
efficace). Pour comprendre comment utiliser ces tables, il vous suffit de regarder la page de manuel
de hcreate qui contient un exemple complet.
Note: Pour faciliter les comparaisons, tous les mots qui seront ranges dans la table devront etre
convertis en minuscules auparavant.

2.2 Corrections
Voyons maintenant comment  enumerer l’ensemble des corrections possibles pour un mot m. Nous
allons considerer ici des mots qui ne contiennent qu’une erreur. Une correction peut etre:
• un effacement (suppresion d’une lettre)
• une transposition (echange de deux lettres adjacentes)
• une modification (changement d’une lettre du mot m par une autre lettre de l’alphabet)
• une insertion (insertion d’une lettre de l’alphabet dans toutes les postions possibles de m.
Le nombre de corrections peut etre assez consequent puisque pour un mot de longueur n, nous
avons n effacements, n−1 transpositions, 26n modifications et 26(n+1) insertions. Par consequent,
le nombre de corrections potentielles pour un mot de longueur n est 54n + 25 (soit tout de meme
565 corrections pour un mots de 10 lettres!).

2.3 Correction d’un mot
Pour corriger un mot m nous allons utiliser un algorithme simple:
• si m est dans notre corpus, on renvoie ce mot.
• si le m n’est pas present,
– on construit l’ensemble E des corrections de m tel qu’il est defini dans la section
precedente.
– on revoie le mot de E qui est le plus probable (i.e. celui qui a le plus grand nombre
d’apparitions).
– si aucune correction de m n’apparait dans notre corpus, on renvoie m (qui apres tout
n’est peut-etre pas faux).

3 Travail demande
Prendre le fichier de ressources associe a ce TD, il contient le programme principal main.c, ainsi
que les fichiers d’entetes corpus.h, correct.h, hash.h et une partie de correct.c. Le fichier
correct.h contient des exemples exhaustifs sur les corrections a construire pour un mot de 4
lettres. Par ailleurs, il vous est aussi donne deux fichiers de tests: test1.c et test2.c. Le
premier permet de tester la table de hash et le second permet de tester la creation du corpus en
partant du fichier Data/strtok.txt. Pour votre programme final le corpus sera construit a partir
de Data/Iliad.txt
Vous devez travailler en binomes.
Ce que vous devez rendre: un programme complet (avec son Makefile) et un README indiquant
ce qui marche ou pas dans votre programme. N’oubliez pas d’indiquer les membre du binome. La
clarte du code et la qualite de la distribution (makefile correct et complet, respect des conventions
issues des fichier “.h”, ...) et la correction du programme interviendront dans la notation.
Pour info, voila la taille des fichiers de la correction:
$ wc -l corpus.c correct.c hash.c main.c
43 corpus.c
173 correct.c
92 hash.c
37 main.c
345 total

Date de remise du TD: 22 janvier 2014 – 23h59.
