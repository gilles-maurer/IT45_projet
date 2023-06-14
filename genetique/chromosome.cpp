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

Chromosome::Chromosome(Chromosome* source){ // constructeur de copie

    this->nb_missions = source->nb_missions;
    this->nb_employes = source->nb_employes;
    this->nb_centres = source->nb_centres;

    this->list_missions = source->list_missions;
    this->list_employes = source->list_employes;
    this->list_centres = source->list_centres;

    this->fitness = source->fitness;
    this->nb_missions_affecte = source->nb_missions_affecte;
    this->distance_parcourue = source->distance_parcourue;
    this->nb_specialite = source->nb_specialite;

    this->genes = source->genes;


}

Chromosome::Chromosome(int nb_missions, int nb_employes, int nb_centres, Mission *list_missions, Employe *list_employes, Centre *list_centres){

    this->nb_missions = nb_missions;
    this->nb_employes = nb_employes;
    this->nb_centres = nb_centres;

    this->list_missions = list_missions;
    this->list_employes = list_employes;
    this->list_centres = list_centres;

    this->fitness = 0;
    this->nb_missions_affecte = 0;
    this->distance_parcourue = 0;
    this->nb_specialite = 0;

    this->genes = new bool*[nb_missions];
    for (int i = 0; i < nb_missions; i++){
        this->genes[i] = new bool[nb_employes];
    }

}


Chromosome::~Chromosome(){

    for (int i = 0; i < this->nb_missions; i++){
        delete[] this->genes[i];
    }
    delete[] this->genes;

}

// GETTERS 
bool** Chromosome::getGene(){
    return this->genes;
}

// retourne le tableau de genes entre deux point
bool** Chromosome::getGene(int firstPoint, int secondPoint){

    bool** returnGenes = new bool*[secondPoint - firstPoint];
    for (int i = 0; i < secondPoint - firstPoint; i++){
        returnGenes[i] = new bool[this->nb_employes];
    }

    for(int i = 0; i < secondPoint - firstPoint; i++){
        for(int j = 0; j < this->nb_employes; j++){
            returnGenes[i][j] = false; // Initialisation à false (0)
        }
    }

    for(int i = 0; i < secondPoint - firstPoint; i++){
        for(int j = 0; j < this->nb_employes; j++){
            returnGenes[i][j] = this->genes[firstPoint + i][j];
        }
    }
    
    return returnGenes;
}

int Chromosome::getFitness(){
    return this->fitness;
}

int Chromosome::getNbMissions(){
    return this->nb_missions;
}

int Chromosome::getNbEmployes(){
    return this->nb_employes;
}

int Chromosome::getNbCentres(){
    return this->nb_centres;

}

Mission* Chromosome::getListMissions(){
    return this->list_missions;
}

Employe* Chromosome::getListEmployes(){
    return this->list_employes;
}

Centre* Chromosome::getListCentres(){
    return this->list_centres;
}

int Chromosome::getNbMissionsAffecte(){
    return this->nb_missions_affecte;
}

float Chromosome::getDistance(){
    return this->distance_parcourue;
}

int Chromosome::getNbSpecialite(){
    return this->nb_specialite;
}


// METHODES
void Chromosome::print(){// fonction d'affichage du Chromosome (i.e. de la solution)
    for(int i = 0; i < this->nb_missions; i++){
        cout << list_missions[i].getId() << " ";
        for(int j = 0; j < this->nb_employes; j++){
            cout << this->genes[i][j] << " ";
        }
        cout << endl;
    }
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
    float distanceParcourue = 0; // distance parcourue par les employés dans la solution
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

            missions = sortMission(missions, count);

            // on calcule la distance parcourue par l'employé pour le jour j
            distanceParcourue += ridelenght(missions, count, i);
        }
    }

    // Calcul du nombre de mission ou la spécialité est respectée

    for(int i = 0; i < this->nb_missions; i++){ // chaque mission
        for(int j = 0; j < this->nb_employes; j++){ // chaque employé
            if(this->genes[i][j] == 1){ // si la mission est affecté à l'employé
                if(list_missions[i].getSpeciality() == list_employes[j].getSpeciality()){ // si la spécialité de l'employé correspond à la spécialité de la mission
                    nbMissionSpe++;
                }
            }
        }
    }

    this->nb_missions_affecte = nbMissionAffecte;
    this->distance_parcourue = distanceParcourue;
    this->nb_specialite = nbMissionSpe;

    this->fitness = (coefNbMisAffecte * nbMissionAffecte) - 
                        (coefDistParcourue * distanceParcourue) + (coefNbMisSpe * nbMissionSpe);

}   


