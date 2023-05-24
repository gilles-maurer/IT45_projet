#ifndef _MISSION_H
#define _MISSION_H

#include <string>
#include "position.h"

class Mission {
private:

    int id; 
    int day; // valeur entre 1 et 7
    int hour_start; // valeur entre 0 et 23
    int hour_end; // valeur entre 0 et 23
    std::string competence; 
    std::string speciality; 

    Position position;

    int kmean_group;

public:
    Mission(int id, int day, int hour_start, int hour_end, std::string competence, std::string speciality, Position position);
    ~Mission();


    // SETTERS
    void setKmeanGroup(int kmean_group);

};


#endif // _MISSION_H
