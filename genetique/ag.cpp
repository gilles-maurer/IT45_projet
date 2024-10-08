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
    this->pop = new Population(taille_pop, nb_missions, nb_employes, nb_centres, list_missions, list_employes, list_centres);       

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


    Chromosome* meilleurIndividu = new Chromosome(this->nb_missions, this->nb_employes, this->nb_centres, 
                                                    this->list_missions, this->list_employes, this->list_centres);

    // évaluation de la population (appel de la fonction evaluer de chaque individu)
    this->pop->evaluer(this->coefNbMisAffecte, this->coefDistParcourue, this->coefNbMisSpe); 

    // on démarre le chronomètre
    clock_t start = clock();
    
    // on lance la boucle principale de l'algorithme
    for (int i = 0; i < this->nbgenerations; i++) {

        // on vérifie si on a atteint le temps limite
        clock_t end = clock();
        double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
        if (elapsed_secs > 60) {
            cout << "Temps limite atteint" << endl;
            break;
        }

        cout << "Generations :" << i << endl;
        
        // Création de la liste d'enfants :
        Chromosome* list_enfants = new Chromosome[this->taille_pop];

        // On va créer une liste d'enfants de la même taille que la population
        for(int j=0; j< this->taille_pop/2; j++){
            // croisement des deux parents

            // On tire aléatoirement un nombre entre 0 et 100 pour savoir si on croise ou non
            int random = rand() % 100;

            // Si le nombre est inférieur au taux de croisement*100 (taux de croisement entre 0 et 1) alors on croise
            // sélection de deux parents
            Chromosome* parent1 = this->pop->selection_roulette();
            Chromosome* parent2 = this->pop->selection_roulette();

            if (random < this->taux_croisement*100){

                // sélection des enfants
                Chromosome* enfant1 = new Chromosome(this->nb_missions, this->nb_employes, this->nb_centres, 
                                                        this->list_missions, this->list_employes, this->list_centres);
                Chromosome* enfant2 = new Chromosome(this->nb_missions, this->nb_employes, this->nb_centres, 
                                                    this->list_missions, this->list_employes, this->list_centres);

                // croisement des deux parents
                this->pop->croisement(parent1, parent2, enfant1, enfant2);

                // mutation des deux enfants
                // On tire aléatoirement un nombre entre 0 et 100 pour savoir si on croise ou non
                int random = rand() % 100;
                // Si le nombre est inférieur au taux de mutation*100 (taux de mutation entre 0 et 1) alors on mute
                if (random < this->taux_mutation*100){
                    enfant1->muter();
                    enfant2->muter();
                }
                // évaluation des deux enfants
                enfant1->evaluer(this->coefNbMisAffecte, this->coefDistParcourue, this->coefNbMisSpe);
                enfant2->evaluer(this->coefNbMisAffecte, this->coefDistParcourue, this->coefNbMisSpe);
                // Affectation des enfants à la liste d'enfants
                list_enfants[2*j] = *enfant1;
                list_enfants[2*j+1] = *enfant2;
            }else{
                // On tire aléatoirement un nombre entre 0 et 100 pour savoir si on croise ou non
                int random = rand() % 100;
                // Si le nombre est inférieur au taux de mutation*100 (taux de mutation entre 0 et 1) alors on mute
                if (random < this->taux_mutation*100){
                    parent1->muter();
                    parent2->muter();
                }
                // évaluation des deux nouveaux parents
                parent1->evaluer(this->coefNbMisAffecte, this->coefDistParcourue, this->coefNbMisSpe);
                parent2->evaluer(this->coefNbMisAffecte, this->coefDistParcourue, this->coefNbMisSpe);
                // Affectation des parents à la liste d'enfants
                list_enfants[2*j] = *parent1;
                list_enfants[2*j+1] = *parent2;
            }
            

        }


        this->pop->remplacement_roulette(list_enfants);
        

        if (this->pop->getMeilleurIndividu()->getFitness() > meilleurIndividu->getFitness()) {
            meilleurIndividu = this->pop->getMeilleurIndividu();

            cout << "Nouveau meilleur individu" << endl;
            meilleurIndividu->stats();
            
        }

        // affichage des statistiques de la population
        this->pop->statistiques();
    }

    // retourne le meilleur individu de la population
    return meilleurIndividu;
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

