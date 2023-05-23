#include "ag.h"

using namespace std;


// CONSTRUCTEUR 
Ag::Ag() {


}

// DESTRUCTEUR
Ag::~Ag() {

}


// METHODES

// fonction principale qui décit le déroulement de l'algorithme évolusionniste
Chromosome* Ag::optimiser() {

    int amelioration = 0;
    Chromosome *fils1 = new Chromosome(taille_chromosome);
    Chromosome *fils2 = new Chromosome(taille_chromosome);
    Chromosome *parent1; 
    Chromosome *parent2;
    int best_fitness = 0;

    // evaluer la population initiale
    for (int i = 0; i < taille_pop; i++) {
        pop->individus[i]->evaluer();
    }



    // on ordonne la population initiale
    pop->ordonner();

    best_fitness = pop->individus[pop->ordre[0]]->fitness; 
    // statistiques de la population initiale
    cout << "Generation 0 : " << endl;
    pop->statistiques();

    // boucle principale de l'algorithme
    // tant que le nombre de génération n'est pas atteint

    for (int g = 0; g<nbgenerations; g++) {

        parent1 = pop->selection_roulette();
        parent2 = pop->selection_roulette();


        // croisement avec probabilité taux_croisement
        if (/*random sur la probabilité de croisement*/1) {
            croisement(parent1, parent2, fils1, fils2);
        } else {
            fils1->copier(parent1);
            fils2->copier(parent2);
        }

        // mutation avec probabilité taux_mutation
        if (/*random sur la probabilité de mutation*/1) {
            fils1->mutation();
        }
        if (/*random sur la probabilité de mutation*/1) {
            fils2->mutation();
        }

        // évaluation des fils
        fils1->evaluer();
        fils2->evaluer();

        // insertion des fils dans la population
        pop->remplacement_roulette(fils1);
        pop->remplacement_roulette(fils2);

        // on ordonne la population
        pop->reordonner();

        // si la fitness du meilleur individu a pas changé
        if (pop->individus[pop->ordre[0]]->fitness < best_fitness) {
            best_fitness = pop->individus[pop->ordre[0]]->fitness;
            cout << "Generation " << g << " : " << best_fitness << endl;
            amelioration = g; 
        }       
    }

    // statistiques de la population finale
    cout << "Statistiques de la population finale : " << endl;
    pop->statistiques();
    // calcul de la consanguinité
    pop->similitude();

    // retourne le meilleur individu
    return pop->individus[pop->ordre[0]];
}  


// OPERATEURS DE CROISEMENT
// opérateur de croisement de deux Chromosomes

void Ag::croisement(Chromosome* parent1, Chromosome* parent2,
                      Chromosome* enfant1, Chromosome* enfant2) {

}