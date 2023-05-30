#ifndef _CENTRE_H
#define _CENTRE_H

#include <string>
#include "mission.h"

class Centre {
private:

    int id;
    std::string name;

    float *distance;

    int kmean_group;

public:
    Centre(); 
    Centre(int id, std::string name);

    ~Centre();

    // GETTERS
    int getId();
    std::string getName();
    int getKmeanGroup();

    float getDistance(Mission mission, int nb_centres);
    float getDistance(Centre centre);

    // SETTERS
    void setKmeanGroup(int kmean_group);

    void setDistance(float *distance);

    // METHODES
    void print();


};


#endif // _CENTRE_H