#include "population.h"


// CONSTRUCTEURS
population::population(int tp, int tc){
    this->taille_pop = tp;
    this->tc = tc;

}

// destructeur de l'objet
population::~population(){ 

}            

// METHODES

// affiche quelques statistiques sur la population
void population::statistiques(){

} 

// compte le nombre de Chromosomes similaires 'chro'
int population::nb_Chromosomes_similaires(Chromosome* chro){
    int count;

    return count;

}

// affiche les resultats du comptage de Chromosomes similaires aux meilleurs individus de la population.                   
void population::similitude(){

}

// OPERATEURS DE SELECTION ET DE REMPLACEMENT

// selection par roulette biaisee d'un individu de la population
Chromosome *population::selection_roulette(){

}     

// rempacement par roulette biaisee d'un individu de la population par un Chromosome donne
void population::remplacement_roulette(Chromosome *individu){

}
    
void population::ordonner(){

}

void population::reordonner(){

}

void population::afficher(){
    for(int i = 0; i < taille_pop; i++){
        individus
    }
}
