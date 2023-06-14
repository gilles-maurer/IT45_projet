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

        this->nb_employes = nb_employes;
        this->nb_missions = nb_missions;

        this->list_centres = list_centres;
        this->list_employes = list_employes;
        this->list_missions = list_missions;

        this->ordre = new int[tp];
    }

// destructeur de l'objet
Population::~Population(){

    delete[] this->individus;
    delete[] this->ordre;

}        

// METHODES

// affiche quelques statistiques sur la population
void Population::statistiques(){

    cout << "Statistiques de la population" << endl;

    // on calcule l'écart type de la fitness
    float moyenne = 0;
    float ecart_type = 0;

    for (int i = 0; i < this->taille_pop; i++){
        moyenne += this->individus[i].getFitness();
    }

    moyenne = moyenne / this->taille_pop;

    for (int i = 0; i < this->taille_pop; i++){
        ecart_type += pow(this->individus[i].getFitness() - moyenne, 2);
    }

    ecart_type = sqrt(ecart_type / this->taille_pop);

    cout << "Moyenne : " << moyenne << endl;
    cout << "Ecart type : " << ecart_type << endl;
    cout << endl;

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

    return &this->individus[index];
}



// OPERATEURS DE SELECTION ET DE REMPLACEMENT

// selection par roulette biaisee d'un individu de la population
Chromosome *Population::selection_roulette(){

    // calcul de la somme des fitness
    int sumFitness = 0;
    
    // Normalisation des fitness, recherche du min 
    int minFitness = 100000;
    for(int i = 0; i < this->taille_pop; i++){
        if(this->individus[i].getFitness() < minFitness){
            minFitness = this->individus[i].getFitness();
        }
    }

    for(int i = 0; i < this->taille_pop; i++){
        sumFitness += this->individus[i].getFitness() - minFitness;

    }

    // calcul des probabilités
    // On créer un tableau qui garde en mémoire la plage de valeur pour laquel un individu sera selectioné, 
    //plus son fitness est grand, plus il a de chance d'être sélectioné
    int* proba = new int[this->taille_pop];
    proba[0] = this->individus[0].getFitness() - minFitness;

    for(int i = 1; i < this->taille_pop; i++){
        proba[i] = proba[i-1] + this->individus[i].getFitness() - minFitness; // Plage de selection d'un individu = i-1 - i
    }

    // selection biaisée
    int random = rand();
    random = random * (sumFitness / RAND_MAX); // on obtient un nombre aléatoire entre 0 et la somme des fitness

    int numIndividu = 0; 

    // tant que le nombre aléatoire est plus petit que la plage superieur de la probabilité de l'individu
    while(random > proba[numIndividu] && numIndividu < this->taille_pop){
        numIndividu++; // On incrémente
    }

    // On retourn l'individu.
    // Attention dès que random est supérieur à la borne superieur de proba on sort, mais l'individu seletionné est l'individu précédent
    if (numIndividu == this->taille_pop) {
        numIndividu--;
    }

    return &this->individus[numIndividu];

}


// rempacement par roulette biaisee d'un individu de la population par un Chromosome donne
void Population::remplacement_roulette(Chromosome *list_enfants){
       
    // Pour chaque enfant
    for(int k = 0; k < this->taille_pop; k++){
        // calcul de la somme des fitness
        double sumFitness = 0;

        // Normalisation des fitness, recherche du min
        double minFitness = 1000000;
        for(int i = 0; i < this->taille_pop; i++){
            if(((double)1/this->individus[i].getFitness())< minFitness){
                minFitness = ((double)1/this->individus[i].getFitness());
            }
        }
        for(int i = 0; i < this->taille_pop; i++){
            sumFitness += (((double)1/this->individus[i].getFitness()) - minFitness)*1000000;
        }

        // calcul des probabilités
        // On créer un tableau qui garde en mémoire la plage de valeur pour laquel un individu sera selectioné, 
        //plus son fitness est grand, moins il a de chance d'être sélectioné
        int* proba = new int[this->taille_pop];
        proba[0] = (((double)1/this->individus[0].getFitness()) - minFitness)*1000000;

        for(int i = 1; i < this->taille_pop; i++){
            proba[i] = proba[i-1] + (((double)1/this->individus[i].getFitness()) - minFitness)*1000000; // Plage de selection d'un individu = i-1 - i
        }
        // selection biaisée
        int random = rand();
        random = random * (sumFitness / RAND_MAX); // on obtient un nombre aléatoire entre 0 et la somme des fitness

        int numIndividu = 0; 

        // tant que le nombre aléatoire est plus petit que la plage superieur de la probabilité de l'individu
        while(random > proba[numIndividu] && numIndividu < this->taille_pop){
            numIndividu++; // On incrémente
        }

        // On retourn l'individu.
        this->individus[numIndividu] = list_enfants[k];
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

void Population::print(){
    for(int i = 0; i < this->taille_pop; i++){
        cout << "Individu " << i << endl;
        this->individus[i].print();
    }
}

void Population::croisement(Chromosome* parent1, Chromosome* parent2,
                      Chromosome* enfant1, Chromosome* enfant2) {
    bool valide = true;
    // Tirage aléatoire 5 fois max
    for(int k = 0; k < 5; k++){
        valide = true;
        // tirage aléatoire d'un point de croisement
        int point = rand() % this->nb_missions;

        // copie des gènes des parents dans les enfants
        enfant1->fusion(parent1->getGene(0, point), parent2->getGene(point, this->nb_missions), point); // enfant1 = parent1[0:point] + parent2[point+1:nb_missions]
        enfant2->fusion(parent2->getGene(0, point), parent1->getGene(point, this->nb_missions), point); // enfant2 = parent2[0:point] + parent1[point+1:nb_missions]

        // check si les enfants sont valides

        for (int i = 0; i < this->nb_employes; i++) {
            bool* planning1 = new bool[this->nb_missions];
            bool* planning2 = new bool[this->nb_missions];
            for (int j = 0; j < this->nb_missions; j++) {
                planning1[j] = enfant1->getGene()[j][i]; // on récupère le planning de l'employé i
                planning2[j] = enfant2->getGene()[j][i];
            }

            if (!enfant1->isPlaningValid(planning1)) {
                valide = false;
                break;
            }        
            if (!enfant2->isPlaningValid(planning2)) {
                valide = false;
                break;
            }
        }
        // Si les enfants sont valides, on sort de la boucle
        if (valide) {

            break;
        }
    }

    // Si les enfants ne sont pas valides, on les remplace par les parents
    if (!valide) {
        *enfant1 = *parent1;
        *enfant2 = *parent2;
    }
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

