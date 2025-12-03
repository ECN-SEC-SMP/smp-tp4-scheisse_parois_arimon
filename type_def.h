#ifndef TYPE_DEF_H
#define TYPE_DEF_H

#include <string>
#define MAX_NOM 100
#define MAX_PRENOM 100
#define TELEPHONE_LEN 10

/* Structure personne : nom, prénom, téléphone (std::string au lieu de tableaux char) */
typedef struct personne {
    std::string nom;
    std::string prenom;
    std::string telephone;
} personne;

/* Structure elementListe : contient une personne et les pointeurs pour une liste chaînée.
   Pour le bonus, la liste est doublement chaînée (suivant, precedent). */
typedef struct elementListe {
    personne info;
    struct elementListe *suivant;
    struct elementListe *precedent;
} elementListe;

#endif /* TYPE_DEF_H */
