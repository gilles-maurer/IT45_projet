#include "population.h"


// CONSTRUCTEURS
Population::Population(int tp, int tc){
        this->taille_pop = tp;
        this->individus = new Chromosome[tp];
        this->ordre = new int[tp];
    }

// destructeur de l'objet
Population::~Population(){}        

// METHODES

// affiche quelques statistiques sur la population
void Population::statistiques(){
    individus[0].evaluer();
    int fitness = individus[0].getFitness();
    printf("Fitness: %i\n", fitness);
} 

// compte le nombre de Chromosomes similaires 'chro'
int Population::nb_Chromosomes_similaires(Chromosome* chro){
    int count;

    return count;

}

// affiche les resultats du comptage de Chromosomes similaires aux meilleurs individus de la population.                   
void Population::similitude(){

}

// OPERATEURS DE SELECTION ET DE REMPLACEMENT

// selection par roulette biaisee d'un individu de la population
Chromosome *Population::selection_roulette(){

}     

// rempacement par roulette biaisee d'un individu de la population par un Chromosome donne
void Population::remplacement_roulette(Chromosome *individu){

}
    
void Population::ordonner(){

}

void Population::reordonner(){

}

void Population::afficher(){
    for(int i = 0; i < this->taille_pop; i++){
        this->individus[i].afficher();
    }
}
