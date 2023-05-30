#ifndef _CENTRE_H
#define _CENTRE_H

#include <string>
#include "mission.h"

class Centre {
private:

    int id;
    std::string name;

    float *distance;

public:
    Centre(); 
    Centre(int id, std::string name);

    ~Centre();

    // GETTERS
    int getId();
    std::string getName();

    float getDistance(Mission mission, int nb_centres);
    float getDistance(Centre centre);

    // SETTERS
    void setDistance(float *distance);

    // METHODES
    void print();


};


#endif // _CENTRE_H