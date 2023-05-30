#include "employe.h"
#include "mission.h"
#include "centre.h"
#include "part1/group_maker.h"
#include "part1/group.h"
#include "instances/data.h"
#include "genetique/ag.h"

#include <iostream>
#include <string>


using namespace std;

int main(int argc, char **argv)
{
 
    // valeurs par défaut
	string file_name = "instances/30Missions-2centres/";


	if (argc == 2)
	{
        // initialisation des parametres
		file_name = argv[1];
	}
	else if (argc == 1)
	{
		cout << "Parametres par default" << endl;
	}
	else
	{
		cout << "Nombre d'arguments n'est pas correct." << endl;
		cout << "Soit l'executable 'algo_evo' ne prend pas d'arguments soit il prend 6 arguments : " << endl;
		cout << "   1. nombre de generation (entier > 0)" << endl;
		cout << "   2. taille de la population (entier > 0)" << endl;
		cout << "   3. taux de croisement (0 <= reel <= 1)" << endl;
		cout << "   4. taux de mutation (0 <= reel <= 1)" << endl;
		cout << "   5. nombre de villes (=taille d'un chromosome)" << endl;
		cout << "   6. nom du fichier indiquant les distances entre villes" << endl;
		exit(EXIT_FAILURE);
	}

	Data data(file_name);

	int nb_employes = data.count_lines("employees.csv");
	int nb_centres = data.count_lines("centres.csv");
	int nb_missions = data.count_lines("missions.csv");

	Employe *list_employe = data.read_employes(nb_employes);
	Mission *list_mission = data.read_missions(nb_missions);
	Centre *list_centre = data.read_centres(nb_centres);

	float **distance = data.read_distance(nb_missions, nb_centres);

	for (int i = 0; i < nb_centres; i++) { // on ajoute les distances aux centres
		list_centre[i].setDistance(distance[i]);
	}
	for (int i = nb_centres; i < nb_missions; i++) { // on ajoute les distances aux missions
		list_mission[i].setDistance(distance[i]);
	}

	// initialisation des parametres


	// séparer les infos en 2 groupe (par compétence)

	int nb_employe_lsf = 0;

	for (int i = 0; i < nb_employes; i++) {
		if (list_employe[i].getSkill() == "LSF") {
			nb_employe_lsf++;
		}
	}

	int nb_employe_lpc = nb_employes - nb_employe_lsf;

	Employe *list_employe_lsf = new Employe[nb_employe_lsf];
	Employe *list_employe_lpc = new Employe[nb_employe_lpc];

	int i_lsf = 0;
	int i_lpc = 0;

	for (int i = 0; i < nb_employes; i++) {
		if (list_employe[i].getSkill() == "LSF") {
			list_employe_lsf[i_lsf] = list_employe[i];
			i_lsf++;
		}
		else {
			list_employe_lpc[i_lpc] = list_employe[i];
			i_lpc++;
		}
	}

	int nb_missions_lsf = 0;

	for (int i = 0; i < nb_missions; i++) {
		if (list_mission[i].getSkill() == "LSF") {
			nb_missions_lsf++;
		}
	}

	int nb_missions_lpc = nb_missions - nb_missions_lsf;

	Mission *list_mission_lsf = new Mission[nb_missions_lsf];
	Mission *list_mission_lpc = new Mission[nb_missions_lpc];

	i_lsf = 0;
	i_lpc = 0;

	for (int i = 0; i < nb_missions; i++) {
		if (list_mission[i].getSkill() == "LSF") {
			list_mission_lsf[i_lsf] = list_mission[i];
			i_lsf++;
		}
		else {
			list_mission_lpc[i_lpc] = list_mission[i];
			i_lpc++;
		}
	}

	
	// création des groupes (part 1)

	GroupMaker group_maker_lsf = GroupMaker(nb_missions_lsf, nb_centres, list_mission_lsf, list_centre);
	GroupMaker group_maker_lpc = GroupMaker(nb_missions_lpc, nb_centres, list_mission_lpc, list_centre);

	group_maker_lsf.makeGroups();
	group_maker_lpc.makeGroups();

	// affichage des groupes (part 1)

	cout << "Groupes pour les missions LSF : " << endl;
	group_maker_lsf.printGroups();

	cout << "Groupes pour les missions LPC : " << endl;
	group_maker_lpc.printGroups();


    // algo genetique
	// cout << ("----------------") << endl;
	// Ag ag = Ag(10, 10, 0.5, 0.5, nb_missions, 0.2, 0.1, 0.7); // A separer en 2 plus tard

	cout << ("----------------") << endl;

    // fusion des resultats


    // affichage des resultats
    cout << "La meilleure solution trouvee pour la competence 1 est : " << endl;
    // afficher la meilleure solution
    cout << "La meilleure solution trouvee pour la competence 2 est : " << endl;
    // afficher la meilleure solution
    cout << "La meilleure solution totale est : " << endl;
    // afficher la meilleure solution

}