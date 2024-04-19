#ifndef CAPTEUR_H_INCLUDED
#define CAPTEUR_H_INCLUDED

#define NOM_FICHIER_CAPTEURS "capteurs.txt"

typedef struct Capteur
{
int id;
char nom[256];
struct Capteur* suivant;
} Capteur;


//fonction permettant de creer un capteur
Capteur* creer_capteur(int id, char* nom);

//fonction permettant d' ajouter un capteur
void ajouter_capteur(Capteur** tete, Capteur* capteur);

//fonction qui affiche un message de succes
void ajouter_succes(Capteur** tete, Capteur* capteur);

//fonction permettant de trouver un capteur dans la liste chainee par l id
Capteur* trouver_capteur(Capteur* tete, int id);

//fonction permettant de modifier le nom d'un capteur 
void modifier_capteur(Capteur* tete, int id, char* nom);

//fonction permettant de supprimer un capteur dans la liste chainee
void supprimer_capteur(Capteur** tete, int id);

//fonction permettant d'afficher les capteurs de la liste chainee
void afficher_capteurs(Capteur* tete);

//fonction permettant de enregistrer la liste chainee des capteurs dans un fichier
void enregistrer_capteurs(Capteur* tete);

//fonction permettant de charger la liste chainee des capteurs d'un fichier
Capteur* lire_donnees_fichier_capteur(Capteur* tete_capteurs);


#endif // CAPTEUR_H_INCLUDED
