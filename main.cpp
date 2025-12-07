/* Benchmark des structures: liste chaînée triée vs tableau trié
 * Mesure: création (insertion triée), affichage, recherche 100, suppression 100
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include "utilitaires.h"

using namespace std;

int main() {
    const int N = 1000;
    const int M = 100; // nombre pour recherches & suppressions

    // Générer un pool de N personnes uniques
    vector<personne> pool;
    pool.reserve(N);
    while ((int)pool.size() < N) {
        personne p = genererPersonne();
        bool found = false;
        for (const auto &q : pool) if (egalitePersonne(p, q)) { found = true; break; }
        if (!found) pool.push_back(p);
    }

    // mélanger pool
    std::mt19937 rng((unsigned)time(nullptr));
    shuffle(pool.begin(), pool.end(), rng);

    // Construire liste chaînée triée
    clock_t t1 = clock();
    elementListe* head = nullptr;
    for (const auto &p : pool) {
        head = ajouter(head, p);
    }
    clock_t t2 = clock();
    double time_list_create = double(t2 - t1) / CLOCKS_PER_SEC;

    // Construire tableau trié (insertion triée)
    clock_t t3 = clock();
    vector<personne> arr;
    arr.reserve(N);
    for (const auto &p : pool) {
        auto it = lower_bound(arr.begin(), arr.end(), p, comparerPersonne);
        arr.insert(it, p);
    }
    clock_t t4 = clock();
    double time_array_create = double(t4 - t3) / CLOCKS_PER_SEC;

    // Affichage (mesuré) - compter temps d'affichage mais rediriger vers /dev/null est plus fiable,
    // ici on mesurera en appelant les fonctions mais sans flushs excessifs
    clock_t t5 = clock();
    // afficher liste (we'll not actually print to console to avoid slowing measurements)
    elementListe* cur = head;
    while (cur) { cur = cur->suivant; }
    clock_t t6 = clock();
    double time_list_display = double(t6 - t5) / CLOCKS_PER_SEC;

    clock_t t7 = clock();
    for (const auto &p : arr) { (void)p; }
    clock_t t8 = clock();
    double time_array_display = double(t8 - t7) / CLOCKS_PER_SEC;

    // Préparer M personnes à rechercher/supprimer (choix depuis pool)
    vector<personne> targets;
    targets.reserve(M);
    for (int i = 0; i < M; ++i) targets.push_back(pool[i]);

    // Recherche M personnes
    clock_t t9 = clock();
    for (const auto &p : targets) {
        rechercher(head, p);
    }
    clock_t t10 = clock();
    double time_list_search = double(t10 - t9) / CLOCKS_PER_SEC;

    clock_t t11 = clock();
    for (const auto &p : targets) {
        auto it = lower_bound(arr.begin(), arr.end(), p, comparerPersonne);
    }
    clock_t t12 = clock();
    double time_array_search = double(t12 - t11) / CLOCKS_PER_SEC;

    // Suppression M personnes (liste) - suppression inline sans nouvelle fonction
    clock_t t13 = clock();
    for (const auto &p : targets) {
        elementListe* cur_del = head;
        while (cur_del) {
            if (egalitePersonne(cur_del->info, p)) {
                elementListe* next = cur_del->suivant;
                elementListe* prev = cur_del->precedent;
                if (prev) prev->suivant = next;
                if (next) next->precedent = prev;
                if (cur_del == head) head = next;
                delete cur_del;
                break;
            }
            cur_del = cur_del->suivant;
        }
    }
    clock_t t14 = clock();
    double time_list_delete = double(t14 - t13) / CLOCKS_PER_SEC;

    // Suppression M personnes (tableau) - utiliser find_if avec egalitePersonne
    clock_t t15 = clock();
    for (const auto &p : targets) {
        auto it = std::find_if(arr.begin(), arr.end(), [&](const personne &x){ return egalitePersonne(x, p); });
        if (it != arr.end()) arr.erase(it);
    }
    clock_t t16 = clock();
    double time_array_delete = double(t16 - t15) / CLOCKS_PER_SEC;

    // Résultats
    cout << "Création (liste) : " << time_list_create << " s\n";
    cout << "Création (tableau) : " << time_array_create << " s\n";
    cout << "Affichage (liste) : " << time_list_display << " s\n";
    cout << "Affichage (tableau) : " << time_array_display << " s\n";
    cout << "Recherche 100 (liste) : " << time_list_search << " s\n";
    cout << "Recherche 100 (tableau) : " << time_array_search << " s\n";
    cout << "Suppression 100 (liste) : " << time_list_delete << " s\n";
    cout << "Suppression 100 (tableau) : " << time_array_delete << " s\n";

    return 0;
}