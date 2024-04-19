#ifndef QUALITE_H_INCLUDED
#define QUALITE_H_INCLUDED

#define BONNE_QUALITE 0
#define MOYENNE_QUALITE 1
#define MAUVAISE_QUALITE 2

#define MIN_COV 100
#define MAX_COV 3000

#define NOM_FICHIER_QUALITE_AIR "qualite_air.txt"

#include "capteur.h"

typedef struct QualiteAir 
{
int id;
int id_capteur;
char date_heure[256];
int val_cov;
int etat_qualite;
struct QualiteAir* suivant;
} QualiteAir;

//fonction permettant de creer une qualite d'air
QualiteAir* creer_qualite_air(int id, int id_capteur, char* date_heure, int val_cov, int etat_qualite);

//fonction permettant de trouver une qualite d'air
QualiteAir* trouver_qualite(QualiteAir* tete, int id);

//fonction permettant d'ajouter une qualite d'air
void ajouter_qualite_air(QualiteAir** tete, QualiteAir* qualite_air);

//fonction permettant de supprimer une qualite d'air
void supprimer_qualite(QualiteAir** tete, int id);

//fonction permettant de determiner l'etat de la qualite d'air
int determiner_etat_qualite(int val_cov);

//fonction permettant d' obtenir lle message concernant une qualite d'air
char* obtenir_message_qualite(int etat_qualite);

//fonction permettant de donner une qualite d'air
QualiteAir* donner_qualite_air(Capteur* tete_capteurs,QualiteAir* tete_qualite_air) ;

//fonction permettant d'afficher une qualite d'air
void afficher_qualite_air(QualiteAir* tete);

//fonction permettant d'enregistrer une qualite d'air
void enregistrer_qualite_air(QualiteAir* tete);

//fonction permettant de donner les statistiques de la qualite d'air
void statistiques_qualite_air(QualiteAir* tete_qualite_air);

//fonction permettant de lire les donnees de la qualite d'air
QualiteAir* lire_donnees_fichier_qualite(QualiteAir* tete_qualite_air);

#endif // QUALITE_H_INCLUDED
