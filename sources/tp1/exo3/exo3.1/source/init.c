#include "../head/init.h"
#include <stddef.h>
#include <string.h>

Etat *create_etat(int id, bool isFinal, bool isInit)
{
    Etat *etat = (Etat *)malloc(sizeof(Etat));
    

    etat->id = id;
    etat->isFinal = isFinal;
    etat->isInit = isInit;

    
    etat->trans = (Trans *)malloc(26 * sizeof(Trans));
    

    // Initialisation de la table de transitions
    for (int i = 0; i < 26; ++i) {
          // Le symbole est converti à partir du code ASCII
        etat->trans[i].destination = NULL;  // Destination par défaut (à définir selon la logique de votre application)
    }

    return etat;
}

void reconnaissance(Automate *automate, MotPresence *tableau, int taille)

{
    for (int i = 0; i < taille; i++) {
        Etat *etat_courant = &automate->initial;
        char *mot = tableau[i].mot;
        bool reconnu = false;
       
        
        for (int j = 0; j < strlen(mot); j++) {
             
           if (etat_courant->trans[mot[j] - 'a'].destination == NULL) {
                break;
            }

            etat_courant = etat_courant->trans[mot[j] - 'a'].destination;

        }
        
        if (etat_courant->isFinal) {
            reconnu = true;
        }
        
        tableau[i].presence = reconnu ? 1 : 0;
    }
}

void remplirTrans(Etat *etat, char symbol, Etat *destination)
{
    etat->trans[symbol -'a'].destination = destination;
}

Automate *create_automate(int num_etats, Etat initial, Etat **Etats)
{
    Automate *automate = (Automate *)malloc(sizeof(Automate));
    if (automate == NULL) {
        return NULL;  // Gestion d'erreur si l'allocation échoue
    }

    automate->initial = initial;
    automate->etats = Etats; // Correction ici pour utiliser Etats
    automate->num_etats = num_etats;

    return automate;
}


void completer_automate(Automate *automate, Etat *etat)
{
   

    for (int i = 0; i < automate->num_etats; i++) {
        Etat *current_etat = automate->etats[i];
        
        // Parcourir les transitions de l'état courant
        for (int j = 0; j < 26; j++) {
            if (current_etat->trans[j].destination == NULL) {
                current_etat->trans[j].destination = etat;
            }
        }
    }
}