void Chromosome::stats(){ // affiche quelques statistiques sur le Chromosome
    cout << "Fitness: " << this->fitness << endl;
    cout << "Nombre de missions affectees: " << this->nb_missions_affecte << endl;
    cout << "Distance parcourue: " << this->distance_parcourue << endl;
    cout << "Nombre de missions ou la specialite est respectee: " << this->nb_specialite << endl;
    cout << endl;
}


float Chromosome::ridelenght(Mission* missions, int count, int id_employe){

    float distance_totale = 0;

    if (count == 0) { // si l'employé n'a pas de mission on renvoie 0
        return 0;
    }    

    if (count > 1) { // s'il y a au moins 2 missions on peut calculer la distance entre les missions
        for (int i = 0; i < count - 1; i++) {
            // on calcule le temps pour aller d'une mission à une autre 
            float distance = missions[i].getDistance(missions[i + 1], this->nb_centres);

            // on ajoute le temps de trajet à la distance totale
            distance_totale += distance;
        }
    }

    int id_centre = list_employes[id_employe].getCentreId();
    Centre centre = list_centres[id_centre - 1];

    distance_totale += centre.getDistance(missions[0], this->nb_centres);
    distance_totale += centre.getDistance(missions[count - 1], this->nb_centres);
    return distance_totale; 
}

// OPERATEURS DE COPIE

void Chromosome::copier(bool** genes){ // copie le gene 'source'
    this->genes = genes;
}


// Verifier que le planing est valide
bool Chromosome::isPlaningValid(bool* planning) { // planning correspond donc à toutes les missions affectées à un employé 

    // pour être valide il faut qu'aucune mission ne se chevauche
    // il faut que l'employé ne travaille pas plus de 7h par jour
    // il faut que l'employé ne travaille pas plus de 35h par semaine
    // il faut que l'amplitude horaire de travail soit inférieure à 13h par jour

    int heures_semaine = 0;

    for (int i = 1; i <= 5; i++) { // on regarde pour tout les jours 

        int heures_jour = 0;
        Mission *mission_jour = new Mission[nb_missions]; // on crée un tableau de missions pour stocker les missions du jour i
        int count = 0;

        for (int m = 0; m < nb_missions; m++) { // on parcours toutes les missisions 

            if (planning[m] == 1) { // si la mission est affectée à l'employé
                if (list_missions[m].getDay() == i) { // si la mission est le jour i

                    heures_semaine += list_missions[m].getDuration(); // on ajoute la durée de la mission au nombre d'heures travaillées dans la semaine
                    heures_jour += list_missions[m].getDuration(); // on ajoute la durée de la mission au nombre d'heures travaillées dans la journée
                    mission_jour[count] = list_missions[m]; // on ajoute la mission au tableau de missions du jour i
                    count++;

                }
            }

            mission_jour = sortMission(mission_jour, count); // on trie les missions du jour par heure de début

            if(areMissionsOverlapping(mission_jour, count)){ // si les missions du jour se chevauchent
                return false;
            }

            if(isDayTooLong(mission_jour, count)){ // si l'amplitude horaire de travail est supérieure à 13h
                return false;
            }

            float temps_trajet = rideTime(mission_jour, count); // on calcule le temps de trajet entre les missions du jour
            
            if (heures_jour + temps_trajet > 7) { // si l'employé travaille plus de 7h dans la journée
                return false;
            }
        }
    }

    if (heures_semaine > 35) { // si l'employé travaille plus de 35h dans la semaine
        return false;
    }

    return true;
}

float Chromosome::rideTime(Mission* missions, int count) {

    float temps_total = 0;

    for (int i = 0; i < count - 1; i++) {
        // on calcule le temps pour aller d'une mission à une autre 
        float distance = missions[i].getDistance(missions[i + 1], this->nb_centres);    // on suppose que les employés se déplacent à 50km/h

        // on calcule le temps de trajet entre les deux missions
        float temps_trajet = distance / 50; // on suppose que les employés se déplacent à 50km/h

        temps_total += temps_trajet;
    }


    return temps_total;
}

