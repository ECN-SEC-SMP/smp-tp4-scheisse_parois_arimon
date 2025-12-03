#ifndef TYPE_DEF_H
#define TYPE_DEF_H

/* Définitions de types pour TP4 - fichiers */

/* Tailles maximales (modifiable si besoin) */
#define MAX_NOM 100
#define MAX_PRENOM 100
#define TELEPHONE_LEN 10 /* 10 chiffres */

/* Structure personne : nom, prénom, téléphone (10 chiffres, chaîne sans espaces) */
typedef struct personne {
    char nom[MAX_NOM];
    char prenom[MAX_PRENOM];
    char telephone[TELEPHONE_LEN];
} personne;

/* Structure elementListe : contient une personne et les pointeurs pour une liste chaînée.
   Pour le bonus, la liste est doublement chaînée (suivant, precedent). */
typedef struct elementListe {
    personne info;
    struct elementListe *suivant;
    struct elementListe *precedent; /* peut être NULL si on n'utilise que simple chaînage */
} elementListe;

#endif /* TYPE_DEF_H */