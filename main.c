#include <stdio.h>
#include "tache_manager.h"

int main() {
    int choix;
    Tache taches[Max_Taches];
    int nbTaches = 0;

    while (true) {
        printf("Menu de Selection:\n\n[1]. Ajouter une tache\n[2]. Modifier une tache\n[3]. Supprimer une tache\n[4]. Afficher touts les taches\n[5]. Filtrer les taches par priorite\n[6]. Quitter\n\n");
        scanf("%d", &choix);
        getchar();

        lireTaches(taches, &nbTaches);

        switch (choix) {
            case 1:
                ajouterTache(taches, &nbTaches);
                afficherTaches(taches, nbTaches);
                break;

            case 2:
                modifierTache(taches, nbTaches);
                afficherTaches(taches, nbTaches);
                break;

            case 3:
                supprimerTache(taches, &nbTaches);
                afficherTaches(taches, nbTaches);
                break;

            case 4:
                afficherTaches(taches, nbTaches);
                break;

            case 5:
                filtrerTachesParPriorite(taches, nbTaches);
                break;

            case 6:
                printf("Au revoir!\n");
                return 0;

            default:
                printf("Choix invalide\n\n");
        }
    }

    return 0;
}
