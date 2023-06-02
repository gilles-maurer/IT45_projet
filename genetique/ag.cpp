#include "ag.h"


using namespace std;


// CONSTRUCTEUR 
Ag::Ag(int nbgenerations, int taille_pop, double taux_croisement, double taux_mutation, 
            double coefNbMisAffecte, double coefDistParcourue, double coefNbMisSpe, 
            Mission *list_missions, int nb_missions, Employe *list_employes, int nb_employes, 
            Centre *list_centres, int nb_centres, Group *list_group, int nb_group) {
    this->nbgenerations = nbgenerations;
    this->taille_pop = taille_pop;
    this->taux_croisement = taux_croisement;
    this->taux_mutation = taux_mutation;
    this->coefNbMisAffecte = coefNbMisAffecte;
    this->coefDistParcourue = coefDistParcourue;
    this->coefNbMisSpe = coefNbMisSpe;
    this->pop = new Population(taille_pop, nb_missions, nb_employes);

    this->list_missions = list_missions;
    this->nb_missions = nb_missions;
    this->list_employes = list_employes;
    this->nb_employes = nb_employes;
    this->list_centres = list_centres;
    this->nb_centres = nb_centres;

    this->list_group = list_group;
    this->nb_group = nb_group;
}

// DESTRUCTEUR
Ag::~Ag() {

}


// METHODES

// fonction principale qui décit le déroulement de l'algorithme évolusionniste
Chromosome* Ag::optimiser() {

    // évaluation de la population (appel de la fonction evaluer de chaque individu)
    this->pop->evaluer(this->coefNbMisAffecte, this->coefDistParcourue, this->coefNbMisSpe); 
    // affichage des statistiques de la population
    this->pop->statistiques(this->coefNbMisAffecte, this->coefDistParcourue, this->coefNbMisSpe);
    // boucle principale de l'algorithme
    for (int i = 0; i < this->nbgenerations; i++) {

        cout << "Generation " << i << endl;

        // sélection de deux parents
        Chromosome* parent1 = this->pop->selection_roulette();
        Chromosome* parent2 = this->pop->selection_roulette();
        // croisement des deux parents
        Chromosome* enfant1 = new Chromosome(this->nb_missions, this->nb_employes);
        Chromosome* enfant2 = new Chromosome(this->nb_missions, this->nb_employes);
        this->croisement(parent1, parent2, enfant1, enfant2);
        // mutation des deux enfants
        enfant1->muter(this->taux_mutation);
        enfant2->muter(this->taux_mutation);
        // évaluation des deux enfants
        enfant1->evaluer(this->coefNbMisAffecte, this->coefDistParcourue, this->coefNbMisSpe);
        enfant2->evaluer(this->coefNbMisAffecte, this->coefDistParcourue, this->coefNbMisSpe);
        // remplacement des deux parents par les deux enfants
        this->pop->remplacement_roulette(enfant1);
        this->pop->remplacement_roulette(enfant2);
        // affichage des statistiques de la population
        this->pop->statistiques(this->coefNbMisAffecte, this->coefDistParcourue, this->coefNbMisSpe);
    }
    // affichage des statistiques de la population
    this->pop->statistiques(this->coefNbMisAffecte, this->coefDistParcourue, this->coefNbMisSpe);

    // retourne le meilleur individu de la population

    // change this
    return new Chromosome();
}  


// OPERATEURS DE CROISEMENT
// opérateur de croisement de deux Chromosomes

void Ag::croisement(Chromosome* parent1, Chromosome* parent2,
                      Chromosome* enfant1, Chromosome* enfant2) {
    // tirage aléatoire d'un point de croisement
    int point = rand() % this->nb_missions-1;

    // copie des gènes des parents dans les enfants
    enfant1->fusion(parent1->getGene(0, point), parent2->getGene(point+1, this->nb_missions), point); // enfant1 = parent1[0:point] + parent2[point+1:nb_missions]
    enfant2->fusion(parent2->getGene(0, point), parent1->getGene(point+1, this->nb_missions), point); // enfant2 = parent2[0:point] + parent1[point+1:nb_missions]
}

