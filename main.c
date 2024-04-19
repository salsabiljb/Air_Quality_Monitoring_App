#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "capteur.h"
#include "qualite.h"
#include "date.h"

//fonction permettant de vider un fichier
void vider_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Impossible de vider le fichier %s.\n", nom_fichier);
        return;
    }
    fclose(fichier);
}

//************************************************************************************************************


//debut du programme principale
int main() {
    char rep[3];
    int id;
    int id_capteur ;
    char nom[256];
    
    Capteur* capteur;
    QualiteAir* qualite_air;
    
    //intiation des listes chainees
    Capteur* tete_capteurs = NULL;
    QualiteAir* tete_qualite_air = NULL;

    //charger les donnees dans les listes chainees 
    tete_qualite_air=lire_donnees_fichier_qualite(tete_qualite_air);
    tete_capteurs =lire_donnees_fichier_capteur(tete_capteurs);


   printf("\n************************************************************************************************************************************************************************");
   printf("                                                                                                ==========================================                                                         \n");
   printf("**************************************************************|    \\  ____  ___    __ ____       ___  *****************************************************************\n");
   printf("**************************************************************|_____||    ||   |    ||    ||   ||   | *****************************************************************\n");
   printf("**************************************************************|     ||    ||   |    ||    ||   ||     *****************************************************************\n");
   printf("**************************************************************|____/ |____||   ||___||____||___||     *****************************************************************\n");
   printf("                                                              ==========================================                                                         \n");


  int choix = 0;
  while (choix != 9) {
    printf("\n************************************************************************************************************************************************************************\n");
    printf("\n                                                              ");
    printf("1. Ajouter un capteur\n");
    printf("\n                                                              ");
    printf("2. Modifier un capteur\n");
    printf("\n                                                              ");
    printf("3. Supprimer un capteur\n");
    printf("\n                                                              ");
    printf("4. Ajouter une mesure de qualite de l'air\n");
    printf("\n                                                              ");
    printf("5. Afficher les capteurs\n");
    printf("\n                                                              ");
    printf("6. Afficher les mesures de qualite de l'air d'un capteur \n");
    printf("\n                                                              ");
    printf("7. Afficher les statistiques d'un capteur \n");
    printf("\n                                                              ");
    printf("8. Effacer\n");
    printf("\n                                                              ");
    printf("9. Quitter\n");    
    printf("\n************************************************************************************************************************************************************************\n");
    printf("\n                                                              ");
    printf("Veuillez entrer votre choix                  ");
    scanf("%d",&choix);

    switch (choix) {
      case 1:
        system("clear");
        do
        {
            do{
        printf("\n                                                              ");
        printf("Entrez l'ID du capteur: ");
        fflush(stdin);
        scanf("%d", &id);
            }while(trouver_capteur(tete_capteurs,id)!=NULL);
        printf("\n                                                              ");
        printf("Entrez le nom du capteur: ");
        fflush(stdin);
        scanf("%s", nom);
        capteur = creer_capteur(id, nom);
        ajouter_succes(&tete_capteurs, capteur) ;
        printf("\n");
        printf("\n                                                              ");
        printf("voulez-vous ajouter un capteur oui ou non :");
        scanf("%s",rep);
        }while(!strcmp(rep,"oui"));
        system("clear");
        break;
        
      case 2:
        system("clear");
        do{
        while(1){
        printf("\n                                                              ");
        printf("Entrez l'ID du capteur a modifier: ");
        fflush(stdin);
        scanf("%d", &id);
        Capteur* capteur = trouver_capteur(tete_capteurs, id);
        if (capteur != NULL) 
        break ;
        }
        printf("\n                                                              ");
        printf("Entrez le nouveau nom du capteur: ");
        fflush(stdin);
        scanf("%s", nom);
        modifier_capteur(tete_capteurs, id, nom);
        printf("\n                                                              ");
        printf("Modifie avec succes");
        printf("\n");  
        printf("\n                                                              ");
        printf("voulez-vous modifier un autre capteur oui ou non :");
        scanf("%s",rep);
        }while(!strcmp(rep,"oui"));
        system("clear");
        break;
        
      case 3:
        system("clear");
        do{
        while(1){
        printf("\n                                                              ");
        printf("Entrez l'ID du capteur a supprimer: ");
        fflush(stdin);
        scanf("%d", &id);
        Capteur* capteur = trouver_capteur(tete_capteurs, id);
        if (capteur != NULL) 
        break ;
        }
        supprimer_capteur(&tete_capteurs, id);
        supprimer_qualite(&tete_qualite_air,id);
        printf("\n                                                              ");
        printf("supprime avec succes");  
        printf("\n");
        printf("\n                                                              ");
        printf("voulez-vous supprimer un autre capteur oui ou non :");
        scanf("%s",rep);
        }while(!strcmp(rep,"oui"));
        system("clear");
        break;
        
      case 4:
        system("clear");
        do
       {
        tete_qualite_air = donner_qualite_air(tete_capteurs,tete_qualite_air); 
        printf("\n                                                              ");
        printf("voulez-vous ajouter une qualite oui ou non :");
        scanf("%s",rep);                                                         
       }while(!strcmp(rep,"oui"));
       system("clear");
        break;
        
      case 5:
        system("clear");
        printf("\n                                                              ");
        printf("Les Capteurs  :  \n");          
        afficher_capteurs(tete_capteurs);      
        break;
        
      case 6:
        system("clear");
        printf("\n                                                              ");
        printf("Les Qualites d'air   :  \n");  
        afficher_qualite_air(tete_qualite_air);
        break;
        
      case 7:
        system("clear");
        printf("\n                                                              ");
        printf("Statistiques Qualite d'air   :  \n"); 
        statistiques_qualite_air(tete_qualite_air);
        break;
        
      case 8:    
        system("clear");
        break; 
         
      case 9:
        system("clear");        
        vider_fichier(NOM_FICHIER_QUALITE_AIR);
        enregistrer_qualite_air(tete_qualite_air);
        vider_fichier(NOM_FICHIER_CAPTEURS);
        enregistrer_capteurs(tete_capteurs);
        printf("\n                                                              ");
        printf("Au revoir!\n");
        break;  
             
      default:
      
        printf("Choix non valide.\n");
        break;
    }
  }

  return 0;
}
