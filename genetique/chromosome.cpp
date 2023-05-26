#include "chromosome.h"


Chromosome::Chromosome(int tc){

}

Chromosome::~Chromosome(){// destructeur de l'objet

}

// METHODES
void Chromosome::afficher(){// fonction d'affichage du Chromosome (i.e. de la solution)

}   

void Chromosome::evaluer(){

}
	                    // fonction d'évaluation du Chromosome (c-é-d calcul la fitness)
                        //   Elle doit etre lancée é la creation des solution et apres
					    //   l'exécution des operateurs de mutation et de croisement

void Chromosome::ordonner(){  // ordonne le sens de la tournée si gene[1] > gene[taille-1]

} 
void Chromosome::copier(Chromosome* source){ // copie le Chromosome 'source'

}

bool Chromosome::identique(Chromosome* chro){ // test si 2 chromosome sont identique


}

// OPERATEURS DE MUTATION
void Chromosome::mutation(){
    srand(time(0));
    int mutedGene = rand() % this->taille;
    
} 

