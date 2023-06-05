#include "population.h"
#include <iostream>
#include <random>
#include <vector>

using namespace std;


// CONSTRUCTEURS
Population::Population(int tp, int nb_missions, int nb_employes, int nb_centres, Mission *list_missions, Employe *list_employes, Centre *list_centres){
        this->taille_pop = tp;

        this->individus = new Chromosome[tp];
        
        for (int i = 0; i < tp; i++){
            this->individus[i] = Chromosome(nb_missions, nb_employes, nb_centres, list_missions, list_employes, list_centres);
        }

        cout << "Population créée" << endl;
        for (int i = 0; i < tp; i++){
            cout << this->individus[i].getNbEmployes() << endl;
        }
        cin.get();

        this->nb_employes = nb_employes;
        this->nb_missions = nb_missions;

        this->list_centres = list_centres;
        this->list_employes = list_employes;
        this->list_missions = list_missions;

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


// renvoie le meilleur individu de la population
Chromosome *Population::getMeilleurIndividu(){
    
    float maxFitness = 0;  
    int index = 0;

    for (int i = 0; i < this->taille_pop; i++){
        if (this->individus[i].getFitness() > maxFitness){
            maxFitness = this->individus[i].getFitness();
            index = i;
        }
    }

    this->individus[index].print();
    cin.get();

    return &this->individus[index];
}



// OPERATEURS DE SELECTION ET DE REMPLACEMENT

// selection par roulette biaisee d'un individu de la population
Chromosome *Population::selection_roulette(){
    // calcul de la somme des fitness
    int sumFitness = 0;
    
    for(int i = 0; i < this->taille_pop; i++){
        sumFitness += this->individus[i].getFitness();
    }

    // calcul des probabilités
    // On créer un tableau qui garde en mémoire la plage de valeur pour laquel un individu sera selectioné, 
    //plus son fitness est grand, plus il a de chance d'être sélectioné
    int* proba = new int[this->taille_pop];
    proba[0] = this->individus[0].getFitness();

    for(int i = 1; i < this->taille_pop; i++){
        proba[i] = proba[i-1] + this->individus[i].getFitness(); // Plage de selection d'un individu = i-1 - i 
    }

    // selection biaisée
    int random = rand() % sumFitness;

    int numIndividu = 0;
    // tant que le nombre aléatoire est plus petit que la plage superieur de la probabilité de l'individu
    while(random < proba[numIndividu] || numIndividu < this->taille_pop){
        numIndividu++; // On incrémente
    }

    // On retourn l'individu.
    // Attention dès que random est supéreieur à la borne superieur de proba on sort, mais l'individu seletionné est l'individu précédent
    numIndividu--;
    return &this->individus[numIndividu];

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
        cout << "Individu " << i << endl;
        this->individus[i].print();
    }
}

void Population::croisement(Chromosome* parent1, Chromosome* parent2,
                      Chromosome* enfant1, Chromosome* enfant2) {
    // tirage aléatoire d'un point de croisement
    int point = rand() % this->nb_missions;
    cout << "Point de croisement: " << point << endl;

    cout << "nb employes: " << this->nb_employes << endl;
    cout << "parent1: " << parent1->getNbEmployes() << endl;
    cout << "parent2: " << parent2->getNbEmployes() << endl;
    cin.get();

    // copie des gènes des parents dans les enfants
    enfant1->fusion(parent1->getGene(0, point), parent2->getGene(point+1, this->nb_missions), point); // enfant1 = parent1[0:point] + parent2[point+1:nb_missions]
    enfant2->fusion(parent2->getGene(0, point), parent1->getGene(point+1, this->nb_missions), point); // enfant2 = parent2[0:point] + parent1[point+1:nb_missions]
}

void Population::test_croisement(int a, int b){

    for(int i =0; i < taille_pop; i++){
        this->individus[i].print();
    }

    Chromosome* parent1 = &this->individus[a];
    Chromosome* parent2 = &this->individus[b];

    cout << "Parent 1" << endl;
    parent1->print();
    cout << "Parent 2" << endl;
    parent2->print();
    // croisement des deux parents
    Chromosome* enfant1 = new Chromosome(this->nb_missions, this->nb_employes, this->nb_centres, this->list_missions, this->list_employes, this->list_centres);
    Chromosome* enfant2 = new Chromosome(this->nb_missions, this->nb_employes, this->nb_centres, this->list_missions, this->list_employes, this->list_centres);
    this->croisement(parent1, parent2, enfant1, enfant2);

    cout << "Enfant 1" << endl;
    enfant1->print();
    cout << "Enfant 2" << endl;
    enfant2->print();

}

