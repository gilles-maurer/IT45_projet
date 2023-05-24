#include "centre.h"

using namespace std;

Centre::Centre(/* args */)
{
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

Position Centre::getPosition()
{
    return this->position;
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