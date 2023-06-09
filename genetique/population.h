#ifndef _POPULATION_H
#define _POPULATION_H


#include <math.h>
#include <stdio.h>
#include <iostream>
#include "chromosome.h"

// La classe population englobe plusieurs solution potentielle du probleme
class Population{
private:
    // ATTRIBUTS
	int taille_pop;          // nombre d'individus de la population
	int *ordre;              // tableau donnat l'ordre des individus dans la population

	int nb_missions;
	int nb_employes;
	int nb_centres;

	Mission *list_missions;
	Employe *list_employes;
	Centre *list_centres;

	Chromosome *individus;  // liste des individus de la population

                             //   du meilleur au plus mauvais en fonction de la fitness	population(int tp, int tc);    // constructeur de l'objet
public:


	// CONSTRUCTEURS
	Population(int tp, int nb_missions, int nb_employes, int nb_centres, Mission *list_missions, Employe *list_employes, Centre *list_centres); // constructeur de l'objet
	
	~Population();              // destructeur de l'objet

	// METHODES
	void statistiques(); // affiche quelques statistiques sur la population
	int nb_Chromosomes_similaires(Chromosome* chro);
	                     // compte le nombre de Chromosomes similaires � 'chro'
	void similitude();   // affiche les r�sultats du comptage de Chromosomes similaires
	                     // aux meilleurs individus de la population.

	Chromosome *getMeilleurIndividu(); // renvoie le meilleur individu de la population

    // OPERATEURS DE SELECTION ET DE REMPLACEMENT
    Chromosome *selection_roulette();                 // sel�ction par roulette biais�e d'un individu de la population
	 void remplacement_roulette(Chromosome *individus); // rempacement par roulette biais�e d'un individu de la population par un Chromosome donn�
	void evaluer(double coefNbMisAffecte, double coefDistParcourue, double coefNbMisSpe);
	                     
	void ajouter(bool** genes, int numIndividu);
    void print();

	// opérateur de croisement de deux Chromosomes
    void croisement(Chromosome* parent1, Chromosome* parent2,
                      Chromosome* enfant1, Chromosome* enfant2);
	void test_croisement(int a, int b);
};











#endif // _POPULATION_H