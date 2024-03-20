#include "tache_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Chemin_Fichier "taches.json"

void lireTaches(Tache taches[Max_Taches], int *nbTaches) {
    FILE *fichier = fopen(Chemin_Fichier, "r");
    if (!fichier) {
        printf("Impossible d'ouvrir le fichier.\n");
        exit(1);
    }

    *nbTaches = 0;
    char ligne[Max_Taille_Tache];
    while (*nbTaches < Max_Taches && fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (sscanf(ligne, "{\"tache\":\"%999[^\"]\",\"priorite\":%d,\"estFait\":%d,\"dateEcheance\":\"%999[^\"]\"}",
                   taches[*nbTaches].tache, &taches[*nbTaches].priorite, &taches[*nbTaches].estFait, taches[*nbTaches].dateEcheance) == 4) {
            (*nbTaches)++;
        }
    }

    fclose(fichier);
}

void ecrireTaches(Tache taches[Max_Taches], int nbTaches) {
    FILE *fichier = fopen(Chemin_Fichier, "w");
    if (!fichier) {
        printf("Impossible d'ouvrir le fichier.\n");
        exit(1);
    }

    for (int i = 0; i < nbTaches; i++) {
        fprintf(fichier, "{\"tache\":\"%s\",\"priorite\":%d,\"estFait\":%d,\"dateEcheance\":\"%s\"}\n",
                taches[i].tache, taches[i].priorite, taches[i].estFait, taches[i].dateEcheance);
    }

    fclose(fichier);
}

void ajouterTache(Tache taches[Max_Taches], int *nbTaches) {

    char tache[Max_Taille_Tache];
    int priorite;
    int estFait;
    char dateEcheance[Max_Taille_Tache];

    printf("Entrez votre tache (ou 0 pour quitter):\n\n");
    fgets(tache, Max_Taille_Tache, stdin); // tach katbqa t3mr hta twsl max ou user ydir \n
    tache[strcspn(tache, "\n")] = '\0'; // katms7 entrer mn input w kadir null

    if (tache[0] == '0') {
        return;
    }

    printf("Entrez la priorite de votre tache (1-5):\n\n");
    scanf("%d", &priorite);
    getchar();
    printf("La tache est terminee? (Yes: 1, No: 0):\n\n");
    scanf("%d", &estFait);
    getchar();
    printf("Entrez la date d'echeance (AAAA-MM-JJ):\n\n");
    fgets(dateEcheance, Max_Taille_Tache, stdin);
    dateEcheance[strcspn(dateEcheance, "\n")] = '\0';

    strcpy(taches[*nbTaches].tache, tache); // affecter tach f *taches
    taches[*nbTaches].priorite = priorite;
    taches[*nbTaches].estFait = estFait;
    strcpy(taches[*nbTaches].dateEcheance, dateEcheance);
    (*nbTaches)++;
    ecrireTaches(taches, *nbTaches);

    printf("Tache ajoutee avec succes!\n\n");
}

void modifierTache(Tache taches[Max_Taches], int nbTaches) {
    int modfyTache;
    printf("Entrez le numero de la tache a modifier (ou 0 pour quitter):\n\n");
    for (int i = 0; i < nbTaches; i++) {
        printf("[%d]. %s | P:%d | Statut: %s | Echeance: %s\n",
               i + 1, taches[i].tache, taches[i].priorite,
               taches[i].estFait ? "[TERMINEE]" : "[NON TERMINEE]", taches[i].dateEcheance);
    }
    printf("\n");
    scanf("%d", &modfyTache);
    getchar();

    if (modfyTache == 0) {
        return;
    }
    else if (modfyTache > 0 && modfyTache <= nbTaches) {
        printf("Entrez votre nouvelle tache:\n\n");
        fgets(taches[modfyTache - 1].tache, Max_Taille_Tache, stdin);
        taches[modfyTache - 1].tache[strcspn(taches[modfyTache - 1].tache, "\n")] = '\0';
        printf("Entrez la nouvelle priorite de votre tache (1-5):\n\n");
        scanf("%d", &taches[modfyTache - 1].priorite);
        getchar();
        printf("La tache est terminee? (Yes: 1, No: 0):\n\n");
        int estFait;
        scanf("%d", &estFait);
        getchar();
        taches[modfyTache - 1].estFait = estFait;
        printf("Entrez la date d'echeance (AAAA-MM-JJ):\n\n");
        fgets(taches[modfyTache - 1].dateEcheance, Max_Taille_Tache, stdin);
        taches[modfyTache - 1].dateEcheance[strcspn(taches[modfyTache - 1].dateEcheance, "\n")] = '\0';
        ecrireTaches(taches, nbTaches);
        printf("Tache modifiee avec succes!\n\n");
    } else {
        printf("Tache invalide\n\n");
    }
}

void supprimerTache(Tache taches[Max_Taches], int *nbTaches) {
    int suppTache;
    printf("Entrez le numero de la tache a supprimer (ou 0 pour quitter):\n\n");
    for (int i = 0; i < *nbTaches; i++) {
        printf("[%d]. %s | P:%d | Echeance: %s\n",
               i + 1, taches[i].tache, taches[i].priorite, taches[i].dateEcheance);
    }
    printf("\n");
    scanf("%d", &suppTache);
    getchar();

    if (suppTache == 0) {
        return;
    }
    else if (suppTache > 0 && suppTache <= *nbTaches) {
        for (int i = suppTache - 1; i < *nbTaches - 1; i++) {
            strcpy(taches[i].tache, taches[i + 1].tache);
            taches[i].priorite = taches[i + 1].priorite;
            taches[i].estFait = taches[i + 1].estFait;
            strcpy(taches[i].dateEcheance, taches[i + 1].dateEcheance);
        }
        (*nbTaches)--; // katn9ss value dial taches
        ecrireTaches(taches, *nbTaches);
        printf("Tache supprimee avec succes!\n\n");
    } else {
        printf("Tache invalide\n\n");
    }
}

void afficherTaches(Tache taches[Max_Taches], int nbTaches) {
    printf("Les taches sauvegardees:\n\n");
    for (int i = 0; i < nbTaches; i++) {
        printf("[%d]. %s | P:%d | Echeance: %s", i + 1, taches[i].tache, taches[i].priorite, taches[i].dateEcheance);
        if (taches[i].estFait) {
            printf(" [TERMINEE]\n");
        } else {
            printf(" [NON TERMINEE]\n");
        }
    }
    printf("\n");
}

void filtrerTachesParPriorite(Tache taches[Max_Taches], int nbTaches) {

    int cpt = 1;

    printf("Taches filtree de la priorite elevee a la priorite basse :\n\n");

    for (int p = 5; p >= 1; p--) {
        for (int i = 0; i < nbTaches; i++) {
            if (taches[i].priorite == p) {
                printf("[%d]. %s | P:%d | Echeance: %s",
                       cpt, taches[i].tache, taches[i].priorite,
                       taches[i].dateEcheance);
                if (taches[i].estFait) {
                    printf(" [TERMINEE]\n");
                } else {
                    printf(" [NON TERMINEE]\n");
                }
                cpt++;
            }
        }
    }
    printf("\n");
}
