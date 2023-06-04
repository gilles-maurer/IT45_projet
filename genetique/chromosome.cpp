#include "chromosome.h"
#include <cmath>

using namespace std;


Chromosome::Chromosome(){
    
    this->nb_missions = -1;
    this->nb_employes = -1; 
    this->fitness = -1;

    this->list_missions = NULL;

    this->genes = NULL;

}

Chromosome::Chromosome(int nb_missions, int nb_employes, int nb_centres, Mission *list_missions, Employe *list_employes, Centre *list_centres){

    this->nb_missions = nb_missions;
    this->nb_employes = nb_employes;
    this->nb_centres = nb_centres;

    this->list_missions = list_missions;
    this->list_employes = list_employes;
    this->list_centres = list_centres;

    this->fitness = 0;

    this->genes = new bool*[nb_missions];
}


Chromosome::~Chromosome(){// destructeur de l'objet

}

// Geters 
bool** Chromosome::getGene(){
    return this->genes;
}

// retourne le tableau de genes entre deux point
bool** Chromosome::getGene(int firstPoint, int secondPoint){
        cout << "getGene" << endl;
    bool** returnGenes = new bool*[secondPoint - firstPoint];
    for (int i = 0; i < secondPoint - firstPoint; i++){
        returnGenes[i] = new bool[this->nb_employes];
    }

    for(int i = 0; i < secondPoint - firstPoint; i++){
        for(int j = 0; j < this->nb_employes; j++){
            returnGenes[i][j] = false; // Initialisation à false (0)
        }
    }

    cout << "getGene" << endl;

    for(int i = 0; i < secondPoint - firstPoint; i++){
        for(int j = 0; j < this->nb_employes; j++){
            returnGenes[i][j] = this->genes[firstPoint + i][j];
        }
    }
    
    return genes;
}

int Chromosome::getFitness(){
    return this->fitness;
}

// METHODES
void Chromosome::print(){// fonction d'affichage du Chromosome (i.e. de la solution)
    cout << "Chromosome fitness : " << this->genes[0][0] << endl;
}   

// fonction d'évaluation du Chromosome (c-é-d calcul la fitness)
//   Elle doit etre lancée é la creation des solution et apres
//   l'exécution des operateurs de mutation et de croisement
//La fitness d’une solution sera déterminé par le nombre de missions affectées, la distance 
//totale parcourue par les employés dans la solution et le nombre de missions où la spécialité est respectée.  

//Pour ces 3 critères on pourra attribuer un coefficient qui permettra de faire varier l’importance 
//de chacun dans la valeur de la fitness, on s’assurera cependant de conserver l’ordre d’importance du sujet.  
void Chromosome::evaluer(double coefNbMisAffecte, double coefDistParcourue, double coefNbMisSpe){

    int nbMissionAffecte = 0; // nombre de mission affecté
    int distanceParcourue = 0; // distance parcourue par les employés dans la solution
    int nbMissionSpe = 0; // nombre de mission ou la spécialité est respectée

    // Calcul du nombre de mission affecté
    for(int i = 0; i < this->nb_missions; i++){ 
        for(int j = 0; j < this->nb_employes; j++){
            if(this->genes[i][j] == 1){
                nbMissionAffecte++;
            }
        }
    }

    // Calcul de la distance parcourue par les employés dans la solution 
    for (int i = 0; i < this->nb_employes; i++){ // chaque employé

        for (int j = 1; j <= 5; j++){ // chaque jour 

            Mission* missions = new Mission[this->nb_missions];
            int count = 0;

            for (int k = 0; k < this->nb_missions; k++){ // chaque mission
                if(this->genes[k][i] == 1){ // si la mission est affecté à l'employé
                    if (list_missions[k].getDay() == j){ // si la mission est le jour j
                        missions[count] = list_missions[k];
                        count++;
                    }
                }    
            }

            // on tri les missions par heure de début
            missions = sortMission(missions, count);

            // on calcule la distance parcourue par l'employé pour le jour j
            distanceParcourue += ridelenght(missions, count, i);

        }
    }

    // Calcul du nombre de mission ou la spécialité est respectée

    /**for(int i = 0; i < this->nb_missions; i++){ // chaque mission
        for(int j = 0; j < this->nb_employes; j++){ // chaque employé
            if(this->genes[i][j] == 1){ // si la mission est affecté à l'employé
                if(list_missions[i].getSpeciality() == list_employes[j].getSpeciality()){ // si la spécialité de l'employé correspond à la spécialité de la mission
                    nbMissionSpe++;
                }
            }
        }
    }**/


    this->fitness = coefNbMisAffecte * nbMissionAffecte + 
                        coefDistParcourue * distanceParcourue + coefNbMisSpe * nbMissionSpe;

}

Mission* Chromosome::sortMission(Mission* missions, int count){
   
    // on tri les missions par heure de début
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count - 1; j++) {
            if (missions[j].getStart() > missions[j + 1].getStart()) {
                Mission temp = missions[j];
                missions[j] = missions[j + 1];
                missions[j + 1] = temp;
            }
        }
    }

    return missions;
}

float Chromosome::ridelenght(Mission* missions, int count, int id_employe){
    
    float distance_totale = 0;

    for (int i = 0; i < count - 1; i++) {
        // on calcule le temps pour aller d'une mission à une autre 
        float distance = missions[i].getDistance(missions[i + 1], this->nb_centres);

        // on ajoute le temps de trajet à la distance totale
        distance_totale += distance;
    }

    int id_centre = list_employes[id_employe].getCentreId();
    Centre centre = list_centres[id_centre - 1];

    distance_totale += centre.getDistance(missions[0], this->nb_centres);
    distance_totale += centre.getDistance(missions[count - 1], this->nb_centres);

    return distance_totale; 
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

void Chromosome::copier(bool** genes){ // copie le gene 'source'
    this->genes = genes;
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
    

    return new Chromosome();

}

void Chromosome::fusion(bool** gene1, bool** gene2, int point){ // fusionne 2 genomes
    // taille total = n, taille gene1 = n1, taille gene2 = n2, n1 + n2 = n
    // Il faut fusioner *gene1[0] à *gene2[0] ... *gene1[n1] à *gene2[n2]

    // pour chaque employé
    for (int i = 0; i < this->nb_employes; i++){
        // Allouer un nouvel espace mémoire pour le tableau fusionné
        bool* fusion = (bool*)malloc((this->nb_missions) * sizeof(bool));

        // Copier les valeurs du tableau gene1
        memcpy(fusion, gene1, point * sizeof(bool));

        // Copier les valeurs du tableau gene2 à la suite de gene1
        memcpy(fusion + point, gene2, (this->nb_missions - point) * sizeof(bool));
        
        // On a fusionné *gene1[i] et *gene2[i]
        this->genes[i] = fusion;
    }
}

