#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <iostream>
#include <string>

std::string get_file_name(int file_number);




void init_parameter(int argc, char **argv, std::string &file_name, int &nb_generations, int &taille_pop, 
                    double &taux_croisement, double &taux_mutation, double &coefNbMisAffecte, 
                    double &coefDistParcourue, double &coefNbMisSpe); 




#endif // _FUNCTIONS_H_    