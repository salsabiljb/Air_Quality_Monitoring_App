all : prog
 	

# Cette règle indique comment construire la cible "prog" à partir des
# fichiers objets qualite.o, capteur.o, date.o et main.o.
# Le compilateur gcc est utilisé pour lier ces fichiers objets en un
# exécutable nommé "prog", en incluant les symboles de débogage (-g).

prog: qualite.o capteur.o date.o main.o
	gcc qualite.o capteur.o date.o main.o -o prog -g


# Les règles suivantes sont des règles de dépendance qui indiquent comment
# construire les fichiers objets à partir des fichiers sources C.

main.o: main.c
	gcc -c main.c -g
qualite.o: qualite.c
	gcc -c qualite.c -g
capteur.o: capteur.c
	gcc -c capteur.c -g
date.o: date.c
	gcc -c date.c -g

# Cette règle indique comment nettoyer les fichiers objets du projet en
# utilisant la commande rm.

clean :
	rm -rf *.o

# Cette règle indique comment nettoyer tous les fichiers générés pendant la
# compilation (y compris l'exécutable "prog") en utilisant la commande rm.

mrproper : clean
	rm -rf prog