bool Ag::isPlaningValid(bool* planning) { // planning correspond donc à toutes les missions affectées à un employé 

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

float Ag::rideTime(Mission* missions, int count) {

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

Mission* Ag::sortMission(Mission* missions, int count) {

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

bool Ag::areMissionsOverlapping(Mission* missions, int count) {

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

bool Ag::isDayTooLong(Mission* missions, int count) {

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

void Ag::initialiser(){
    cout << "Initialisation de la population" << endl;
    int nb_solutions = 0; // Nombre de solutions trouvées (pour savoir si on a trouvé autant de solutions valides que de population)

    // Tant qu'on a pas trouvé autant de solutions valides que de population
    while(nb_solutions < this->nbgenerations){

        bool** genes = new bool*[this->nb_missions];

        bool hasFound = false; // Permet de savoir si on a reussis à trouver une solution valide

        // Pour chaque groupe 
        for(int numGroupe = 0; numGroupe < this->nb_group; numGroupe++){
            // On récupère le centre du groupe
            Centre centre = this->list_group[numGroupe].getCentre();

            // On récupère les missions du groupe
            Mission *list_missions = this->list_group[numGroupe].getListMissions();

            // On récupère le nombre de mission du groupe
            int nb_mission = this->list_group[numGroupe].getNbMissions();

            // On récupère la liste des employés du centre du groupe
            Employe *list_employes;
            int count = 0;
            for(int numEmploye = 0; numEmploye < this->nb_employes; numEmploye++){
                if(this->list_employes[numEmploye].getCentreId() == centre.getId()){
                    list_employes[count] = this->list_employes[numEmploye];
                    count++;
                }
            }
            
            for(int numMission = 0; numMission < nb_mission; numMission++){ // Pour chaque mission (du groupe)
                // on affecte aléatoirement un employé à la mission, pour eviter de tourner indefiniment, on limite le nombre d'essai au nombre d'employés
                hasFound = false; // Pour savoir si on a reussis une affectation, on arrete la recherche si on n'a pas reussis
                for(int i = 0; i < count; i++){
                    // On tire un nombre aléatoire entre 0 et le nombre d'employés

                    int employeSelectionned = rand() % count;
                    // On affecte l'employé à la mission
                    genes[numMission][employeSelectionned] = 1;

                    bool* planning = new bool[nb_missions]; // On crée un tableau de booléen pour stocker le planning de l'employé 

                    for (int j = 0; j < nb_missions; j++) {
                        planning[j] = genes[j][employeSelectionned];
                    }
                    
                    // On verifie que l'affectation fournie une solution valide
                    if(!this->isPlaningValid(planning)){
                        // Si la solution n'est pas valide on recommence
                        genes[numMission][employeSelectionned] = 0;
                    }else{
                        // Si la solution est valide on arrete la recherche
                        cout << "Affectation valide trouvée pour la mission " << list_missions[numMission].getId() << endl;
                        hasFound = true;
                        break;
                    }
                }
                if (!hasFound){
                    cout << "Erreur, pas d'affectation valide trouvée pour la mission " << list_missions[numMission].getId() << endl;
                    break;// On arrete l'exploration de cette population
                }
            }

            if (!hasFound){
                cout << "Erreur, pas d'affectation valide trouvée pour le groupe" << endl;
                break;// On arrete l'exploration de cette population
            }
        }

        if(hasFound){
            // On ajoute la solution à la population
            this->pop->ajouter(genes, nb_solutions);

            // On a trouvé une solution valide
            nb_solutions++;
        }
    }
    this->pop->statistiques(this->coefNbMisAffecte, this->coefDistParcourue, this->coefNbMisSpe);

}