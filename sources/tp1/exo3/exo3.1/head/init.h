#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Définition de la structure Trans avant Etat
typedef struct {
    struct Etat *destination; // Utilisation de struct Etat pour éviter une référence incomplète
} Trans;
typedef struct {
    char mot[15];  
    int presence;    
} MotPresence;

typedef struct Etat {
    int id;
    bool isFinal;
    bool isInit;
    Trans *trans;
} Etat;

typedef struct {
    int num_etats;
    Etat initial;
    Etat **etats; 
} Automate;

// Déclarations des fonctions
Etat *create_etat(int id, bool isFinal, bool isInit);
void ajouter_etat(Automate *automate ,Etat *etat) ;
void remplirTrans(Etat *etat, char symbol, Etat *destination);
Automate *create_automate(int num_etats, Etat initial, Etat **Etats);
void completer_automate(Automate *automate, Etat *etat);
void reconnaissance(Automate *automate, MotPresence *tableau, int taille);


#endif // INIT_H
