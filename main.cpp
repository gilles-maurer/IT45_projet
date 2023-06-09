#include "employe.h"
#include "mission.h"
#include "centre.h"
#include "part1/group_maker.h"
#include "part1/group.h"
#include "instances/data.h"
#include "genetique/ag.h"

#include "functions.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
 
	// initialisation des parametres
	string file_name;
	int nb_generations;
	int taille_pop;
	double taux_croisement;
	double taux_mutation;
	double coefNbMisAffecte;
	double coefDistParcourue;
	double coefNbMisSpe;

	bool valid = init_parameter(argc, argv, file_name, nb_generations, taille_pop, taux_croisement, 
					taux_mutation, coefNbMisAffecte, coefDistParcourue, coefNbMisSpe);

	if (!valid) {
		return 0;
	}


	// lecture des données
	Data data(file_name);

	int nb_employes = data.count_lines("employees.csv");
	int nb_centres = data.count_lines("centres.csv");
	int nb_missions = data.count_lines("missions.csv");

	Employe *list_employe = data.read_employes(nb_employes);
	Mission *list_mission = data.read_missions(nb_missions);
	Centre *list_centre = data.read_centres(nb_centres);

	float **distance = data.read_distance(nb_missions, nb_centres);

	// on ajoute les distances aux centres
	for (int i = 0; i < nb_centres; i++) { 

		list_centre[i].setDistance(distance[i]);
	}

	// on ajoute les distances aux missions
	for (int i = 0; i < nb_missions; i++) { 
		list_mission[i].setDistance(distance[i + nb_centres], nb_centres, nb_missions);
	}

	// séparer les infos en 2 groupe (par compétence)

	// on compte le nombre d'employés LSF
	int nb_employe_lsf = 0;

	for (int i = 0; i < nb_employes; i++) {
		if (list_employe[i].getSkill() == "LSF") {
			nb_employe_lsf++;
		}
	}

	// on déduit le nombre d'employés LPC
	int nb_employe_lpc = nb_employes - nb_employe_lsf;

	// on crée les listes d'employés LSF et LPC
	Employe *list_employe_lsf = new Employe[nb_employe_lsf];
	Employe *list_employe_lpc = new Employe[nb_employe_lpc];

	// on remplit les listes d'employés LSF et LPC
	int i_lsf = 0;
	int i_lpc = 0;

	for (int i = 0; i < nb_employes; i++) {
		if (list_employe[i].getSkill() == "LSF") {
			list_employe_lsf[i_lsf] = list_employe[i];
			list_employe_lsf[i_lsf].setIdSkill(i_lsf + 1);
			i_lsf++;
		}
		else {
			list_employe_lpc[i_lpc] = list_employe[i];
			list_employe_lpc[i_lpc].setIdSkill(i_lpc + 1);
			i_lpc++;
		}
	}

	// on compte le nombre de missions LSF
	int nb_missions_lsf = 0;

	for (int i = 0; i < nb_missions; i++) {
		if (list_mission[i].getSkill() == "LSF") {
			nb_missions_lsf++;
		}
	}

	// on déduit le nombre de missions LPC
	int nb_missions_lpc = nb_missions - nb_missions_lsf;

	// on crée les listes de missions LSF et LPC
	Mission *list_mission_lsf = new Mission[nb_missions_lsf];
	Mission *list_mission_lpc = new Mission[nb_missions_lpc];

	// on remplit les listes de missions LSF et LPC
	i_lsf = 0;
	i_lpc = 0;

	for (int i = 0; i < nb_missions; i++) {
		if (list_mission[i].getSkill() == "LSF") {
			list_mission_lsf[i_lsf] = list_mission[i];
			list_mission_lsf[i_lsf].setIdSkill(i_lsf + 1);
			i_lsf++;
		}
		else {
			list_mission_lpc[i_lpc] = list_mission[i];
			list_mission_lpc[i_lpc].setIdSkill(i_lpc + 1);
			i_lpc++;
		}
	}

	// création des groupes (part 1)
	GroupMaker group_maker_lsf = GroupMaker(nb_missions_lsf, nb_centres, list_mission_lsf, list_centre);
	GroupMaker group_maker_lpc = GroupMaker(nb_missions_lpc, nb_centres, list_mission_lpc, list_centre);

	group_maker_lsf.makeGroups();
	group_maker_lpc.makeGroups();


	// affichage des groupes (part 1)
	// cout << "Groupes pour les missions LSF : " << endl;
	// group_maker_lsf.printGroups();

	// cout << "Groupes pour les missions LPC : " << endl;
	// group_maker_lpc.printGroups();


    // algo genetique (part 2)
	cout << ("----------------") << endl;
	cout << ("Algorithme genetique") << endl;
	cout << ("----------------") << endl;

	// résolution du problème pour les missions LSF
	Ag ag = Ag(nb_generations, taille_pop, taux_croisement, taux_mutation,
		coefNbMisAffecte, coefDistParcourue, coefNbMisSpe,
		list_mission_lsf, nb_missions_lsf, list_employe_lsf, nb_employe_lsf, list_centre, nb_centres,
		group_maker_lsf.getListGroups(), nb_centres);

	ag.initialiser(); // on initialise la population
	Chromosome *solution_lsf = ag.optimiser(); // on optimise la population

	// résolution du problème pour les missions LPC
	ag = Ag(nb_generations, taille_pop, taux_croisement, taux_mutation,
		coefNbMisAffecte, coefDistParcourue, coefNbMisSpe,
		list_mission_lpc, nb_missions_lpc, list_employe_lpc, nb_employe_lpc, list_centre, nb_centres,
		group_maker_lpc.getListGroups(), nb_centres);

	ag.initialiser(); // on initialise la population
	Chromosome *solution_lpc = ag.optimiser(); // on optimise la population


	// affichage des solutions (part 2)
	// stats de la solution lsf
	cout << "Resultat pour les missions LSF : " << endl;
	solution_lsf->stats();

	// stats de la solution lpc 
	cout << "Resultat pour les missions LPC : " << endl;
	solution_lpc->stats();

	// stats de la solution globale
	print_stats_lsf_lpc(solution_lsf, solution_lpc);

}