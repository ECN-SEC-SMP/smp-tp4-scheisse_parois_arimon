#ifndef UTILITAIRES_H
#define UTILITAIRES_H

#include <iostream>
#include "type_def.h"
#include "utilitaire_generation.h"

personne genererPersonne();
elementListe* creerElementListe(personne p);
void affichagePersonne(const personne &p);
bool egalitePersonne(const personne &p, const personne &p2);
bool comparerPersonne(const personne &p1, const personne &p2);
elementListe* ajouter(elementListe* tete, personne p);
void afficher(elementListe* tete);
int rechercher(elementListe* tete, personne p);
elementListe* supprimer(elementListe* tete, const personne &p);

#endif /* UTILITAIRES_H */

