#include "mission.h"

using namespace std;


Mission::Mission(int id, int day, int start_period, int end_period, string competence, string speciality, Position position)
{
    this->id = id;
    this->day = day;
    this->start_period = start_period;
    this->end_period = end_period;
    this->competence = competence;
    this->speciality = speciality;
    this->position = position;
    this->kmean_group = -1;
}

Mission::~Mission()
{
}


// SETTERS
void Mission::setKmeanGroup(int kmean_group)
{
    this->kmean_group = kmean_group;
}