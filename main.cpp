#include "employe.h"
#include "mission.h"
#include "centre.h"
#include "kmean.h"

#include <iostream>



using namespace std;

int main(int argc, char **argv)
{
 
    // valeurs par défaut



	if (argc == 7)
	{
        // initialisation des parametres
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


    // lecture des infos dans le fichier

	Employe *list_employe; 
	int nb_employe;
	Centre *list_centre;
	int nb_centre;
	Mission *list_mission;
	int nb_missions; 




	// séparer les infos en 2 groupe (par compétence)

	Employe *list_employe_lsf;
	int nb_employe_lsf;
	Mission *list_mission_lsf;
	int nb_missions_lsf;

	Employe *list_employe_lpc;
	int nb_employe_lpc;
	Mission *list_mission_lpc;
	int nb_missions_lpc;


    // kmean 






    // algo genetique


    // fusion des resultats


    // affichage des resultats
    cout << "La meilleure solution trouvee pour la compétence 1 est : ";
    // afficher la meilleure solution
    cout << "La meilleure solution trouvee pour la compétence 2 est : ";
    // afficher la meilleure solution
    cout << "La meilleure solution totale est : ";
    // afficher la meilleure solution

}