bool Ag::areMissionsOverlapping(Mission* missions, int count) {

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
    srand(time(NULL));
 
    // Tant qu'on a pas trouvé autant de solutions valides que de population
    for(int nbsol = 0; nbsol < this->taille_pop; nbsol++){

        bool** genes = new bool*[this->nb_missions];
        for(int i = 0; i < this->nb_missions; i++){
            genes[i] = new bool[this->nb_employes];
        }

        for(int i = 0; i < this->nb_missions; i++){
            for(int j = 0; j < this->nb_employes; j++){
                genes[i][j] = false; // Initialisation à false (0)
            }
        }

        bool hasFound = false; // Permet de savoir si on a reussis à trouver une solution valide

        // Pour chaque groupe 
        for(int numGroupe = 0; numGroupe < this->nb_group; numGroupe++){
            
            // On récupère le centre du groupe
            // Plus de chance de choisir le centre du groupe mais pas obligatoire
            // On tire un nombre aléatoire entre 1 et 3, si le nombre est inferieur à 2 on choisit un employé du groupe        
            Centre centreGroupe = this->list_group[numGroupe].getCentre();

            // On récupère les missions du groupe
            Mission *list_missions = this->list_group[numGroupe].getListMissions();

            // On récupère le nombre de mission du groupe
            int nb_mission = this->list_group[numGroupe].getNbMissions();

            for(int numMission = 0; numMission < nb_mission; numMission++){ // Pour chaque mission (du groupe)
                // on affecte aléatoirement un employé à la mission, pour eviter de tourner indefiniment, on limite le nombre d'essai au nombre d'employés
                for(int i = 0; i < this->nb_employes; i++){ // POur eviter de boucler indéfiniment, on limite le nombre d'essai au nombre d'employés
                    // nombre aléatoire pour choisir si on va essayer d'affecter un emplouyé du groupe ou non. Permet d'avoir des changements entre les populaitons 
                    int random = rand() % 3 + 1; // On tire un nombre aléatoire entre 1 et 3
                    int employeSelectionned = -1;
                    int idMission = list_missions[numMission].getIdSkill() -1;

                    // on verifie qu'il y a au moins un employé dans le centre du groupe
                    bool hasEmploye = false;
                    for (int i = 0; i < this->nb_employes; i++) {
                        if (this->list_employes[i].getCentreId() == list_group[numGroupe].getCentre().getId()) {
                            hasEmploye = true;
                            break;
                        }
                    }   

                    // on verifie qu'il y a au moins un employé dans un autre centre que celui du groupe
                    bool hasAllEmploye = true;
                    for (int i = 0; i < this->nb_employes; i++) {
                        if (this->list_employes[i].getCentreId() != list_group[numGroupe].getCentre().getId()) {
                            hasAllEmploye = false;
                            break;
                        }
                    }

                    if (hasEmploye == 0) { // il n'y a pas d'employé dans le centre du groupe
                        
                        employeSelectionned = rand() % (this->nb_employes); // On tire un nombre aléatoire entre 0 et le nombre d'employés

                    } else if (hasAllEmploye == 1) { // il n'y a que des employés dans le centre du groupe

                        employeSelectionned = rand() % (this->nb_employes); // On tire un nombre aléatoire entre 0 et le nombre d'employés

                    } else if(random <=2){ // On choisi un employé du groupe 2 fois sur 3
                        //On choisie un employé au hasard dont le centre est le centre du groupe
                        do{
                            //cout << "On choisie un employé au hasard dont le centre est le centre du groupe" << endl;
                            employeSelectionned = rand() % (this->nb_employes); // On tire un nombre aléatoire entre 0 et le nombre d'employés
                        } while (this->list_employes[employeSelectionned].getCentreId() != this->list_group[numGroupe].getCentre().getId()); // On recommence tant qu'on a pas trouvé un centre different du centre du groupe

                    }else{
                        //On choisie un employé au hasard dont le centre n'est pas le centre du groupe
                        do{
                            //cout << "On choisie un employé au hasard" << endl;
                            employeSelectionned = rand() % (this->nb_employes); // On tire un nombre aléatoire entre 0 et le nombre d'employés
                        } while (this->list_employes[employeSelectionned].getCentreId() == this->list_group[numGroupe].getCentre().getId()); // On recommence tant qu'on a pas trouvé un centre different du centre du groupe   
                    }

                    // On affecte l'employé à la mission
                    genes[idMission][list_employes[employeSelectionned].getIdSkill()-1] = 1;
                    
                    bool* planning = new bool[nb_missions]; // On crée un tableau de booléen pour stocker le planning de l'employé 

                    for (int j = 0; j < nb_missions; j++) {
                        planning[j] = genes[j][list_employes[employeSelectionned].getIdSkill()-1];
                    }
                    
                    // On verifie que l'affectation fournie une solution valide
                    if(!this->isPlaningValid(planning)){
                        // Si la solution n'est pas valide on recommence
                        genes[idMission][list_employes[employeSelectionned].getIdSkill()-1] = 0;
                    }else{
                        // Si la solution est valide on arrete la recherche
                        break;
                    }
                }
            }
        }
               

        //On ajoute la solution à un nouvel individu de la population
        this->pop->ajouter(genes, nbsol);

    }

}