#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qualite.h"
#include "capteur.h"
#include "date.h"


//fonction permettant de creer une qualite d'air
QualiteAir* creer_qualite_air(int id, int id_capteur, char* date_heure, int val_cov, int etat_qualite) {
    QualiteAir* qualite_air = malloc(sizeof(QualiteAir));
    qualite_air->id = id;
    qualite_air->id_capteur = id_capteur;
    strcpy(qualite_air->date_heure, date_heure);
    qualite_air->val_cov = val_cov;
    qualite_air->etat_qualite = etat_qualite;
    qualite_air->suivant = NULL;
    return qualite_air;
}


//************************************************************************************************************


//fonction permettant de trouver une qualite d'air
QualiteAir* trouver_qualite(QualiteAir* tete, int id){
	QualiteAir* courant = tete;
	while (courant != NULL) {
	if (courant->id == id) {
	return courant;
	}
	courant = courant->suivant;
	}
	return NULL;
}

//************************************************************************************************************


//fonction permettant d'ajouter une qualite d'air
void ajouter_qualite_air(QualiteAir** tete, QualiteAir* qualite_air) {
	QualiteAir* dernier = *tete;
	QualiteAir* courant = *tete;

	// verifier si la mesure existe deja dans la liste
	while (courant != NULL) {
	if (courant->id == qualite_air->id) {
	        printf("\n                                                              ");
		printf("la mesure de l ID '%d' existe deja.\n", qualite_air->id);
	return;
	}
	courant = courant->suivant;
	}

	// ajouter une mesure a la liste
	if (*tete == NULL) {
		*tete = qualite_air;
	} 
	else{
		while (dernier->suivant != NULL) {
			dernier = dernier->suivant;
	 }
	dernier->suivant = qualite_air;
	}
}

//************************************************************************************************************


//fonction permettant de supprimer une qualite d'air
void supprimer_qualite(QualiteAir** tete, int id) {
	QualiteAir* courant = *tete;
	QualiteAir* precedent = NULL;
	while(courant != NULL){
		while (courant != NULL && courant->id_capteur != id) {
			precedent = courant;
			courant = courant->suivant;
		}
		if (courant != NULL) {
			if (precedent == NULL) {
		    		*tete = courant->suivant;
		} 
		else{
			precedent->suivant = courant->suivant;
		}
		free(courant);
		}
	}
}

//************************************************************************************************************


//fonction permettant de determiner l'etat de la qualite d'air
int determiner_etat_qualite(int val_cov) {
	if (val_cov < 500) {
		return BONNE_QUALITE;
	} 
	else if (val_cov < 2000) {
		return MOYENNE_QUALITE;
	}
	else {
		return MAUVAISE_QUALITE;
	}
}

//************************************************************************************************************


//fonction permettant d' obtenir lle message concernant une qualite d'air
char* obtenir_message_qualite(int etat_qualite) {
	if (etat_qualite == BONNE_QUALITE) {
		return "La qualité de l'air est bonne";
	} 
	else if (etat_qualite == MOYENNE_QUALITE) {
		return "La qualité de l'air est moyenne";
	}
	else {
		return "La qualité de l'air est mauvaise";
	}
}

//************************************************************************************************************


//fonction permettant de donner une qualite d'air
QualiteAir* donner_qualite_air(Capteur* tete_capteurs,QualiteAir* tete_qualite_air) {
	int id;
	int id_capteur ;
	char date_heure[256];
	Date* date ;
	printf("\n                                                              ");
	printf("Entrez l'ID du capteur: ");
	fflush(stdin);
	scanf("%d", &id_capteur);
	Capteur* capteur = trouver_capteur(tete_capteurs, id_capteur);
	if (capteur == NULL) {
	        printf("\n                                                              ");
		printf("Capteur %d introuvable\n", id_capteur);
	return;
	}
	do{
	        printf("\n                                                              ");
		printf("Entrez l'ID de la mesure: ");
		fflush(stdin);
		scanf("%d", &id);
	}while(trouver_qualite(tete_qualite_air,id)!=NULL);
	date=saisir_date();
	date_to_string(date, date_heure);
	int val_cov = rand() % (MAX_COV - MIN_COV + 1) + MIN_COV;
	int etat_qualite = determiner_etat_qualite(val_cov);
	char* message = obtenir_message_qualite(etat_qualite);
	printf("\n                                                              ");
	printf("%s\n", message);
	QualiteAir* qualite_air = creer_qualite_air(id, id_capteur, date_heure, val_cov, etat_qualite);
	ajouter_qualite_air(&tete_qualite_air, qualite_air);
	printf("\n                                                              ");
        printf("Ajoute avec succes"); 
	return tete_qualite_air ;

}

