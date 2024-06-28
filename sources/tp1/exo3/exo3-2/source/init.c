#include "../headers/init.h"
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>
// Cette partie initialise les ensembles d'etat
#define MAX_WORD_LENGTH 1024    

Etat *createEtat(int id, bool estInit, bool estTerm)
{
    Etat *etat = (Etat *)malloc(sizeof(Etat));
    etat->id = id;
    etat->estInit = estInit;
    etat->estTerm = estTerm;
    etat->transitions = (EnsEtat **)malloc(26 * sizeof(EnsEtat *)); // Initialiser les transitions
    for (int i = 0; i < 26; i++)
    {
        etat->transitions[i] = createEnsEtat(2);
    }
    etat->numTransitions = 0;
    return etat;
}

void ajouteTransition(Etat *etat, char c, Etat *succ)
{
    addEtatToEns(etat->transitions[c - 'a'], succ);
}

EnsEtat *createEnsEtat(int capacity)
{
    EnsEtat *ens = (EnsEtat *)malloc(sizeof(EnsEtat));
    ens->etats = (Etat **)malloc(capacity * sizeof(Etat *));
    ens->size = 0;
    ens->capacity = capacity;
    return ens;
}

void addEtatToEns(EnsEtat *ens, Etat *etat)
{
    if (ens->size >= ens->capacity)
    {
        ens->capacity *= 2;
        ens->etats = (Etat **)realloc(ens->etats, ens->capacity * sizeof(Etat *));
    }
    ens->etats[ens->size++] = etat;
}

bool containsEtat(EnsEtat *ens, int id)
{
    for (int i = 0; i < ens->size; i++)
    {
        if (ens->etats[i]->id == id)
            return true;
    }
    return false;
}

Automate *createAutomate(int capacity)
{
    Automate *automate = (Automate *)malloc(sizeof(Automate));
    automate->etats = createEnsEtat(capacity);
    automate->initiaux = createEnsEtat(capacity);
    return automate;
}

bool ajouteEtatSeul(Automate *automate, Etat *etat)
{
    if (containsEtat(automate->etats, etat->id))
        return false;
    addEtatToEns(automate->etats, etat);
    if (etat->estInit)
        addEtatToEns(automate->initiaux, etat);
    return true;
}

bool ajouteEtatRecursif(Automate *automate, Etat *etat)
{
    if (!ajouteEtatSeul(automate, etat))
        return false;
    for (int i = 0; i < 26; i++)
    {
        EnsEtat *ens = etat->transitions[i];
        for (int j = 0; j < ens->size; j++)
        {
            ajouteEtatRecursif(automate, ens->etats[j]);
        }
    }
    return true;
}

bool estDeterministe(Automate *automate)
{
    for (int i = 0; i < automate->etats->size; i++)
    {
        Etat *etat = automate->etats->etats[i];
        for (int j = 0; j < 26; j++)
        {
            EnsEtat *ens = etat->transitions[j];
            if (ens->size > 1)
                return false;
        }
    }
    return true;
}

void printAutomate(Automate *automate)
{
    printf("Automate:\n");
    printf("--------\n");

    printf("Etats:\n");
    for (int i = 0; i < automate->etats->size; i++)
    {
        Etat *etat = automate->etats->etats[i];
        printf("Etat %d - Initial: %s - Terminal: %s\n", etat->id, etat->estInit ? "Oui" : "Non", etat->estTerm ? "Oui" : "Non");
        printf("Transitions:\n");
        for (int j = 0; j < 26; j++)
        {
            EnsEtat *transitions = etat->transitions[j];
            if (transitions->size > 0)
            {
                printf("\t%c -> ", 'a' + j);
                for (int k = 0; k < transitions->size; k++)
                {
                    printf("%d ", transitions->etats[k]->id);
                }
                printf("\n");
            }
        }
        printf("\n");
    }
}

// ---------------------------------- 1er approche ---------------------------------------------------------------

Automata Initialise(int numstates, int numtransitions, int* finalstates, int startid){

    // Creation des etats
    Automata automata;
    automata.num_states = numstates;
    automata.states = (State*)malloc(numstates*sizeof(State));

    // Definition de l'etat Initial
    automata.start_state = &automata.states[startid];


    // Initialisation des etats
    for (int i = 0; i<numstates; i++){
        automata.states[i].id= i;
        automata.states[i].is_final = 0;
        automata.states[i].num_transitions = 0;
        automata.states[i].transitions =  NULL;
    }

    // Ajout des transitions
}


// Calcul du nombres d'occurrences d'un terme

Automate *construireAutomate(char *chaine)
{
    int length = strlen(chaine);
    Automate *automate = createAutomate(length + 1);

    Etat *etatPrecedent = createEtat(0, true, false);
    ajouteEtatSeul(automate, etatPrecedent);

    for (int i = 0; i < length; i++)
    {
        Etat *etatSuivant = createEtat(i + 1, false, i == length - 1);
        ajouteTransition(etatPrecedent, chaine[i], etatSuivant);
        ajouteEtatSeul(automate, etatSuivant);
        etatPrecedent = etatSuivant;
    }

    return automate;
}

bool reconnaitAutomate(Automate *automate, char *chaine)
{
    Etat *etatCourant = automate->initiaux->etats[0];
    int length = strlen(chaine);
    for (int i = 0; i < length; i++)
    {
        EnsEtat *ens = etatCourant->transitions[chaine[i] - 'a'];
        if (ens->size == 0)
        {   
            return false;
        }

        etatCourant = ens->etats[0];
    }

    return etatCourant->estTerm;
}


// Comptons le nombre d'occurences
int compterOccurrences(char *mot, char *fichier)
{
    FILE *file = fopen(fichier, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", fichier);
        return -1;
    }

    Automate *automate = construireAutomate(mot);

    printAutomate(automate);

    int occurrences = 0;
    char ligne[1024]; // Assurez-vous que la taille de la ligne est suffisante pour les lignes dans le fichier

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) == 1)
    {
        printf("%s\n", word);

        if (reconnaitAutomate(automate, word))
         {
             occurrences++;
         }
    }

    // while (fgets(ligne, sizeof(ligne), file))
    //     {
    //         char *motLigne = strtok(ligne, " ");
    //         {
    //             printf("%s\n", motLigne);

    //             // while (motLigne != NULL)
    //             //  if (reconnaitAutomate(automate, motLigne))
    //             //  {
    //             //      occurrences++;
    //             //  }
    //             //  motLigne = strtok(NULL, " \t\n");
    //          }
    // }

    fclose(file);
    return occurrences;
}