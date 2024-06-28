//  In this file we'll define the class InitAutomata that will be used to initialize the automata

#ifndef INIT_H
#define INIT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>



typedef struct Etat
{
    int id;
    bool estInit;
    bool estTerm;
    struct EnsEtat **transitions;
    int numTransitions;
}Etat;

typedef struct EnsEtat
{
    Etat **etats;
    int size;
    int capacity;
} EnsEtat;  

typedef struct Automate
{
    EnsEtat *etats;
    EnsEtat *initiaux;
} Automate;


// Definitions des fonctions

EnsEtat *createEnsEtat(int capacity);
// Déclarations des fonctions
Etat *createEtat(int id, bool estInit, bool estTerm);
void ajouteTransition(Etat *etat, char c, Etat *succ);
EnsEtat *createEnsEtat(int capacity);
void addEtatToEns(EnsEtat *ens, Etat *etat);
bool containsEtat(EnsEtat *ens, int id);
Automate *createAutomate(int capacity);
bool ajouteEtatSeul(Automate *automate, Etat *etat);
bool ajouteEtatRecursif(Automate *automate, Etat *etat);
bool estDeterministe(Automate *automate);
Automate *determinise(Automate *automate);
EnsEtat *accessibles(Automate *automate);
EnsEtat *coAccessibles(Automate *automate);
void elimineEtatsNonAccessibles(Automate *automate);
void elimineEtatsNonCoAccessibles(Automate *automate);
void printAutomate(Automate *automate);


// Exercices 3 - Section 2 of the

bool reconnaitAutomate(Automate *automate, char *chaine);
int compterOccurrences(char *mot, char *fichier);
Automate *construireAutomate(char *chaine);
// Déclarations des fonctions

// -----------------------nouvelle Approche Fin ----------------------------------------------------------------

typedef struct State
{
    int id;
    int is_final;
    struct Transition *transitions;
    int num_transitions;
}State;


typedef struct Transition
{
    char symbol;
    State *destination;
}Transition;

typedef struct Automata
{
    State *states;
    int num_states;
    State *start_state;
}Automata;

Automata
Initialise(int numstates, int numtransitions, int *finalstates, int startid);

#endif // INIT_H
