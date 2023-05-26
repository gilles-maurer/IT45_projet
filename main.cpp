#include "employe.h"
#include "mission.h"
#include "centre.h"
// #include "kmean/kmean.h"
#include "instances/data.h"
#include "genetique/population.h"

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

	Population individus = Population(10, 10);
	individus.afficher();
	individus.statistiques();
	getchar();

<<<<<<< Updated upstream
    // lecture des infos dans le fichier 
=======
    // lecture des infos dans le fichier
	/**
	Employe *list_employe; 
	int nb_employe;
	Centre *list_centre;
	int nb_centre;
	Mission *list_mission;
	int nb_missions; 
>>>>>>> Stashed changes

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

	Employe *list_employe_lsf;
	int nb_employe_lsf;
	Mission *list_mission_lsf;
	int nb_missions_lsf;

	Employe *list_employe_lpc;
	int nb_employe_lpc;
	Mission *list_mission_lpc;
	int nb_missions_lpc;**/


    // kmean 






    // algo genetique


    // fusion des resultats


    // affichage des resultats
    cout << "La meilleure solution trouvee pour la competence 1 est : " << endl;
    // afficher la meilleure solution
    cout << "La meilleure solution trouvee pour la competence 2 est : " << endl;
    // afficher la meilleure solution
    cout << "La meilleure solution totale est : " << endl;
    // afficher la meilleure solution

}