//************************************************************************************************************


//fonction permettant d'afficher une qualite d'air
void afficher_qualite_air(QualiteAir* tete) {
	QualiteAir* courant = tete;
	while (courant != NULL) {
		char* message=obtenir_message_qualite(courant->etat_qualite);
		printf("Qualité de l'air enregistrée le %s par le capteur %d : %d COV (%s)\n",courant->date_heure, courant->id_capteur, courant->val_cov, message);
		courant = courant->suivant;
	}
}

//************************************************************************************************************


//fonction permettant d'enregistrer une qualite d'air
void enregistrer_qualite_air(QualiteAir* tete) {
	FILE* fichier = fopen(NOM_FICHIER_QUALITE_AIR, "w");
	if (fichier == NULL) {
	        printf("\n                                                              ");
		printf("Impossible d'ouvrir le fichier %s\n", NOM_FICHIER_QUALITE_AIR);
	return;
	}
	QualiteAir* courant = tete;
	while (courant != NULL) {
		fprintf(fichier, "%d	%d	%s	%d	%d\n", courant->id, courant->id_capteur, courant->date_heure, courant->val_cov, courant->etat_qualite);
		courant = courant->suivant;
	}
	fclose(fichier);
}

//************************************************************************************************************


//fonction permettant de donner les statistiques de la qualite d'air
void statistiques_qualite_air(QualiteAir* tete_qualite_air) {
    Date* debut;
    Date* fin ;
    char debut_str[DATE_INPUT_LENGTH];
    char fin_str[DATE_INPUT_LENGTH];
    Date* date;
    int id_capteur;
    printf("\n                                                              ");
    printf("Entrez l'ID du capteur: ");
    fflush(stdin);
    scanf("%d", &id_capteur);
    printf("\n                                                              ");
    printf("debut : ");
    debut=saisir_date();
    printf("\n                                                              ");
    printf("fin: ");
    fin=saisir_date();
    date_to_string(debut, debut_str);
    date_to_string(fin, fin_str);
    QualiteAir* courant = tete_qualite_air;
    int nb_bonne_qualite = 0;
    int nb_moyenne_qualite = 0;
    int nb_mauvaise_qualite = 0;
    while (courant != NULL) {
        if (courant->id_capteur == id_capteur && strcmp(courant->date_heure, debut_str) >= 0 && strcmp(courant->date_heure, fin_str) <= 0 ) {
        if (courant->etat_qualite == BONNE_QUALITE) {
        	nb_bonne_qualite++;
        }
        else if (courant->etat_qualite == MOYENNE_QUALITE) {
        	nb_moyenne_qualite++;
        }
        else {
        	nb_mauvaise_qualite++;
        }
        }
        courant = courant->suivant;
    }

    printf("Periode du %s au %s \n", debut_str, fin_str);
    printf("Bonne qualite : %d\n", nb_bonne_qualite);
    printf("Moyenne qualite : %d\n", nb_moyenne_qualite);
    printf("Mauvaise qualite : %d\n", nb_mauvaise_qualite);
    }

//************************************************************************************************************


//fonction permettant de lire les donnees de la qualite d'air
QualiteAir* lire_donnees_fichier_qualite(QualiteAir* tete_qualite_air) {
    //tete_qualite_air = NULL ;
    FILE* fichier_qualite_air = fopen(NOM_FICHIER_QUALITE_AIR, "r");
    if (fichier_qualite_air == NULL) {
        perror("Error opening file");
        return;
    }
    int id;
    int id_capteur;
    char date_heure[256];
    int val_cov;
    int etat_qualite;
    while (fscanf(fichier_qualite_air, "%d	%d	%[^	]	%d	%d", &id, &id_capteur, date_heure, &val_cov, &etat_qualite) == 5) {
        QualiteAir* qualite_air = creer_qualite_air(id, id_capteur, date_heure, val_cov, etat_qualite);
        ajouter_qualite_air(&tete_qualite_air, qualite_air);
    }

    fclose(fichier_qualite_air);
    return tete_qualite_air ;
}

//************************************************************************************************************
