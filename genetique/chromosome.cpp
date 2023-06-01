#include "chromosome.h"
#include <cmath>

using namespace std;


Chromosome::Chromosome(){
    
    this->nb_missions = -1;
    this->nb_employes = -1; 
    this->fitness = -1;
    this->genes = NULL;

}

Chromosome::Chromosome(int nb_missions, int employes){

    this->nb_missions = nb_missions;
    this->nb_employes = nb_employes;

    this->fitness = 0;

    this->genes = new bool*[nb_missions];
    for(int i = 0; i < nb_missions; i++){
        this->genes[i] = new bool[nb_employes];
    }

}


Chromosome::~Chromosome(){// destructeur de l'objet

}

// Geters 
bool** Chromosome::getGene(){
    return this->genes;
}

int Chromosome::getFitness(){
    return this->fitness;
}


// METHODES
void Chromosome::print(){// fonction d'affichage du Chromosome (i.e. de la solution)
    cout << "Chromosome: " << this->genes[0] << endl;
}   

// fonction d'évaluation du Chromosome (c-é-d calcul la fitness)
//   Elle doit etre lancée é la creation des solution et apres
//   l'exécution des operateurs de mutation et de croisement
//La fitness d’une solution sera déterminé par le nombre de missions affectées, la distance 
//totale parcourue par les employés dans la solution et le nombre de missions où la spécialité est respectée.  

//Pour ces 3 critères on pourra attribuer un coefficient qui permettra de faire varier l’importance 
//de chacun dans la valeur de la fitness, on s’assurera cependant de conserver l’ordre d’importance du sujet.  
void Chromosome::evaluer(){
    int fitness = 0; // valeur de la fonction objectif (fitness) de la solution
    int nbMissionAffecte = 0; // nombre de mission affecté
    int distanceParcourue = 0; // distance parcourue par les employés dans la solution
    int nbMissionSpe = 0; // nombre de mission ou la spécialité est respectée

    for(int i = 0; i < this->nb_missions; i++){ 
        for(int j = 0; j < this->nb_employes; j++){
            if(this->genes[i][j] == 1){
                nbMissionAffecte++;
            }
        }
    }
    fitness = nbMissionAffecte + distanceParcourue + nbMissionSpe;
    this->fitness = fitness;

    // Calcul de la distance parcourue par les employés dans la solution 

}
	                    
void Chromosome::ordonner(){  // ordonne le sens de la tournée si gene[1] > gene[taille-1]
    if(this->genes[0][0] > this->genes[this->nb_missions-1][this->nb_employes-1]){
        for(int i = 0; i < this->nb_missions; i++){
            for(int j = 0; j < this->nb_employes; j++){
                if(this->genes[i][j] == 1){
                    this->genes[i][j] = 0;
                    this->genes[j][i] = 1;
                }
            }
        }
    }
} 

void Chromosome::copier(Chromosome* source){ // copie le Chromosome 'source'
    this->genes = source->getGene();
}

bool Chromosome::identique(Chromosome* chro){ // test si 2 chromosome sont identique
    if(this->genes != chro->getGene()){
        return false;
    }
    return true;
}

// OPERATEURS DE MUTATION
void Chromosome::muter(int taux){ // Echange deux missions (i.e. deux colomnes de la matrice)
    int nbMutation = (this->nb_missions * taux) / 100;
    int nbMutationEffectue = 0;
    int i = 0;
    int j = 0;
    while(nbMutationEffectue < nbMutation){
        i = rand() % this->nb_missions;
        j = rand() % this->nb_employes;
        if(this->genes[i][j] == 1){
            this->genes[i][j] = 0;
            this->genes[j][i] = 1;
            nbMutationEffectue++;
        }
    }
} 


Chromosome* Chromosome::fusion(Chromosome* chro1, Chromosome* chro2){ // fusionne 2 chromosomes

    Chromosome* chroFusion = new Chromosome(this->nb_missions, this->nb_employes);

    return chroFusion;
}

