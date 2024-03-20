#ifndef TACHE_MANAGER_H
#define TACHE_MANAGER_H

#include <stdbool.h>

#define Max_Taches 100
#define Max_Taille_Tache 1000

typedef struct {
    char tache[Max_Taille_Tache];
    int priorite;
    bool estFait;
    char dateEcheance[Max_Taille_Tache];
} Tache;

void lireTaches(Tache taches[Max_Taches], int *nbTaches);
void ecrireTaches(Tache taches[Max_Taches], int nbTaches);
void ajouterTache(Tache taches[Max_Taches], int *nbTaches);
void modifierTache(Tache taches[Max_Taches], int nbTaches);
void supprimerTache(Tache taches[Max_Taches], int *nbTaches);
void afficherTaches(Tache taches[Max_Taches], int nbTaches);
void filtrerTachesParPriorite(Tache taches[Max_Taches], int nbTaches);

#endif /* TACHE_MANAGER_H */
