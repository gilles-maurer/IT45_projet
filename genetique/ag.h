#ifndef _AG_H
#define _AG_H


#include <math.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "population.h"
#include "chromosome.h"
#include "../mission.h"
#include "../employe.h"
#include "../centre.h"
#include "../part1/group.h"


using namespace std;
// La classe Ag définie les paramétres d'une exécution d'un algorithme
//    évolutionniste ainsi que la procédure principale de recherche
class Ag{

private:
    // ATTRIBUTS
	int nbgenerations;       // nombre de générations aprés quoi la recherche est arrétée
	int taille_pop;          // nombre d'individus dans la population
	double taux_croisement;  // taux de croisement : valeur entre 0 et 1
	double taux_mutation;    // taux de mutation : valeur entre 0 et 1
  	double coefNbMisAffecte; // coefficient du nombre de mission affecté
    double coefDistParcourue; // coefficient de la distance parcourue par les employés dans la solution
    double coefNbMisSpe; //	 coefficient du nombre de mission ou la spécialité est respectée
	Population *pop;         // liste des individus de la population

	Mission *list_missions;
	int nb_missions;
	Employe *list_employes;
	int nb_employes;
	Centre *list_centres;
	int nb_centres;

	Group *list_group;
	int nb_group;
	
public:
	// CONSTRUCTEURS
	Ag(int nbgenerations,
	int taille_pop,         
	double taux_croisement,  
	double taux_mutation,
	double coefNbMisAffecte,
    double coefDistParcourue,
    double coefNbMisSpe,
	Mission *list_missions,
	int nb_missions,
	Employe *list_employes,
	int nb_employes,
	Centre *list_centres,
	int nb_centres, 
	
	Group *list_group,
	int nb_group);
                             // constructeur de l'objet Algaorithme evolutioniste
	~Ag();                   // destructeur de l'objet Ag

	// METHODES
	Chromosome* optimiser(); // fonction principale qui décrit le déroulement de l'algorithme évolusionniste

	// OPERATEURS DE CROISEMENT

	void initialiser();

	bool isPlaningValid(bool* planing);

	Mission* sortMission(Mission* missions, int count);
	float rideTime(Mission* missions, int count);
	bool areMissionsOverlapping(Mission* missions, int count); 
	bool isDayTooLong(Mission* missions, int count);

};


#endif // _AG_H