#ifndef _CHROMOSOME_H
#define _CHROMOSOME_H


#include <math.h>
#include <stdio.h>
#include <iostream>

// La classe chromosome represente la structure d'une solution du probléme
class Chromosome{
private:
    // ATTRIBUTS
	bool **genes;         // les génes du chromosome/solution 1 mission regarde à qui elle est associé employé puis mission
	int taille;         // la taille du chromosome = nombre de génes
	int fitness;        // la valeur de la fonction objectif (fitness) de la solution

public:
	// CONSTRUCTEURS
	Chromosome();
	Chromosome(int tc); // constructeur de l'objet aléatoirement
	~Chromosome();      // destructeur de l'objet

	// METHODES
	void afficher();    // fonction d'affichage du Chromosome (i.e. de la solution)
	void evaluer();
	                    // fonction d'évaluation du Chromosome (c-é-d calcul la fitness)
                        //   Elle doit etre lancée é la creation des solution et apres
					    //   l'exécution des operateurs de mutation et de croisement
    void ordonner();    // ordonne le sens de la tournée si gene[1] > gene[taille-1]
    void copier(Chromosome* source);  // copie le Chromosome 'source'
	bool** getGene();	 // retourne le tableau de genes
	int getFitness();	 // retourne la fitness
	int getTaille();	 // retourne la taille
    bool identique(Chromosome* chro); // test si 2 chromosome sont identique

	//Surchage d'opérateur

    // OPERATEURS DE MUTATION
    void mutation();    // opérateur de mutation
};










#endif // _CHROMOSOME_H