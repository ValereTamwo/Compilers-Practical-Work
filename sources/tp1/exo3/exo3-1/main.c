#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include "./head/init.h"



void ajouter_mot(MotPresence *tableau, int *taille, char *mot)
{
    strcpy(tableau[*taille].mot, mot);
    tableau[*taille].presence = 0;
    (*taille)++;
}

void lire_fichier_et_ajouter_mots(const char *nom_fichier, MotPresence *tableau, int *taille)
{
    char mot[15];
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(1); 
    }

    while (fscanf(fichier, "%s", mot) == 1) {
        ajouter_mot(tableau, taille, mot);
    }

    fclose(fichier);  
}

// Fonction pour construire l'automate
Automate *construire_automate()
{
    // Création des états
    Etat *etats[5];
    etats[0] = create_etat(0, false, true);
    etats[1] = create_etat(1, false, false);
    etats[2] = create_etat(2, false, false);
    etats[3] = create_etat(3, true, false);
    etats[4] = create_etat(4, false, false);

    // Remplissage des transitions
    remplirTrans(etats[0], 'm', etats[1]);
    remplirTrans(etats[1], 'u', etats[2]);
    remplirTrans(etats[2], 'r', etats[3]);

    // Création de l'automate
    Automate *automate = create_automate(4, *etats[0], etats);

    // Compléter l'automate avec Etat4
    completer_automate(automate, etats[4]);

    return automate;
}

// Fonction main qui appelle construire_automate
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nom_du_fichier>\n", argv[0]);
        return 1;
    }

    const char *nom_fichier = argv[1];
    printf("\n -------Exercice 3.1  on compte le nombre d'occurence du mot mur dans un fichier en utilisant un automate\n");

    // Appel de la fonction pour construire l'automate
    Automate *automate = construire_automate();
    
    MotPresence tableau[300]; 
    int taille_tableau = 0;

    // Appel de la fonction pour lire le fichier et ajouter les mots au tableau
    lire_fichier_et_ajouter_mots(nom_fichier, tableau, &taille_tableau);
    reconnaissance(automate,tableau,taille_tableau);

     int count_presence = 0;
    for (int i = 0; i < taille_tableau; i++) {
        if (tableau[i].presence == 1) {
            count_presence++;
        }
    }
    

     printf("Nombre de fois que mur apparait est de : %d\n", count_presence);


    return 0;
}
