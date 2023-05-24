#ifndef _AG_H
#define _AG_H


#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "population.h"
#include "chromosome.h"


using namespace std;
// La classe Ag d�finie les param�tres d'une ex�cution d'un algorithme
//    �volutionniste ainsi que la proc�dure principale de recherche
class Ag{
public:
    // ATTRIBUTS

	
	int nbgenerations;       // nombre de g�n�rations apr�s quoi la recherche est arr�t�e
	int taille_pop;          // nombre d'individus dans la population
	double taux_croisement;  // taux de croisement : valeur entre 0 et 1
	double taux_mutation;    // taux de mutation : valeur entre 0 et 1
	int taille_chromosome;   // nombre de g�nes dans le chromosome
	population *pop;         // liste des individus de la population
    int **les_distances;     // matrice des distances entre les villes
	

	// CONSTRUCTEURS
	Ag();
                             // constructeur de l'objet Algaorithme evolutioniste
	~Ag();                   // destructeur de l'objet Ag

	// METHODES
	Chromosome* optimiser(); // fonction principale qui d�cit le d�roulement de l'algorithme �volusionniste

	// OPERATEURS DE CROISEMENT
	// opérateur de croisement de deux Chromosomes
    void croisement(Chromosome* parent1, Chromosome* parent2,
                      Chromosome* enfant1, Chromosome* enfant2);

};


#endif // _AG_H