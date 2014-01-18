correcteurortho
===============
1
Introduction
Dans cette feuille nous allons construire un correcteur orthographique. Notre correcteur sera
capable de corriger des mots comportant une seule erreur (un caract`re oubli ́, un caract`re en
e
e
e
trop, une inversion de lettre, ...).
Avant de commencer, voyons comment le programme est organis ́. Tout d’abord, pour  ́viter de
e
e
g ́rer les probl`mes d’accents et d’encodage qui en d ́coulent, nous nous limiterons `  ́crire un
e
e
e
a e
correcteur pour l’anglais. Le principe de fonctionnement est assez simple:  ́tant donn ́ un mot,
e
e
nous essayons de choisir la correction orthographique la plus probable pour ce mot (la ”correction”
peut-ˆtre le mot d’origine). Il n’existe aucun moyen de savoir avec certitude le mot le plus probable
e
(par exemple, si on a le mot “larges”, celui-ci doit il ˆtre remplac ́ par “larger” ou “largest”?). Par
e
e
cons ́quent nous allons utiliser un m ́canisme probabiliste pour d ́terminer le mot de remplacement
e
e
e
qui semble le plus judicieux. Nous allons donc construire une liste de toutes les corrections possibles
pour ce mot et choisir parmi celles-ci la correction qui a la plus forte probabilit ́.
e
Consid ́rons le mot mal orthographi ́ m = ”thei”, et les deux corrections possibles c1 = ”the”
e
e
(l’utilisateur a tap ́ une lettre en trop) et c2 = ”they” (l’utilisateur a tap ́ une lettre ` la place
e
e
a
d’une autre). Ici, notre programme choisira de remplacer m par c1 , car le mot “the” est plus
employ ́ en anglais que “they”.
e
2
2.1
Principes
Corpus
La premi`re tˆche consiste ` se construire une table contenant des mots (anglais ici) et ` leur
e
a
a
a
associer un poids en fonction de leur fr ́quence dans la langue. Il existe de telles tables toutes
e
faites, mais nous allons ici la cr ́er nous mˆme ` partir d’un texte d’un volume cons ́quent. Pour
e
e
a
e
cela, nous allons prendre l’Illiade d’Hom`re et construire une table qui associera pour chaque
e
mot son nombre d’apparitions dans le texte. Cela constituera notre corpus sur lequel nous nous
baserons pour nos corrections orthographiques.
Pour la r ́alisation de cette partie nous utiliserons les primitives Posix hcreate, hsearch et
e
hdestroy qui permettent de g ́rer des tables de hachage (tables dont l’acc`s est g ́n ́ralement tr`s
e
e
e e
e
efficace). Pour comprendre comment utiliser ces tables, il vous suffit de regarder la page de manuel
de hcreate qui contient un exemple complet.
Note: Pour faciliter les comparaisons, tous les mots qui seront rang ́s dans la table devront ˆtre
e
e
convertis en minuscules auparavant.
2.2
Corrections
Voyons maintenant comment  ́num ́rer l’ensemble des corrections possibles pour un mot m. Nous
e
e
allons consid ́rer ici des mots qui ne contiennent qu’une erreur. Une correction peut ˆtre:
e
e
• un effacement (suppresion d’une lettre)
• une transposition ( ́change de deux lettres adjacentes)
e
• une modification (changement d’une lettre du mot m par une autre lettre de l’alphabet)
• une insertion (insertion d’une lettre de l’alphabet dans toutes les postions possibles de m.
Le nombre de corrections peut ˆtre assez cons ́quent puisque pour un mot de longueur n, nous
e
e
avons n effacements, n−1 transpositions, 26n modifications et 26(n+1) insertions. Par cons ́quent,
e
le nombre de corrections potentielles pour un mot de longueur n est 54n + 25 (soit tout de mˆme
e
565 corrections pour un mots de 10 lettres!).
2.3
Correction d’un mot
Pour corriger un mot m nous allons utiliser un algorithme simple:
• si m est dans notre corpus, on renvoie ce mot.
• si le m n’est pas pr ́sent,
e
– on construit l’ensemble E des corrections de m tel qu’il est d ́fini dans la section
e
pr ́c ́dente.
e e
– on revoie le mot de E qui est le plus probable (i.e. celui qui a le plus grand nombre
d’apparitions).
– si aucune correction de m n’apparaˆ dans notre corpus, on renvoie m (qui apr`s tout
ıt
e
n’est peut-ˆtre pas faux).
e
3
Travail demand ́
e
Prendre le fichier de ressources associ ́ ` ce TD, il contient le programme principal main.c, ainsi
ea
que les fichiers d’entˆtes corpus.h, correct.h, hash.h et une partie de correct.c. Le fichier
e
correct.h contient des exemples exhaustifs sur les corrections ` construire pour un mot de 4
a
lettres. Par ailleurs, il vous est aussi donn ́ deux fichiers de tests: test1.c et test2.c. Le
e
premier permet de tester la table de hash et le second permet de tester la cr ́ation du corpus en
e
partant du fichier Data/strtok.txt. Pour votre programme final le corpus sera construit ` partir
a
de Data/Iliad.txt
Vous devez travailler en binˆmes.
o
Ce que vous devez rendre: un programme complet (avec son Makefile) et un README indiquant
ce qui marche ou pas dans votre programme. N’oubliez pas d’indiquer les membre du binˆme. La
o
clart ́ du code et la qualit ́ de la distribution (makefile correct et complet, respect des conventions
e
e
issues des fichier “.h”, ...) et la correction du programme interviendront dans la notation.
Pour info, voila la taille des fichiers de la correction:
$ wc
43
173
92
37
345
-l corpus.c correct.c hash.c main.c
corpus.c
correct.c
hash.c
main.c
total
Date de remise du TD: 22 janvier 2014 – 23h59.