Mission* Chromosome::sortMission(Mission* missions, int count) {

    // on tri les missions par heure de début

    if (count == 0 || count == 1) {
        return missions;
    }

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

bool Chromosome::areMissionsOverlapping(Mission* missions, int count) {

    if (count == 0 || count == 1) {
        return false;
    }

    for (int i = 0; i < count - 1; i++) {

        // on calcule le temps pour aller d'une mission à une autre 
        float distance = missions[i].getDistance(missions[i + 1], this->nb_centres);

        // on calcule le temps de trajet entre les deux missions
        float temps_trajet = distance / 50; // on suppose que les employés se déplacent à 50km/h

        if (missions[i].getEnd() + temps_trajet > missions[i + 1].getStart()) { // si le temps de trajet entre les deux missions fait que la mission i+1 commence avant la fin de la mission i 
            return true;
        }

    }

    return false;
} 

bool Chromosome::isDayTooLong(Mission* missions, int count) {

    int start = 24; 
    int end = 0; 

    for (int i = 0; i < count; i++) {
        if (missions[i].getStart() < start) {
            start = missions[i].getStart();
        }
        if (missions[i].getEnd() > end) {
            end = missions[i].getEnd();
        }
    }

    if (end - start > 13) {
        return true;
    }

    return false;
}



// OPERATEURS DE MUTATION
void Chromosome::muter(){ // Echange deux missions (i.e. deux colomnes de la matrice)

    //pour chaque mission
    for(int i = 0; i < this->nb_missions; i++){ 
        // Partie 1 : On commence par effectuer une mutation pour swiper deux employés d'une mission

            //On effectue une mutation
            int randNewEmploye = rand() % nb_employes;;
            bool hasOnlyZeros = true;
            int idEmployee = -1;

            //On parcours le tableau pour trouver l'employé affecté à la misison
            for(int j = 0; j < this->nb_employes; j++){
                if(this->genes[i][j] == 1){ //Une fois qu'on l'a trouvé, on effectue la modification
                    hasOnlyZeros = false;
                    idEmployee = j;
                    break; // On arrete l'exploration du tableau
                }                
            }

            if(randNewEmploye != idEmployee){// On n'effectue pas la mutation si le nouvelle employé est le même que le précédent
                if(hasOnlyZeros){ // Si la mission n'est affecté à aucun employé, on affecte l'employé aléatoire
                    this->genes[i][randNewEmploye] = 1;
                }else{
                    // Si la mission est affecté à un employé, on l'a supprime et on affecte l'employé aléatoire
                    this->genes[i][randNewEmploye] = 1;
                    this->genes[i][idEmployee] = 0;
                }

                // Verification que la solution est valide
                bool* planning = new bool[nb_missions]; // On crée un tableau de booléen pour stocker le planning de l'employé 

                for (int j = 0; j < nb_missions; j++) {
                    planning[j] = genes[j][randNewEmploye];
                }

                if(!this->isPlaningValid(planning)){
                    // Si la solution n'est pas valide, on annule la mutation      
                    if(!hasOnlyZeros){ // Si la mission n'était pas affecté à aucun employé, on affecte l'employé du départ
                        this->genes[i][idEmployee] = 1;
                    }
                    this->genes[i][randNewEmploye] = 0;
                }
            }
        

        //Partie 2 : On effectue maintenant une mutation sur le swip de deux missions
        // On tire un nombre aléatoire entre 0 et 100

            //On effectue une mutation
            int randOtherMission;
            do{
                randOtherMission = rand() % nb_missions;
            }while(randOtherMission == i); // tant que la mission tiré aléatoirement est la même que la mission actuelle
            
            bool* temp = genes[i];
            this->genes[i] = this->genes[randOtherMission];
            this->genes[randOtherMission] = temp;

            // Verification que la solution est valide, sinon on annule la mutation
            if(!isMissionValide(i) || !isMissionValide(randOtherMission)){
                bool* temp = genes[i];
                this->genes[i] = this->genes[randOtherMission];
                this->genes[randOtherMission] = temp;
            }
        
    }
} 

// Récupère l'employé affecté à la mission puis verifie son planing
bool Chromosome::isMissionValide(int mission){
    bool* planning = new bool[this->nb_missions]; // On crée un tableau de booléen pour stocker le planning de l'employé
    int employeID = -1;
        for(int j= 0; j < this->nb_employes; j++){
            if(this->genes[mission][j] == 1){
                employeID = j;
                break;
            }
        }
        if(employeID == -1){
            return true; // Si la mission n'est affecté à aucun employé, on considère qu'elle est valide
        }else{
            for (int j = 0; j < this->nb_missions; j++) {
                planning[j] = genes[j][employeID];
            }
            if(!this->isPlaningValid(planning)){
                return false;
            }
        }

    return true;
}


void Chromosome::fusion(bool** gene1, bool** gene2, int point){ // fusionne 2 genomes
    // taille total = n, taille gene1 = n1, taille gene2 = n2, n1 + n2 = n
    // Il faut fusioner *gene1[0] à *gene2[0] ... *gene1[n1] à *gene2[n2]

    // pour chaque employé
    for (int i = 0; i < this->nb_employes; i++){
        for(int j = 0; j < this->nb_missions; j++){

            if(j<point) {
               this->genes[j][i] = gene1[j][i];
            } else {
                this->genes[j][i] = gene2[j-point][i];
            }
        }
    }
}

