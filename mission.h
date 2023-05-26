#ifndef _MISSION_H
#define _MISSION_H

#include <string>
#include "position.h"

class Mission {
private:

    int id; 
    int day; // valeur entre 1 et 7
    int start_period;
    int end_period;
    std::string skill; 
    std::string speciality; 

    float *distance;

    int kmean_group;

public:
    Mission(int id, int day, int start_period , int end_period, std::string skill, std::string speciality);
    
    Mission();

    ~Mission();

    // GETTERS
    Position getPosition();

    int getId();


    // SETTERS
    void setKmeanGroup(int kmean_group);

    void setDistance(float *distance);

    // METHODES
    void print();

};


#endif // _MISSION_H
