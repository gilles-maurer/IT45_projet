#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <string>
#include "centre.h"

class Employe{
private:

    int id; 
    int id_skill;
    int centre_id;
    std::string skill;
    std::string speciality;

public:
    Employe();

    Employe(int id, int centre_id, std::string skill, std::string speciality);

    ~Employe();

    // GETTERS
    int getId();
    int getIdSkill();
    int getCentreId();
    std::string getSkill();
    std::string getSpeciality();

    // SETTERS
    void setIdSkill(int id_skill);


    // METHODES
    void print();
};


#endif // EMPLOYE_H
