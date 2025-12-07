#include "utilitaires.h"
#include "utilitaire_generation.h"
#include "type_def.h"
#include <tuple>

personne genererPersonne() {
    personne p;
    p.nom = genererNomPrenom("Noms_TP4.txt", 1000);
    p.prenom = genererNomPrenom("Prenoms_TP4.txt", 11612);
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

void affichagePersonne(const personne &p) {
    std::cout << "Nom: " << p.nom << std::endl;
    std::cout << "Prénom: " << p.prenom << std::endl;
    std::cout << "Téléphone: " << p.telephone << std::endl;
}

bool egalitePersonne(const personne &p, const personne &p2) {
    return (p.nom == p2.nom) && (p.prenom == p2.prenom) && (p.telephone == p2.telephone);
}

bool comparerPersonne(const personne &p1, const personne &p2) {
    return std::tie(p1.nom, p1.prenom, p1.telephone) < std::tie(p2.nom, p2.prenom, p2.telephone);
}

elementListe* ajouter(elementListe* tete, personne p) {
    // si la liste est vide, créer et retourner le nouvel élément
    if (tete == nullptr) {
        return creerElementListe(p);
    }

    elementListe* cur = tete;
    elementListe* prev = nullptr;

    // parcourir jusqu'au premier élément qui n'est pas < p
    while (cur != nullptr && comparerPersonne(cur->info, p)) {
        prev = cur;
        cur = cur->suivant;
    }

    // si on a trouvé une personne identique, ne pas ajouter
    if (cur != nullptr && egalitePersonne(cur->info, p)) {
        return tete;
    }
    // si prev existe et est identique (cas où cur est nullptr et le dernier élément est égal)
    if (prev != nullptr && egalitePersonne(prev->info, p)) {
        return tete;
    }

    elementListe* nouveau = creerElementListe(p);

    // insertion en tête
    if (prev == nullptr) {
        nouveau->suivant = tete;
        if (tete) tete->precedent = nouveau;
        return nouveau;
    }

    // insertion en fin
    if (cur == nullptr) {
        prev->suivant = nouveau;
        nouveau->precedent = prev;
        return tete;
    }

    // insertion entre prev et cur
    prev->suivant = nouveau;
    nouveau->precedent = prev;
    nouveau->suivant = cur;
    cur->precedent = nouveau;
    return tete;
}

void afficher(elementListe* tete) {
    elementListe* cur = tete;
    while (cur != nullptr) {
        affichagePersonne(cur->info);
        cur = cur->suivant;
    }
}

int rechercher(elementListe* tete, personne p) {
    int index = 0;
    elementListe* cur = tete;
    while (cur != nullptr) {
        if (egalitePersonne(cur->info, p)) return index;
        cur = cur->suivant;
        ++index;
    }
    return -1;
}

elementListe* supprimer(elementListe* tete, const personne &p) {
    elementListe* cur = tete;
    while (cur != nullptr) {
        if (egalitePersonne(cur->info, p)) {
            elementListe* next = cur->suivant;
            elementListe* prev = cur->precedent;
            if (prev) prev->suivant = next;
            if (next) next->precedent = prev;
            if (cur == tete) tete = next;
            delete cur;
            return tete;
        }
        cur = cur->suivant;
    }
    return tete;
}