#include "ag.h"

using namespace std;


// CONSTRUCTEUR 
Ag::Ag(int nbgenerations, int taille_pop, double taux_croisement, double taux_mutation, int taille_chromosome, 	double coefNbMisAffecte, double coefDistParcourue, double coefNbMisSpe){
    this->nbgenerations = nbgenerations;
    this->taille_pop = taille_pop;
    this->taux_croisement = taux_croisement;
    this->taux_mutation = taux_mutation;
    this->taille_chromosome = taille_chromosome;
    this->coefNbMisAffecte = coefNbMisAffecte;
    this->coefDistParcourue = coefDistParcourue;
    this->coefNbMisSpe = coefNbMisSpe;
    this->pop = new Population(taille_pop, taille_chromosome);
}

// DESTRUCTEUR
Ag::~Ag() {

}


// METHODES

// fonction principale qui décit le déroulement de l'algorithme évolusionniste
Chromosome* Ag::optimiser() {
    // initialisation de la population
    this->pop->initialiser();
    // évaluation de la population
    this->pop->evaluer();
    // affichage des statistiques de la population
    this->pop->statistiques();
    // boucle principale de l'algorithme
    for (int i = 0; i < this->nbgenerations; i++) {
        // sélection de deux parents
        Chromosome* parent1 = this->pop->selection_roulette();
        Chromosome* parent2 = this->pop->selection_roulette();
        // croisement des deux parents
        Chromosome* enfant1 = new Chromosome(this->taille_chromosome);
        Chromosome* enfant2 = new Chromosome(this->taille_chromosome);
        this->croisement(parent1, parent2, enfant1, enfant2);
        // mutation des deux enfants
        enfant1->muter(this->taux_mutation);
        enfant2->muter(this->taux_mutation);
        // évaluation des deux enfants
        enfant1->evaluer();
        enfant2->evaluer();
        // remplacement des deux parents par les deux enfants
        this->pop->remplacement_roulette(enfant1);
        this->pop->remplacement_roulette(enfant2);
        // affichage des statistiques de la population
        this->pop->statistiques();
    }
    // affichage des statistiques de la population
    this->pop->statistiques();

    // retourne le meilleur individu de la population
}  


// OPERATEURS DE CROISEMENT
// opérateur de croisement de deux Chromosomes

void Ag::croisement(Chromosome* parent1, Chromosome* parent2,
                      Chromosome* enfant1, Chromosome* enfant2) {
    // tirage aléatoire d'un point de croisement
    int point = rand() % this->taille_chromosome;
    // copie des gènes des parents dans les enfants
    for (int i = 0; i < point; i++) {



}