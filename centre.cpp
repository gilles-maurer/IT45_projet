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