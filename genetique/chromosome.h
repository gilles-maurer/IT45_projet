#ifndef _CHROMOSOME_H
#define _CHROMOSOME_H

#include "../mission.h"
#include "../employe.h"
#include "../centre.h"

#include <math.h>
#include <stdio.h>
#include <iostream>

// La classe chromosome represente la structure d'une solution du probléme
class Chromosome{
private:
    // ATTRIBUTS
	bool **genes;         // les génes du chromosome/solution 1 mission regarde à qui elle est associé employé puis mission

	int nb_missions;
	int nb_employes;
	int nb_centres;

	Mission *list_missions;
	Employe *list_employes;
	Centre *list_centres;



	int fitness;        // la valeur de la fonction objectif (fitness) de la solution

public:
	// CONSTRUCTEURS
	Chromosome();
	Chromosome(int nb_missions, int nb_employes, int nb_centres, Mission *list_missions, Employe *list_employes, Centre *list_centres);  
	~Chromosome();      // destructeur de l'objet

	// METHODES
	void evaluer(double coefNbMisAffecte, double coefDistParcourue, double coefNbMisSpe);
	                    // fonction d'évaluation du Chromosome (c-é-d calcul la fitness)
                        //   Elle doit etre lancée é la creation des solution et apres
					    //   l'exécution des operateurs de mutation et de croisement

	Mission* sortMission(Mission* missions, int count);
	float ridelenght(Mission* missions, int count, int id_employe);


    void ordonner();    // ordonne le sens de la tournée si gene[1] > gene[taille-1]
    void copier(Chromosome* source);  // copie le Chromosome 'source'
	void copier(bool** genes);  // copie le gene 'source'
	bool** getGene();	 // retourne le tableau de genes
	bool** getGene(int firstPoint, int lastPoint); // retourne le tableau de genes entre deux point
	int getFitness();	 // retourne la fitness

    bool identique(Chromosome* chro); // test si 2 chromosome sont identique

	Chromosome* fusion(Chromosome* chro1, Chromosome* chro2); // fusionne 2 chromosomes
	void fusion(bool** gene1, bool** gene2, int point); // fusionne 2 genomes

	void print(); // fonction d'affichage du Chromosome (i.e. de la solution)

    // OPERATEURS DE MUTATION
    void muter(int taux);    // opérateur de mutation

};










#endif // _CHROMOSOME_H