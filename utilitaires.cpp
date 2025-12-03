#include "utilitaires.h"
#include "utilitaire_generation.cpp"
#include "type_def.h"

personne genererPersonne() {
    personne p;
    p.nom = genererNomPrenom();
    p.prenom = genererNomPrenom();
    p.telephone = genererTel();
    return p;
}

elementListe* creerElementListe(personne p) {
    elementListe* elem = new elementListe;
    elem->info = p;
    elem->suivant = nullptr;
    elem->precedent = nullptr;
    return elem;
}

void affichagePersonne(personne p) {
    std::cout << "Nom: " << p.nom << std::endl;
    std::cout << "Prénom: " << p.prenom << std::endl;
    std::cout << "Téléphone: " << p.telephone << std::endl;
}