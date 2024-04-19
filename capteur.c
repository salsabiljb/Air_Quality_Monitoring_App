#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "capteur.h"



//fonction permettant de creer un capteur
Capteur* creer_capteur(int id, char* nom) {
	Capteur* capteur = malloc(sizeof(Capteur));
	capteur->id = id;
	strcpy(capteur->nom, nom);
	capteur->suivant = NULL;
	return capteur;
}

//************************************************************************************************************


//fonction permettant d'ajouter un capteur
void ajouter_capteur(Capteur** tete, Capteur* capteur) {
	Capteur* dernier = *tete;

	// ajouter un capteur a la fin du liste
	if (*tete == NULL) {
		*tete = capteur;
	} 
	else {
		while (dernier->suivant != NULL) {
			dernier = dernier->suivant;
		}
	dernier->suivant = capteur;
	}
}

//************************************************************************************************************

//fonction qui affiche un message de succes
void ajouter_succes(Capteur** tete, Capteur* capteur){
    ajouter_capteur(tete,capteur);
    printf("\n                                                              ");
    printf("Ajoute avec succes"); 
    return ;
}

//************************************************************************************************************


//fonction permettant de trouver un capteur dans la liste chainee par l id
Capteur* trouver_capteur(Capteur* tete, int id) {
	Capteur* courant = tete;
	while (courant != NULL) {
	if (courant->id == id) {
	return courant;
	}
	courant = courant->suivant;
	}
	return NULL;
}

//************************************************************************************************************


//fonction permettant de modifier le nom d'un capteur 
void modifier_capteur(Capteur* tete, int id, char* nom) {
	Capteur* capteur = trouver_capteur(tete, id);
	if (capteur != NULL) {
		strcpy(capteur->nom, nom);
	}
}

//************************************************************************************************************


//fonction permettant de supprimer un capteur dans la liste chainee
void supprimer_capteur(Capteur** tete, int id) {
	Capteur* courant = *tete;
	Capteur* precedent = NULL;
	while (courant != NULL && courant->id != id) {
	precedent = courant;
	courant = courant->suivant;
	}
	if (courant != NULL) {
		if (precedent == NULL) {
		    *tete = courant->suivant;
		} 
		else {
		    precedent->suivant = courant->suivant;
		}
		free(courant);
	}
}

//************************************************************************************************************


//fonction permettant d'afficher les capteurs de la liste chainee
void afficher_capteurs(Capteur* tete) {
	Capteur* courant = tete;
	while (courant != NULL) {
		printf("Capteur %d : %s\n", courant->id, courant->nom);
		courant = courant->suivant;
	}
}

//************************************************************************************************************


//fonction permettant de enregistrer la liste chainee des capteurs dans un fichier
void enregistrer_capteurs(Capteur* tete) {
	FILE* fichier = fopen(NOM_FICHIER_CAPTEURS, "w");
	if (fichier == NULL) {
		printf("Impossible d'ouvrir le fichier %s\n", NOM_FICHIER_CAPTEURS);
	return;
	}
	Capteur* courant = tete;
	while (courant != NULL) {
		fprintf(fichier, "%d %s\n", courant->id, courant->nom);
		courant = courant->suivant;
	}
	fclose(fichier);
}

//************************************************************************************************************


//fonction permettant de charger la liste chainee des capteurs d'un fichier
Capteur* lire_donnees_fichier_capteur(Capteur* tete_capteurs) {
	//tete_capteurs = NULL;
	FILE* fichier_capteurs = fopen(NOM_FICHIER_CAPTEURS, "r");
	if (fichier_capteurs == NULL) {
		perror("Error opening file");
	return;
	}

	int id;
	char nom[256];
	while (fscanf(fichier_capteurs, "%d %s", &id, nom) == 2) {
		Capteur* capteur = creer_capteur(id, nom);
		ajouter_capteur(&tete_capteurs, capteur);
	}

	fclose(fichier_capteurs);
	return tete_capteurs ;
}

//************************************************************************************************************
