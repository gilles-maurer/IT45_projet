#include "functions.h"

using namespace std;

string get_file_name(int file_number)
{

    string file_name;
    
    switch (file_number) {

        case 1:
			file_name = "instances/30Missions-2centres/";
			break;
		case 2:
			file_name = "instances/66Missions-2centres/";
			break;
		case 3:
			file_name = "instances/94Missions-2centres/";
			break;
		case 4:
			file_name = "instances/94Missions-3centres/";
			break;
		case 5:
			file_name = "instances/100Missions-2centres/";
			break;
		case 6:
			file_name = "instances/200Missions-2centres/";
			break;
    }

    return file_name;
}


void init_parameter(int argc, char **argv, string &file_name, int &nb_generations, int &taille_pop, 
                    double &taux_croisement, double &taux_mutation, double &coefNbMisAffecte, 
                    double &coefDistParcourue, double &coefNbMisSpe) {

    
    // valeurs par défaut
	file_name = "instances/30Missions-2centres/";
	nb_generations = 10;
	taille_pop = 10;          
	taux_croisement = 0.5;  
	taux_mutation = 0.5;
	coefNbMisAffecte = 100;
	coefDistParcourue = 1;
	coefNbMisSpe = 5;


	if (argc == 1) { // pas de parametres
		cout << "Parametres par default" << endl;
	}
	else if (argc == 2) { // juste le nom du fichier 
		
		// initialisation du fichier
		file_name = get_file_name(atoi(argv[1]));

	} else if (argc == 4) {

		file_name = get_file_name(atoi(argv[1]));

		nb_generations = atoi(argv[2]);
		taille_pop = atoi(argv[3]);

	} else if (argc == 6) {

		file_name = get_file_name(atoi(argv[1]));

		nb_generations = atoi(argv[2]);
		taille_pop = atoi(argv[3]);
		taux_croisement = atof(argv[4]);
		taux_mutation = atof(argv[5]);

	} else if (argc == 9) { // tous les parametres

		file_name = get_file_name(atoi(argv[1]));

		nb_generations = atoi(argv[2]);
		taille_pop = atoi(argv[3]);          
		taux_croisement = atof(argv[4]);
		taux_mutation = atof(argv[5]);
		coefNbMisAffecte = atof(argv[6]);
		coefDistParcourue = atof(argv[7]);
		coefNbMisSpe = atof(argv[8]);
	
	} else {
		cout << "Nombre de parametres incorrect" << endl;
        EXIT_FAILURE;
	}


}