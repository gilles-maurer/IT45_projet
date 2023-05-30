#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <string>
#include "centre.h"

class Employe{
private:

    int id; 
    int centre_id;
    std::string skill;
    std::string speciality;

public:
    Employe();

    Employe(int id, int centre_id, std::string skill, std::string speciality);

    ~Employe();


    // METHODES
    void print();
};


#endif // EMPLOYE_H
