#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <string>
#include "position.h"

class Employe {
private:

    int id; 
    int centre_id;
    std::string competence;
    std::string speciality;

public:
    Employe(/* args */);
    ~Employe();
};


#endif // EMPLOYE_H
