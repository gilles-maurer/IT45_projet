#include "population.h"
#include <iostream>
#include <random>
#include <vector>

using namespace std;


// CONSTRUCTEURS
Population::Population(int tp, int nb_missions, int nb_employes){
        this->taille_pop = tp;

        this->individus = new Chromosome[tp];

        for (int i = 0; i < tp; i++){
            this->individus[i] = Chromosome(nb_missions, nb_employes);
        }

        this->ordre = new int[tp];
    }

// destructeur de l'objet
Population::~Population(){}        

// METHODES

// affiche quelques statistiques sur la population
void Population::statistiques(double coefNbMisAffecte, double coefDistParcourue, double coefNbMisSpe){
    individus[0].evaluer(coefNbMisAffecte, coefDistParcourue, coefNbMisSpe);
    int fitness = individus[0].getFitness();
    cout << "Fitness: " << fitness << endl;

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
    double sumFitness = 0;
    // calcul de la somme des fitness
    for(int i = 0; i < this->taille_pop; i++){
        sumFitness += this->individus[i].getFitness();
    }
    
    // calcul des probabilités
    vector<double> proba;
    
    for(int i = 0; i < this->taille_pop; i++){
        proba.push_back(this->individus[i].getFitness()/sumFitness);
    }

    // Choix aléatoire d'un individu en fonction des probabilités
    random_device rd;
    mt19937 gen(rd());
    discrete_distribution<> dist(proba.begin(), proba.end());

    return &individus[gen() + 1];

}     

// rempacement par roulette biaisee d'un individu de la population par un Chromosome donne
void Population::remplacement_roulette(Chromosome *individu){

}
    
void Population::ordonner(){
    int fitness;
    int fitness2;
    int index;
    int index2;
    for(int i = 0; i < this->taille_pop; i++){
        fitness = this->individus[i].getFitness();
        index = i;
        for(int j = i+1; j < this->taille_pop; j++){
            fitness2 = this->individus[j].getFitness();
            index2 = j;
            if(fitness2 < fitness){
                fitness = fitness2;
                index = index2;
            }
        }
        this->ordre[i] = index;
    }
}

// Permet d'ajouter un individu à la population
void Population::ajouter(bool** genes, int numIndividu){
    this->individus[numIndividu].copier(genes);
}

void Population::evaluer(double coefNbMisAffecte, double coefDistParcourue, double coefNbMisSpe){
    for(int i = 0; i < this->taille_pop; i++){
        this->individus[i].evaluer(coefNbMisAffecte, coefDistParcourue, coefNbMisSpe);
    }
}


void Population::reordonner(){

}

void Population::print(){
    for(int i = 0; i < this->taille_pop; i++){
        this->individus[i].print();
    }
}
