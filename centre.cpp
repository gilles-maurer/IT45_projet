#include "centre.h"
#include <iostream>

using namespace std;

Centre::Centre()
{
    this->id = -1;
    this->name = "";

    this->kmean_group = -1;
}

Centre::Centre(int id, string name)
{
    this->id = id;
    this->name = name;

    this->kmean_group = -1;
}   

Centre::~Centre()
{
}


// GETTERS
int Centre::getId()
{
    return this->id;
}

string Centre::getName()
{
    return this->name;
}

int Centre::getKmeanGroup()
{
    return this->kmean_group;
}

float Centre::getDistance(Mission mission, int nb_centres)
{
    return this->distance[mission.getId() + nb_centres - 1];
}

float Centre::getDistance(Centre centre)
{
    return this->distance[centre.getId() - 1];
}





// SETTERS
void Centre::setKmeanGroup(int kmean_group)
{
    this->kmean_group = kmean_group;
}

void Centre::setDistance(float *distance)
{
    this->distance = distance;
}

// METHODES
void Centre::print()
{
    cout << "Centre " << this->id << " : " << this->name << endl;
}